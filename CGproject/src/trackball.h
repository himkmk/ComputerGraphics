#ifndef __TRACKBALL_H__
#define __TRACKBALL_H__
#include "cgmath.h"


// 외부에서 cam 변수를 불러옴. 따라서  main 파일에서 정의된 카메라 이름이 cam 이어야함.
extern float t;

struct camera
{
	vec3	eye = vec3(0, 0, 15);
	vec3	at = vec3(0, 0, 0);
	vec3	up = vec3(0, 1, 0);
	mat4	view_matrix = mat4::look_at(eye, at, up);

	float	fovy = PI / 4.0f; // must be in radian
	float	aspect;
	float	dnear = 1.0f;
	float	dfar = 1000.0f;
	mat4	projection_matrix;
};

extern camera cam;

struct trackball
{

	float	scale;			// controls how much rotation is applied
	mat4	view_matrix0;	// initial view matrix
	vec2	m0;				// the last mouse position
	float t0;					// 함수 불린 시점.
	float speed=2;			//camer의 이동 속도 . 아마 탱크의 이동속도랑 같아야될듯?

	void begin_ALL() {
		b_W = true;
		b_A = true;
		b_S = true;
		b_D = true;
		b_RIGHT = true;
		b_LEFT = true;
	};		// WASD 방향으로 움직이는거 
	void end_ALL() { 
		b_W = false;
		b_A = false;
		b_S = false;
		b_D = false;
		b_RIGHT = false;
		b_LEFT = false;
	}



	vec3 eye0=vec3(0);
	vec3 at0= vec3(0);
	vec3 up0= vec3(0);
	
	trackball( float rot_scale=1.0f ) : scale(rot_scale){}




	// ************ WASD 움직이는거 ***************//

	bool b_W = false;
	bool b_A = false;
	bool b_S = false;
	bool b_D = false;
	bool b_LEFT = false;
	bool b_RIGHT = false;

	bool is_W() const { return b_W; }
	bool is_A() const { return b_A; }
	bool is_S() const { return b_S; }
	bool is_D() const { return b_D; }
	bool is_LEFT() const { return b_LEFT; }
	bool is_RIGHT() const { return b_RIGHT; }

	void begin_W(const mat4& view_matrix, vec2 m);		// WASD 방향으로 움직이는거 
	void begin_A(const mat4& view_matrix, vec2 m);		// WASD 방향으로 움직이는거 
	void begin_S(const mat4& view_matrix, vec2 m);			// WASD 방향으로 움직이는거 
	void begin_D(const mat4& view_matrix, vec2 m);		// WASD 방향으로 움직이는거 
	void begin_LEFT(const mat4& view_matrix, vec2 m);		// WASD 방향으로 움직이는거 
	void begin_RIGHT(const mat4& view_matrix, vec2 m);		// WASD 방향으로 움직이는거 



	void end_W() { b_W= false; }
	void end_A() { b_A = false; }
	void end_S() { b_S= false; }
	void end_D() { b_D = false; }
	void end_LEFT() { b_LEFT = false; }
	void end_RIGHT() { b_RIGHT= false; }

	mat4 update_W(vec2 m) const;
	mat4 update_A(vec2 m) const;
	mat4 update_S(vec2 m) const;
	mat4 update_D(vec2 m) const;
	mat4 update_LEFT(vec2 m) const;
	mat4 update_RIGHT(vec2 m) const;


	// ************ TRACKING ****************//
	bool	b_tracking = false;
	bool is_tracking() const { return b_tracking; }
	void begin( const mat4& view_matrix, vec2 m );
	void end() { b_tracking = false; }
	mat4 update( vec2 m ) const;


	// *********** PANNING ***************//
	bool	b_panning = false;
	bool is_panning() const { return b_panning; }
	void begin_panning(const mat4& view_matrix, vec2 m);  //panning
	void end_panning() { b_panning = false; }
	mat4 update_panning(vec2 m) const;


	//*********** ZOOMING *************//
	bool	b_zooming = false;
	bool is_zooming() const { return b_zooming; }
	void begin_zooming(const mat4& view_matrix, vec2 m);  //zooming
	void end_zooming() { b_zooming = false; }
	mat4 update_zooming(vec2 m) const;
};




// *************** BEGIN 함수들 **********************//
inline void trackball::begin(const mat4& view_matrix, vec2 m)
{
	end_ALL();

	b_tracking = true;			// enable trackball tracking
	m0 = m;						// save current mouse position
	t0 = t;
	view_matrix0 = view_matrix;	// save current view matrix

	eye0 = cam.eye;
	at0 = cam.at;
	up0 = cam.up;
}

inline void trackball::begin_panning(const mat4& view_matrix, vec2 m)
{
	end_ALL();

	b_panning= true;			// enable trackball tracking
	m0 = m;						// save current mouse position
	t0 = t;
	view_matrix0 = view_matrix;	// save current view matrix

	eye0 = cam.eye;
	at0 = cam.at;
	up0 = cam.up;
}

