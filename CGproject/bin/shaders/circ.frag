#ifdef GL_ES
	#ifndef GL_FRAGMENT_PRECISION_HIGH	// highp may not be defined
		#define highp mediump
	#endif
	precision highp float; // default precision needs to be defined
#endif

// inputs from vertex shader
in vec3 tc;	// used for texture coordinate visualization

// output of the fragment shader
out vec4 fragColor;

// shader's global variables, called the uniform variables
uniform bool b_solid_color;
uniform vec4 solid_color;
uniform int TEXTURE_MODE;

void main()
{
	if (TEXTURE_MODE == 0) fragColor = vec4(tc, 1);

		

}