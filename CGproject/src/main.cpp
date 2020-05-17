#include "cgmath.h"		// slee's simple math library
#include "cgut.h"		// slee's OpenGL utility
#include "trackball.h"	// virtual trackball
#include "circle2.h"		// circle class definition


//*************************************
// global constants
static const char*	window_name = "cgbase - circle";
static const char*	vert_shader_path = "../bin/shaders/circ.vert";
static const char*	frag_shader_path = "../bin/shaders/circ.frag";
static const uint	MIN_TESS = 3;		// minimum tessellation factor (down to a triangle)
static const uint	MAX_TESS = 256;		// maximum tessellation factor (up to 256 triangles)
uint				NUM_TESS = 70;		// initial tessellation factor of the circle as a polygon
uint				ROTATION = 1;


mat4 view_projection_matrix = { 0 , 1 , 0 , 0 ,
															0 , 0 , 1 , 0 ,
														  -1 , 0 , 0 , 1 ,
														   0 , 0 , 0 , 1 };

//*************************************
// common structures
//struct camera
//{
//	vec3	eye = vec3(0, 0, 5);
//	vec3	at = vec3(0, 0, 0);
//	vec3	up = vec3(0, 1, 0);
//	mat4	view_matrix = mat4::look_at(eye, at, up);
//
//	float	fovy = PI / 4.0f; // must be in radian
//	float	aspect;
//	float	dnear = 1.0f;
//	float	dfar = 1000.0f;
//	mat4	projection_matrix;
//};

//*************************************
// window objects
GLFWwindow*	window = nullptr;
ivec2		window_size = cg_default_window_size(); // initial window size

//*************************************
// OpenGL objects
GLuint	program = 0;		// ID holder for GPU program
GLuint	vertex_array = 0;	// ID holder for vertex array object

//*************************************
// global variables
int		frame = 0;						// index of rendering frames
float	t = 0.0f;						// current simulation parameter
bool	b_solid_color = false;			// use circle's color?
bool	b_index_buffer = true;			// use index buffering?
#ifndef GL_ES_VERSION_2_0
bool	b_wireframe = false;
#endif
auto	circles = std::move(create_circles());
struct { bool add=false, sub=false; operator bool() const { return add||sub; } } b; // flags of keys for smooth changes
int	TEXTURE_MODE = 0;
float ROTATION_SPEED=1.0f;
int ROTATION_FLAG = 0;
bool SHIFT_ON = false;
bool CTRL_ON = false;
int MOVE = 0;


//*************************************
// scene objects
camera		cam;
trackball	tb;


//*************************************
// holder of vertices and indices of a unit circle
std::vector<vertex>	unit_circle_vertices;	// host-side vertices