inline void trackball::begin_zooming(const mat4& view_matrix, vec2 m)
{
	end_ALL();

	b_zooming = true;			// enable trackball tracking
	m0 = m;						// save current mouse position
	t0 = t;
	view_matrix0 = view_matrix;	// save current view matrix

	eye0 = cam.eye;
	at0 = cam.at;
	up0 = cam.up;
}

inline void trackball::begin_W(const mat4& view_matrix, vec2 m)
{
	end_ALL();

	b_W = true;			// enable trackball tracking
	m0 = m;						// save current mouse position
	t0 = t;
	view_matrix0 = view_matrix;	// save current view matrix

	eye0 = cam.eye;
	at0 = cam.at;
	up0 = cam.up;
}

inline void trackball::begin_A(const mat4& view_matrix, vec2 m)
{
	end_ALL();

	b_A = true;			// enable trackball tracking
	m0 = m;						// save current mouse position
	t0 = t;
	view_matrix0 = view_matrix;	// save current view matrix

	eye0 = cam.eye;
	at0 = cam.at;
	up0 = cam.up;
}

inline void trackball::begin_S(const mat4& view_matrix, vec2 m)
{
	end_ALL();

	b_S = true;			// enable trackball tracking
	m0 = m;						// save current mouse position
	t0 = t;
	view_matrix0 = view_matrix;	// save current view matrix

	eye0 = cam.eye;
	at0 = cam.at;
	up0 = cam.up;
}

inline void trackball::begin_D(const mat4& view_matrix, vec2 m)
{
	end_ALL();

	b_D = true;			// enable trackball tracking
	m0 = m;						// save current mouse position
	t0 = t;
	view_matrix0 = view_matrix;	// save current view matrix

	eye0 = cam.eye;
	at0 = cam.at;
	up0 = cam.up;
}

inline void trackball::begin_LEFT(const mat4& view_matrix, vec2 m)
{
	end_ALL();

	b_LEFT = true;			// enable trackball tracking
	m0 = m;						// save current mouse position
	t0 = t;
	view_matrix0 = view_matrix;	// save current view matrix

	eye0 = cam.eye;
	at0 = cam.at;
	up0 = cam.up;
}

inline void trackball::begin_RIGHT(const mat4& view_matrix, vec2 m)
{
	end_ALL();

	b_RIGHT = true;			// enable trackball tracking
	m0 = m;						// save current mouse position
	t0 = t;
	view_matrix0 = view_matrix;	// save current view matrix

	eye0 = cam.eye;
	at0 = cam.at;
	up0 = cam.up;
}




//********************UPDATE 함수들 *************************//
inline mat4 trackball::update(vec2 m) const  //input  n == npos
{
	// project a 2D mouse position to a unit sphere
	static const vec3 p0 = vec3(0, 0, 1.0f);																				// reference position on sphere
	vec3 p1 = vec3(m - m0, 0);																									// displacement
	if (!b_tracking || length(p1) < 0.0001f) return view_matrix0;										// ignore subtle movement
	p1 *= scale;																															// apply rotation scale
	p1 = vec3(p1.x, p1.y, sqrtf(max(0, 1.0f - length2(p1)))).normalize();							// back-project z=0 onto the unit sphere = p1


	vec3 v = p0.cross(p1);

	float theta = asin(min(v.length(), 1.0f));

	
	vec4 eye00 = vec4(eye0, 1);
	vec4 at00 = vec4(at0, 1);
	vec4 up00 = vec4(up0, 0);
	
	vec4 eye = (mat4::translate(cam.eye) * mat4::rotate(v.normalize(), theta) * (mat4::translate(-1 * cam.eye) * eye00)) ;
	vec4 at = (mat4::translate(cam.eye) * mat4::rotate(v.normalize(), theta) * (mat4::translate(-1 * cam.eye) * at00));
	vec4 up = mat4::rotate(v.normalize(), theta) * up00;

	cam.eye = vec3(eye.x, eye.y, eye.z);
	cam.at = vec3(at.x, at.y, at.z);
	cam.up = vec3(up.x, up.y, up.z);


	return mat4::look_at(cam.eye, cam.at, cam.up);
}




inline mat4 trackball::update_panning(vec2 m) const
{
																																						// project a 2D mouse position to a unit sphere
	static const vec3 p0 = vec3(0, 0, 1.0f);																					// reference position on sphere
	vec3 p1 = vec3(m - m0, 0);																										// displacement
	if (!b_panning || length(p1) < 0.0001f) return view_matrix0;											// ignore subtle movement
	
	p1 *= scale;																																// apply rotation scale
	p1 = vec3(p1.x, p1.y, sqrtf(max(0, 1.0f - length2(p1)))).normalize();								// back-project z=0 onto the unit sphere

	vec3 v = mat3(view_matrix0).transpose() * p0.cross(p1);
	float theta = asin(min(v.length(), 1.0f));

	vec3 up = -1*cam.up;																												//윗방향 및 옆방향 알아내는 중
	vec3 side = -1*((cam.at - cam.eye).cross(cam.up)).normalize();

	cam.eye = eye0 + up * p1.y + side*p1.x;
	cam.at = at0 + up*p1.y + side*p1.x;

	return mat4::look_at(cam.eye, cam.at, cam.up);
}




