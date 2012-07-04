#version 120 

uniform float diffuse,ambient;
varying vec3 normal,lightDir,halfVector,eyeVec;
uniform vec3 lightPos;

uniform mat4 TexGenMat;
uniform mat4 InvViewMat;
uniform float mat[16];
uniform float scale;
uniform vec3 trans;
uniform float m0, m1, m2, m3,
				m4, m5, m6, m7,
				m8, m9, m10, m11,
				m12, m13, m14, m15;

void main(){

	
	// first transform the normal into eye space and normalize the result 
	normal = gl_NormalMatrix * gl_Normal;
	
	lightDir = lightPos;//(vec4(lightPos, 1.0)*gl_ModelViewMatrixInverse).xyz;
	mat4 biasMat =mat4(0.5,0.0,0.0,0.0,0.0,0.5,0.0,0.0,0.0,0.0,0.5,0.0,0.5,0.5,0.5,1.0);  

	
	
	mat4 textureMat=mat4(
			m0, m1, m2, m3, 
			m4, m5, m6, m7, 
			m8, m9, m10, m11, 
			m12, m13, m14, m15

	);
	

	
	vec4 posEye =  gl_ModelViewMatrix * gl_Vertex;
	vec4 posWorld = gl_ModelViewMatrixInverse * posEye;
	
	gl_TexCoord[0] =  textureMat * posWorld;


	
	eyeVec = -posEye.xyz;
	halfVector = (eyeVec+lightDir)/2.0;
	gl_Position = ftransform();

}


/*

#version 120 

uniform float diffuse,ambient;
varying vec3 normal,lightDir,halfVector,eyeVec;
uniform vec3 lightPos;

uniform mat4 TexGenMat;
uniform mat4 InvViewMat;
uniform float scale;
uniform vec2 trans;
void main(){

	
	// first transform the normal into eye space and normalize the result 
	normal = normalize(gl_NormalMatrix * gl_Normal);
	
	lightDir = normalize(lightPos);
	
	mat4 textureMat=mat4(
			scale, 0.0, 0.0, 0.0, 
			0.0, scale, 0.0, 0.0,
			0.0, 0.0, scale, 0.0,
			0.5, 0.5, 0.5, 1.0);
			
	vec4 posEye =  gl_ModelViewMatrix * gl_Vertex;
	vec4 posWorld = gl_ModelViewMatrixInverse * posEye;
	
	gl_TexCoord[0] = textureMat * posWorld;

	
	
	eyeVec = -posEye.xyz;
	
	
	
	
	

	// Normalize the halfVector to pass it to the fragment shader 
	halfVector = (eyeVec+lightDir)/2.0;
	

	
	gl_Position = ftransform();

}


*/