//*************************************
void update()
{
	cam.aspect = window_size.x / float(window_size.y);
	cam.projection_matrix = mat4::perspective(cam.fovy, cam.aspect, cam.dnear, cam.dfar);


	// update global simulation parameter
	t = float(glfwGetTime()*0.7f) ;

	// tricky aspect correction matrix for non-square window
	float aspect = window_size.x/float(window_size.y);
	mat4 aspect_matrix = 
	{
		min(1/aspect,1.0f), 0, 0, 0,
		0, min(aspect,1.0f), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	// update common uniform variables in vertex/fragment shaders
	GLint uloc;
	uloc = glGetUniformLocation( program, "b_solid_color" );	if(uloc>-1) glUniform1i( uloc, b_solid_color );
	//uloc = glGetUniformLocation( program, "aspect_matrix" );	if(uloc>-1) glUniformMatrix4fv( uloc, 1, GL_TRUE, aspect_matrix );

	//updating view point
	
	//여기!
	
	//cam.view_matrix = mat4::look_at(cam.eye, cam.at, cam.up);
	view_projection_matrix = cam.projection_matrix * cam.view_matrix;
	uloc = glGetUniformLocation(program, "aspect_matrix");
	glUniformMatrix4fv(uloc, 1, GL_TRUE, view_projection_matrix);


	// update vertex buffer by the pressed keys
	void update_tess(); // forward declaration
	if(b) update_tess(); 
}

void render()
{
	// clear screen (with background color) and clear depth buffer
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// notify GL that we use our own program
	glUseProgram( program );

	// bind vertex array object
	glBindVertexArray( vertex_array );

	// render two circles: trigger shader program to process vertex data
	for( auto& c : circles )
	{
		// per-circle update
		c.update(t);

		// update per-circle uniforms
		GLint uloc;
		uloc = glGetUniformLocation( program, "solid_color" );		if(uloc>-1) glUniform4fv( uloc, 1, c.color );	// pointer version
		uloc = glGetUniformLocation( program, "model_matrix" );		if(uloc>-1) glUniformMatrix4fv( uloc, 1, GL_TRUE, c.model_matrix );

		// per-circle draw calls
		if(b_index_buffer)	glDrawElements( GL_TRIANGLES, (NUM_TESS)*(NUM_TESS)*6, GL_UNSIGNED_INT, nullptr );
		else				glDrawArrays( GL_TRIANGLES, 0, NUM_TESS* NUM_TESS*6); // NUM_TESS = N
	}

	// swap front and back buffers, and display to screen
	glfwSwapBuffers( window );
}

void reshape( GLFWwindow* window, int width, int height )
{
	// set current viewport in pixels (win_x, win_y, win_width, win_height)
	// viewport: the window area that are affected by rendering 
	window_size = ivec2(width,height);
	glViewport( 0, 0, width, height );
}

void print_help()
{
	printf( "[help]\n" );
	printf( "- press ESC or 'q' to terminate the program\n" );
	printf( "- press 'd' to change texture coordinate mode\n" );
	printf( "- press '+/-' to change ROTATION SPEED !!!\n");
#ifndef GL_ES_VERSION_2_0
	printf( "- press 'w' to toggle wireframe\n" );
#endif
	printf( "\n" );
}



std::vector<vertex> create_circle_vertices( uint N )
{										//     position3   norm3         tex2
	std::vector<vertex> v = {{ vec3(2,2,2), vec3(0,0,-1.0f), vec3(0.5f,0,0),vec3(0,0,0) }}; // origin


	for (uint k = 0; k <= N; k++) {
		for (uint j = 0; j <= N; j++) {

			float theta = (PI * k) / float(N), phi =( (2* PI * j) / float(N));
			float s_theta = sin(theta), c_theta = cos(theta), s_phi = sin(phi), c_phi = cos(phi);
			float x = s_theta * c_phi;
			float  y = s_theta * s_phi;
			float  z = c_theta;
			//v.push_back({ vec3(y,z,x), vec3(y,z,x), vec2( phi/(2*PI),1-theta/PI)});
			if ( TEXTURE_MODE == 0) v.push_back({ vec3(y,z,x), vec3(y,z,x), vec3(phi / (2 * PI) , 1 - (theta / PI),0),vec3(0,0,0) });
			if (TEXTURE_MODE == 1) v.push_back({ vec3(y,z,x), vec3(y,z,x), vec3(phi / (2 * PI),phi / (2 * PI),phi / (2 * PI)),vec3(0,0,0) });
			if (TEXTURE_MODE == 2) v.push_back({ vec3(y,z,x), vec3(y,z,x), vec3(1 - (theta / PI),1 - (theta / PI),1 - (theta / PI)), vec3(0,0,0) });

			

		}
	}
	return v;
}

void update_vertex_buffer( const std::vector<vertex>& vertices, uint N )
{
	static GLuint vertex_buffer = 0;	// ID holder for vertex buffer
	static GLuint index_buffer = 0;		// ID holder for index buffer
	// clear and create new buffers
	if(vertex_buffer)	glDeleteBuffers( 1, &vertex_buffer );	vertex_buffer = 0;
	if(index_buffer)	glDeleteBuffers( 1, &index_buffer );	index_buffer = 0;

	// check exceptions
	if(vertices.empty()){ printf("[error] vertices is empty.\n"); return; }

	// create buffers
	if(b_index_buffer)
	{
		std::vector<uint> indices;
		for( uint k=0; k <N; k++ )
		{
			for (uint j = 0; j < N; j++) {
				indices.push_back((N + 1)*j + k + 1);
				indices.push_back((N + 1) *j + k + (N+1) + 1);
				indices.push_back((N + 1) *j + k + (N+1) + 2); //뭐지?  +N을 해서 한칸이 밀린건가..? 

				indices.push_back((N + 1) * j + k + 1);
				indices.push_back((N + 1) * j + k + (N+1) + 2);
				indices.push_back((N + 1) * j + k + 2);
			}
		}

		// generation of vertex buffer: use vertices as it is
		glGenBuffers( 1, &vertex_buffer );
		glBindBuffer( GL_ARRAY_BUFFER, vertex_buffer );
		glBufferData( GL_ARRAY_BUFFER, sizeof(vertex)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

		// geneation of index buffer
		glGenBuffers( 1, &index_buffer );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, index_buffer );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)*indices.size(), &indices[0], GL_STATIC_DRAW );
	}
	else
	{
		std::vector<vertex> v; // triangle vertices
		for( uint k=0; k < N; k++ )
		{
			for (uint j = 0; j < N; j++)
			{
				v.push_back(vertices[(N + 1) *j + k + 1]);
				v.push_back(vertices[(N + 1) *j + k + (N+1) + 1]);
				v.push_back(vertices[(N + 1)*j + k + (N+1) + 2]);
													 
				v.push_back(vertices[(N + 1) * j + k + 1]);
				v.push_back(vertices[(N + 1) * j + k + (N+1) + 2]);
				v.push_back(vertices[(N + 1) * j + k + 2]);
			}
		}

		// generation of vertex buffer: use triangle_vertices instead of vertices
		glGenBuffers( 1, &vertex_buffer );
		glBindBuffer( GL_ARRAY_BUFFER, vertex_buffer );
		glBufferData( GL_ARRAY_BUFFER, sizeof(vertex)*v.size(), &v[0], GL_STATIC_DRAW );
	}

	// generate vertex array object, which is mandatory for OpenGL 3.3 and higher
	if(vertex_array) glDeleteVertexArrays(1,&vertex_array);
	vertex_array = cg_create_vertex_array( vertex_buffer, index_buffer );
	if(!vertex_array){ printf("%s(): failed to create vertex aray\n",__func__); return; }
}

