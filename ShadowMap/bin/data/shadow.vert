#version 120 

uniform mat4 lightMat;
varying vec4 projCoord;

void main(){
	
		
	mat4 biasMat = mat4(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);  

	
	gl_TexCoord[0] = biasMat * gl_ProjectionMatrix * lightMat * gl_ModelViewMatrix *  gl_Vertex;
	
	projCoord = lightMat * gl_ModelViewMatrix * gl_Vertex;
	
	gl_Position = ftransform();
}

