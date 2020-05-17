#ifndef __TRACKBALL_H__
#define __TRACKBALL_H__
#include "cgmath.h"


// 외부에서 cam 변수를 불러옴. 따라서  main 파일에서 정의된 카메라 이름이 cam 이어야함.
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

	bool	b_tracking = false;
	float	scale;			// controls how much rotation is applied
	mat4	view_matrix0;	// initial view matrix
	vec2	m0;				// the last mouse position

	bool	b_panning = false;
	bool	b_zooming = false;

	vec3 eye0=vec3(0);
	vec3 at0= vec3(0);
	vec3 up0= vec3(0);
	
	trackball( float rot_scale=1.0f ) : scale(rot_scale){}
	bool is_tracking() const { return b_tracking; }
	bool is_panning() const { return b_panning; }
	bool is_zooming() const { return b_zooming; }


	void begin( const mat4& view_matrix, vec2 m );
	void end() { b_tracking = false; }
	mat4 update( vec2 m ) const;

	void begin_panning(const mat4& view_matrix, vec2 m);  //panning
	void end_panning() { b_panning = false; }
	mat4 update_panning(vec2 m) const;

	void begin_zooming(const mat4& view_matrix, vec2 m);  //zooming
	void end_zooming() { b_zooming = false; }
	mat4 update_zooming(vec2 m) const;
};

inline void trackball::begin(const mat4& view_matrix, vec2 m)
{
	b_tracking = true;			// enable trackball tracking
	m0 = m;						// save current mouse position
	view_matrix0 = view_matrix;	// save current view matrix

	eye0 = cam.eye;
	at0 = cam.at;
	up0 = cam.up;
}

inline void trackball::begin_panning(const mat4& view_matrix, vec2 m)
{
	b_panning= true;			// enable trackball tracking
	m0 = m;						// save current mouse position
	view_matrix0 = view_matrix;	// save current view matrix

	eye0 = cam.eye;
	at0 = cam.at;
	up0 = cam.up;
}

inline void trackball::begin_zooming(const mat4& view_matrix, vec2 m)
{
	b_zooming= true;			// enable trackball tracking
	m0 = m;						// save current mouse position
	view_matrix0 = view_matrix;	// save current view matrix

	eye0 = cam.eye;
	at0 = cam.at;
	up0 = cam.up;
}




inline mat4 trackball::update(vec2 m) const  //input  n == npos
{
	// project a 2D mouse position to a unit sphere
	static const vec3 p0 = vec3(0, 0, 1.0f);	// reference position on sphere
	vec3 p1 = vec3(m - m0, 0);					// displacement
	if (!b_tracking || length(p1) < 0.0001f) return view_matrix0;		// ignore subtle movement
	p1 *= scale;														// apply rotation scale
	p1 = vec3(p1.x, p1.y, sqrtf(max(0, 1.0f - length2(p1)))).normalize();	// back-project z=0 onto the unit sphere = p1

	// find rotation axis and angle in world space
	// - trackball self-rotation should be done at first in the world space
	// - mat3(view_matrix0): rotation-only view matrix
	// - mat3(view_matrix0).transpose(): inverse view-to-world matrix
	//vec3 v = mat3(view_matrix0).transpose() * p0.cross(p1);
	vec3 v = p0.cross(p1);

	float theta = asin(min(v.length(), 1.0f));

	// resulting view matrix, which first applies
	// trackball rotation in the world space
	

/*
	cam.eye = eye0 * mat4::rotate(v.normalize(), theta);
	cam.at = at0 * mat4::rotate(v.normalize(), theta);
	cam.up = up0 * mat4::rotate(v.normalize(), theta);
*/
	//cam.eye = eye0 * mat4::translate(eye0) *  mat4::rotate(v.normalize(), theta) * mat4::translate(eye0).transpose();
	
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
	//return view_matrix0 * mat4::rotate(v.normalize(), theta);
}




inline mat4 trackball::update_panning(vec2 m) const
{
	// project a 2D mouse position to a unit sphere
	static const vec3 p0 = vec3(0, 0, 1.0f);	// reference position on sphere
	vec3 p1 = vec3(m - m0, 0);					// displacement
	if (!b_panning || length(p1) < 0.0001f) return view_matrix0;		// ignore subtle movement
	
	p1 *= scale;														// apply rotation scale
	p1 = vec3(p1.x, p1.y, sqrtf(max(0, 1.0f - length2(p1)))).normalize();	// back-project z=0 onto the unit sphere

	// find rotation axis and angle in world space
	// - trackball self-rotation should be done at first in the world space
	// - mat3(view_matrix0): rotation-only view matrix
	// - mat3(view_matrix0).transpose(): inverse view-to-world matrix
	vec3 v = mat3(view_matrix0).transpose() * p0.cross(p1);
	float theta = asin(min(v.length(), 1.0f));

	// resulting view matrix, which first applies
	// trackball rotation in the world space
	
	vec3 up = -1*cam.up;
	vec3 side = -1*((cam.at - cam.eye).cross(cam.up)).normalize();

	cam.eye = eye0 + up * p1.y + side*p1.x;
	cam.at = at0 + up*p1.y + side*p1.x;



	return mat4::look_at(cam.eye, cam.at, cam.up);


	//return  view_matrix0 * mat4::look_at(vec3(0, 0.1f*p1.y,0.01f ), vec3(0 , 0.1f*p1.y, 0), vec3(0, 1, 0))* view_matrix0;// * mat4::rotate(v.normalize(), theta);
}




inline mat4 trackball::update_zooming(vec2 m) const
{
	// project a 2D mouse position to a unit sphere
	static const vec3 p0 = vec3(0, 0, 1.0f);	// reference position on sphere
	vec3 p1 = vec3(m - m0, 0);					// displacement
	if (!b_zooming || length(p1) < 0.0001f) return view_matrix0;		// ignore subtle movement
	p1 *= scale;										


	vec3 towards = (at0 - eye0).normalize();
	
	cam.eye = eye0 + towards * p1.y * 10;



	// resulting view matrix, which first applies
	// trackball rotation in the world space
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