void update_tex()
{
	unit_circle_vertices = create_circle_vertices(NUM_TESS);
	update_vertex_buffer(unit_circle_vertices, NUM_TESS);
}


void update_tess()
{

	update_vertex_buffer( unit_circle_vertices, NUM_TESS);
	//if (b.add == true) ROTATION_SPEED += 0.005f;
	//if (b.sub == true) ROTATION_SPEED -= 0.005f;
	printf( "> Rotation Speed = % -4f\r", ROTATION_SPEED );
}

void keyboard( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	if(action==GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)	glfwSetWindowShouldClose(window, GL_TRUE);
		else if (key == GLFW_KEY_H || key == GLFW_KEY_F1)	print_help();
		else if (key == GLFW_KEY_R) {
			ROTATION = (ROTATION + 1) % 2;
			if (ROTATION == 0) {
				printf("Rotation Disdabled\n");
			}
			else {
				printf("Rotation Enabled\n");
			}
		}
		else if (key == GLFW_KEY_KP_ADD || (key == GLFW_KEY_EQUAL && (mods & GLFW_MOD_SHIFT))) { b.add = true; ROTATION_FLAG = 1; ROTATION = 0; ROTATION_SPEED += 0.5f; }
		else if (key == GLFW_KEY_KP_SUBTRACT || key == GLFW_KEY_MINUS) { b.sub = true; ROTATION_FLAG = 1; ROTATION = 0; ROTATION_SPEED -= 0.5f; }
		else if (key == GLFW_KEY_M) { MOVE = (MOVE + 1) % 2; printf("MOVE!!\n"); }
		else if(key==GLFW_KEY_I)
		{
			//b_index_buffer = !b_index_buffer;
			update_vertex_buffer( unit_circle_vertices,NUM_TESS );
			printf( "> using %s buffering\n", b_index_buffer?"index":"vertex" );
		}
		else if(key==GLFW_KEY_D)
		{
			TEXTURE_MODE = (TEXTURE_MODE + 1) % 3;
			update_tex();
			printf( "Changed texture coordinate %d\n", TEXTURE_MODE);
		}
#ifndef GL_ES_VERSION_2_0
		else if(key==GLFW_KEY_W)
		{
			b_wireframe = !b_wireframe;
			glPolygonMode( GL_FRONT_AND_BACK, b_wireframe ? GL_LINE:GL_FILL );
			printf( "> using %s mode\n", b_wireframe ? "wireframe" : "solid" );
		}

#endif
	}
	
	else if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_KP_ADD || (key == GLFW_KEY_EQUAL && (mods & GLFW_MOD_SHIFT)))	b.add = false;
		else if (key == GLFW_KEY_KP_SUBTRACT || key == GLFW_KEY_MINUS) b.sub = false;

		else if (key == GLFW_KEY_LEFT_SHIFT) { SHIFT_ON = false; }
		else if (key == GLFW_KEY_LEFT_CONTROL) { CTRL_ON = false; }

		//******WASD 움직임 end*********//
		else if (key == GLFW_KEY_W) { tb.end_W(); }
		else if (key == GLFW_KEY_A) { tb.end_A(); }
		else if (key == GLFW_KEY_S) { tb.end_S(); }
		else if (key == GLFW_KEY_D) { tb.end_D(); }
		else if (key == GLFW_KEY_RIGHT) { tb.end_RIGHT(); }
		else if (key == GLFW_KEY_LEFT) { tb.end_LEFT(); }

	}

	if (action == GLFW_PRESS)
	{
		dvec2 pos; glfwGetCursorPos(window, &pos.x, &pos.y);
		vec2 npos = cursor_to_ndc(pos, window_size);

		if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)	glfwSetWindowShouldClose(window, GL_TRUE);
		else if (key == GLFW_KEY_H || key == GLFW_KEY_F1)	print_help();
		else if (key == GLFW_KEY_HOME)					cam = camera();

		else if (key == GLFW_KEY_LEFT_SHIFT)				{SHIFT_ON = true;}
		else if (key == GLFW_KEY_LEFT_CONTROL)		{CTRL_ON = true;}

		//******WASD 움직임 begin*********//

		else if (key == GLFW_KEY_W) { tb.begin_W(cam.view_matrix,npos); }
		else if (key == GLFW_KEY_A) { tb.begin_A(cam.view_matrix, npos); }
		else if (key == GLFW_KEY_S) { tb.begin_S(cam.view_matrix, npos); }
		else if (key == GLFW_KEY_D) { tb.begin_D(cam.view_matrix, npos); }
		else if (key == GLFW_KEY_RIGHT) { tb.begin_RIGHT(cam.view_matrix, npos); }
		else if (key == GLFW_KEY_LEFT) { tb.begin_LEFT(cam.view_matrix, npos); }


	}

	printf("asdf");

	
	
}

