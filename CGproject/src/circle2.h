#pragma once
#ifndef __CIRCLE_H__
#define __CIRCLE_H__

extern uint ROTATION;
extern float ROTATION_SPEED;
extern int ROTATION_FLAG;
extern int MOVE;


struct circle_t
{
	vec3	center=vec3(0);		// 2D position for translation
	float	radius = 0;		// radius
	float	theta=0.0f;			// rotation angle
	vec4	color;				// RGBA color in [0,1]
	mat4	model_matrix;		// modeling transformation
	float save_t1=0, save_t2=0;

	//coord is RHS
	float orbit_height = 0;
	float orbit_radius = 0.5f;
	float orbit_speed = 1;		//sin(speed*t) 이런식으로 곱해야됨. 븅신마냥 나누고 뇌정지 ㄴㄴ
	float rotation_speed = 1;


	// public functions
	void	update( float t );	
};

inline std::vector<circle_t> create_circles()
{
	std::vector<circle_t> circles;
	circle_t c;
	//		center				 radius		theta					color	

	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +1.50f; c.orbit_radius =+1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +2.00f; c.orbit_radius =+1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +2.50f; c.orbit_radius =+1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +1.00f; c.orbit_radius =+1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +3.00f; c.orbit_radius =+1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +3.50f; c.orbit_radius =+1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양

	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +1.00f; c.orbit_radius =-1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +1.50f; c.orbit_radius =-1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +2.00f; c.orbit_radius =-1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +2.50f; c.orbit_radius =-1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +3.00f; c.orbit_radius =-1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +3.50f; c.orbit_radius =-1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
																																												   
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -1.00f; c.orbit_radius = +1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -1.50f; c.orbit_radius = +1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -2.00f; c.orbit_radius = +1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -2.50f; c.orbit_radius = +1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -3.00f; c.orbit_radius = +1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -3.50f; c.orbit_radius = +1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양

	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -1.00f; c.orbit_radius = -1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -1.50f; c.orbit_radius = -1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -2.00f; c.orbit_radius = -1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -2.50f; c.orbit_radius = -1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -3.00f; c.orbit_radius = -1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -3.50f; c.orbit_radius = -1.50f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양

	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +1.00f; c.orbit_radius = +0.00f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +1.50f; c.orbit_radius = +0.00f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +2.00f; c.orbit_radius = +0.00f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +2.50f; c.orbit_radius = +0.00f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +3.00f; c.orbit_radius = +0.00f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +3.50f; c.orbit_radius = +0.00f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양

	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -1.00f; c.orbit_radius = -0.00f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -1.50f; c.orbit_radius = -0.00f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -2.00f; c.orbit_radius = -0.00f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -2.50f; c.orbit_radius = -0.00f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -3.00f; c.orbit_radius = -0.00f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.10f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = -3.50f; c.orbit_radius = -0.00f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양















	c = { vec3(0,0,0),	0.30f,	0.0f,	vec4(0.0f,0.0f,1.5f,0.5f) };  c.orbit_height = +0.00f; c. orbit_radius = 0.00f; c.orbit_speed = 0.00f; c.rotation_speed = 1.2f;         circles.emplace_back(c);	  //태양
	c = { vec3(0,0,0),	0.06f,	0.0f,	vec4(1.0f,0.5f,0.5f,1.0f) };  c.orbit_height = -0.07f;  c. orbit_radius = 0.75f; c.orbit_speed = 1.00f; c.rotation_speed = 2.3f;         circles.emplace_back(c);	  //행성1
	c = { vec3(0,0,0),	0.04f,	0.0f,	vec4(1.0f,0.5f,0.5f,1.0f) };  c.orbit_height = +0.05f; c. orbit_radius = 1.85f; c.orbit_speed = 2.30f; c.rotation_speed = 3.5f;      	circles.emplace_back(c);  //행성2
	c = { vec3(0,0,0),	0.02f,	0.0f,	vec4(1.0f,0.5f,0.5f,1.0f) };  c.orbit_height = +0.04f; c. orbit_radius = 2.00f; c.orbit_speed = 3.80f; c.rotation_speed = 4.0f;      	circles.emplace_back(c);	  //행성3
	c = { vec3(0,0,0),	0.05f,	0.0f,	vec4(1.0f,0.5f,0.5f,1.0f) };  c.orbit_height = -0.04f;  c. orbit_radius = 1.95f; c.orbit_speed = 2.00f; c.rotation_speed = 2.1f;      	circles.emplace_back(c);  //행성4
	c = { vec3(0,0,0),	0.08f,	0.0f,	vec4(1.0f,0.5f,0.5f,1.0f) };  c.orbit_height = +0.02f; c. orbit_radius = 0.90f; c.orbit_speed = 1.50f; c.rotation_speed = 2.7f;      	circles.emplace_back(c);  //행성5
	c = { vec3(0,0,0),	0.03f,	0.0f,	vec4(1.0f,0.5f,0.5f,1.0f) };  c.orbit_height = +0.02f; c. orbit_radius = 2.20f; c.orbit_speed = 3.00f; c.rotation_speed = 3.6f;      	circles.emplace_back(c);  //행성6
	c = { vec3(0,0,0),	0.05f,	0.0f,	vec4(1.0f,0.5f,0.5f,1.0f) };  c.orbit_height = -0.01f;  c.orbit_radius = 1.65f; c.orbit_speed = 2.50f; c.rotation_speed = 2.5f;      	circles.emplace_back(c);  //행성7
	c = { vec3(0,0,0),	0.05f,	0.0f,	vec4(1.0f,0.5f,0.5f,1.0f) };  c.orbit_height = -0.05f;  c.orbit_radius = 1.95f; c.orbit_speed = 2.70f; c.rotation_speed = 2.9f;		 	circles.emplace_back(c);  //행성7






	//c = {vec2(+0.5f,0),1.0f,0.0f,vec4(0.5f,1.0f,1.0f,1.0f)};
	//circles.emplace_back(c);

	return circles;
}

