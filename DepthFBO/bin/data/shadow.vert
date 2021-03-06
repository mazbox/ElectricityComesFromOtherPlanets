#version 120 
varying vec3		N, V, L;
varying vec4		q;

uniform mat4		shadowTransMatrix;
uniform vec3 lightPos;
void main(void)
{
	vec4 eyeCoord = gl_ModelViewMatrix * gl_Vertex;

	V = normalize( -eyeCoord.xyz );
	L = normalize( lightPos - eyeCoord.xyz );
	N = gl_NormalMatrix * gl_Normal;

	q = shadowTransMatrix * eyeCoord;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