void mouse( GLFWwindow* window, int button, int action, int mods )
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && SHIFT_ON==false && CTRL_ON==false)
	{
		dvec2 pos; glfwGetCursorPos(window, &pos.x, &pos.y);

		vec2 npos = cursor_to_ndc(pos, window_size);
		if (action == GLFW_PRESS)			tb.begin(cam.view_matrix, npos);
		else if (action == GLFW_RELEASE)	tb.end();
	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE || (CTRL_ON==true && button == GLFW_MOUSE_BUTTON_LEFT))
	{
		dvec2 pos; glfwGetCursorPos(window, &pos.x, &pos.y);

		vec2 npos = cursor_to_ndc(pos, window_size);
		if (action == GLFW_PRESS)			tb.begin_panning(cam.view_matrix, npos);
		else if (action == GLFW_RELEASE)	tb.end_panning();
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT || (SHIFT_ON==true && button == GLFW_MOUSE_BUTTON_LEFT))
	{
		dvec2 pos; glfwGetCursorPos(window, &pos.x, &pos.y);

		vec2 npos = cursor_to_ndc(pos, window_size);
		if (action == GLFW_PRESS)			tb.begin_zooming(cam.view_matrix, npos);
		else if (action == GLFW_RELEASE)	tb.end_zooming();
	}





}