inline void circle_t::update(float t)
{
	theta = t;
	
	float c = cos(theta), s = sin(theta);

	// these transformations will be explained in later transformation lecture
	mat4 scale_matrix =
	{
		radius, 0, 0, 0,
		0, radius, 0, 0,
		0, 0, radius, 0,
		0, 0, 0, 1
	};

	if (MOVE == 1) {

		scale_matrix *=
		{
			cos(t * 3) / 10.0f + 0.3f, 0, 0, 0,
				0, cos(t * 3) / 10.0f + 0.3f, 0, 0,
				0, 0, cos(t * 3) / 10.0f + 0.3f, 0,
				0, 0, 0, 1
		};

	}

	mat4 rotation_matrix_x;
	t *= ROTATION_SPEED;



	if (ROTATION == 1) {
		save_t1 = t - save_t2;
		rotation_matrix_x =
		{
				cos(save_t1 * rotation_speed), 0,-sin(save_t1 * rotation_speed), 0,
				0, 1, 0, 0,
				sin(save_t1 * rotation_speed),0,cos(save_t1 * rotation_speed), 0,
				0, 0, 0, 1
		};
	}
	if (ROTATION == 0) {
		save_t2 = t - save_t1; //save_t2 = 멈춰있던 시간
		float t2 = save_t1 * 1.2f;
		rotation_matrix_x *=
		{
			cos(save_t1* rotation_speed), 0, -sin(save_t1 * rotation_speed), 0,
				0, 1, 0, 0,
				sin(save_t1* rotation_speed), 0, cos(save_t1* rotation_speed), 0,
				0, 0, 0, 1
		};
	}


	mat4 translate_matrix;

	if (ROTATION == 1)
	{
		save_t1 = t - save_t2;
		translate_matrix =
		{
			1, 0, 0, orbit_radius * cos(save_t1 * orbit_speed),
			0, 1, 0, orbit_height,
			0, 0, 1, orbit_radius * sin(save_t1 * orbit_speed),
			0, 0, 0, 1
		};
	}

	else
	{
		save_t2 = t - save_t1; //save_t2 = 멈춰있던 시간
		translate_matrix =
		{
			1, 0, 0, orbit_radius * cos(save_t1 * orbit_speed),
			0, 1, 0, orbit_height,
			0, 0, 1, orbit_radius * sin(save_t1 * orbit_speed),
			0, 0, 0, 1
		};
	}


	model_matrix = translate_matrix*rotation_matrix_x*scale_matrix;


	//속도 바꾸면 회전이 갑자기 점프해버림... 왜지? -> 누적 회전량이라 그런듯
	if (ROTATION_FLAG == 1) {
		ROTATION_FLAG = 0; ROTATION = 1;
	}
}

#endif