inline mat4 trackball::update_zooming(vec2 m) const
{
																																						// project a 2D mouse position to a unit sphere
	static const vec3 p0 = vec3(0, 0, 1.0f);																					// reference position on sphere
	vec3 p1 = vec3(m - m0, 0);																										// displacement
	if (!b_zooming || length(p1) < 0.0001f) return view_matrix0;										// ignore subtle movement
	p1 *= scale;										



	vec3 towards = (at0 - eye0).normalize();
	
	cam.eye = eye0 + towards * p1.y * 10;

	return mat4::look_at(cam.eye, cam.at, cam.up);

}



inline mat4 trackball::update_W(vec2 m) const
{
	vec3 towards = (at0 - eye0).normalize();
	vec3 side = ((cam.at - cam.eye).cross(cam.up)).normalize();

	cam.eye = eye0 + towards * (t - t0) * speed;
	
	return mat4::look_at(cam.eye, cam.at, cam.up);
}


inline mat4 trackball::update_A(vec2 m) const
{
	vec3 towards = (at0 - eye0).normalize();
	vec3 side = ((cam.at - cam.eye).cross(cam.up)).normalize();

	cam.eye = eye0 - side * (t-t0) * speed;
	cam.at = at0 - side * (t - t0) * speed;

	return mat4::look_at(cam.eye, cam.at, cam.up);
}


inline mat4 trackball::update_S(vec2 m) const
{
	vec3 towards = (at0 - eye0).normalize();
	vec3 side = ((cam.at - cam.eye).cross(cam.up)).normalize();

	cam.eye = eye0 - towards * (t - t0) * speed;

	return mat4::look_at(cam.eye, cam.at, cam.up);
}


inline mat4 trackball::update_D(vec2 m) const
{
	vec3 towards = (at0 - eye0).normalize();
	vec3 side = ((cam.at - cam.eye).cross(cam.up)).normalize();

	cam.eye = eye0 + side * (t - t0) * speed;
	cam.at = at0 + side * (t - t0) * speed;

	return mat4::look_at(cam.eye, cam.at, cam.up);
}

inline mat4 trackball::update_LEFT(vec2 m) const
{
	//vec4 eye00 = vec4(eye0, 1);
	vec4 at00 = vec4(at0, 1);
	//vec4 up00 = vec4(up0, 0);

	//vec4 eye = (mat4::translate(cam.eye) * mat4::rotate(vec3(0,1,0), t-t0) * (mat4::translate(-1 * cam.eye) * eye00));
	vec4 at = (mat4::translate(cam.eye) * mat4::rotate(vec3(0,1,0), t-t0) * (mat4::translate(-1 * cam.eye) * at00));
	//vec4 up = mat4::rotate(vec3(0,1,0), t-t0) * up00;

	//cam.eye = vec3(eye.x, eye.y, eye.z);
	cam.at = vec3(at.x, at.y, at.z);
	//cam.up = vec3(up.x, up.y, up.z);

	return mat4::look_at(cam.eye, cam.at, cam.up);
}

inline mat4 trackball::update_RIGHT(vec2 m) const
{
	//vec4 eye00 = vec4(eye0, 1);
	vec4 at00 = vec4(at0, 1);
	//vec4 up00 = vec4(up0, 0);

	//vec4 eye = (mat4::translate(cam.eye) * mat4::rotate(vec3(0,1,0), t-t0) * (mat4::translate(-1 * cam.eye) * eye00));
	vec4 at = (mat4::translate(cam.eye) * mat4::rotate(vec3(0, 1, 0), t0 - t) * (mat4::translate(-1 * cam.eye) * at00));
	//vec4 up = mat4::rotate(vec3(0,1,0), t-t0) * up00;

	//cam.eye = vec3(eye.x, eye.y, eye.z);
	cam.at = vec3(at.x, at.y, at.z);
	//cam.up = vec3(up.x, up.y, up.z);

	return mat4::look_at(cam.eye, cam.at, cam.up);
}












// utility function
inline vec2 cursor_to_ndc(dvec2 cursor, ivec2 window_size)
{
	// normalize window pos to [0,1]^2
	vec2 npos = vec2(float(cursor.x) / float(window_size.x - 1),
		float(cursor.y) / float(window_size.y - 1));

	// normalize window pos to [-1,1]^2 with vertical flipping
	// vertical flipping: window coordinate system defines y from
	// top to bottom, while the trackball from bottom to top
	return vec2(npos.x * 2.0f - 1.0f, 1.0f - npos.y * 2.0f);
}




#endif // __TRACKBALL_H__