void motion( GLFWwindow* window, double x, double y )
{
	if (tb.is_tracking()) {
		vec2 npos = cursor_to_ndc(dvec2(x, y), window_size);
		printf("TRACKING\tx: %f  -------  y: %f\n", x, y);
		cam.view_matrix = tb.update(npos);
	}

	if (tb.is_panning()) {
		vec2 npos = cursor_to_ndc(dvec2(x, y), window_size);
		printf("PANNING\t\tx: %f  -------  y: %f\n", x, y);
		cam.view_matrix = tb.update_panning(npos);
	}

	if (tb.is_zooming()) {
		vec2 npos = cursor_to_ndc(dvec2(x, y), window_size);
		printf("ZOOMING\t\tx: %f  -------  y: %f\n", x, y);
		cam.view_matrix = tb.update_zooming(npos);
	}

}

bool user_init()
{
	// log hotkeys
	print_help();

	// init GL states
	glLineWidth( 1.0f );
	glClearColor( 39/255.0f, 40/255.0f, 34/255.0f, 1.0f );	// set clear color
	glEnable( GL_CULL_FACE );								// turn on backface culling
	glEnable( GL_DEPTH_TEST );								// turn on depth tests
	
	// define the position of four corner vertices
	unit_circle_vertices = std::move(create_circle_vertices(NUM_TESS));

	// create vertex buffer; called again when index buffering mode is toggled
	update_vertex_buffer( unit_circle_vertices, NUM_TESS);

	return true;
}

void user_finalize()
{
}

int main( int argc, char* argv[] )
{
	// create window and initialize OpenGL extensions
	if(!(window = cg_create_window( window_name, window_size.x, window_size.y ))){ glfwTerminate(); return 1; }
	if(!cg_init_extensions( window )){ glfwTerminate(); return 1; }	// init OpenGL extensions

	// initializations and validations of GLSL program
	if(!(program=cg_create_program( vert_shader_path, frag_shader_path ))){ glfwTerminate(); return 1; }	// create and compile shaders/program
	if(!user_init()){ printf( "Failed to user_init()\n" ); glfwTerminate(); return 1; }					// user initialization

	// register event callbacks
	glfwSetWindowSizeCallback( window, reshape );	// callback for window resizing events
    glfwSetKeyCallback( window, keyboard );			// callback for keyboard events
	glfwSetMouseButtonCallback( window, mouse );	// callback for mouse click inputs
	glfwSetCursorPosCallback( window, motion );		// callback for mouse movements

	// enters rendering/event loop
	for( frame=0; !glfwWindowShouldClose(window); frame++ )
	{

		if (tb.is_W()) { cam.view_matrix = tb.update_W(vec2(0)); }
		if (tb.is_A()) { cam.view_matrix = tb.update_A(vec2(0)); }
		if (tb.is_S()) { cam.view_matrix = tb.update_S(vec2(0)); }
		if (tb.is_D()) { cam.view_matrix = tb.update_D(vec2(0)); }
		if (tb.is_RIGHT()) { cam.view_matrix = tb.update_RIGHT(vec2(0)); }
		if (tb.is_LEFT()) { cam.view_matrix = tb.update_LEFT(vec2(0)); }


		glfwPollEvents();	// polling and processing of events
		update();			// per-frame update
		render();			// per-frame render
	}
	
	// normal termination
	user_finalize();
	cg_destroy_window(window);

	return 0;
}
