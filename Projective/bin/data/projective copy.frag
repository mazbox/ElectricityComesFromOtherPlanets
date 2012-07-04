#version 120

uniform sampler2D image;
uniform float diffuse,ambient, specular, shininess;
varying vec3 normal,lightDir,halfVector, eyeVec;
/*
void main(){
	
	vec4 c = vec4(0.0, 0.0, 0.0, 0.0);

		// Suppress the reverse projection.
		if( gl_TexCoord[0].q>0.0 ) {
			vec4 ProjMapColor = texture2DProj(image, gl_TexCoord[0]);
			c += ProjMapColor;
		}
  
	gl_FragColor = c;			
}

  
  
  */
void main(){
	
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	
	float lambertTerm = dot(N,L);
  
	vec4 c = vec4(ambient, ambient, ambient, ambient);
	
	if(lambertTerm > 0.0) {	
		c += diffuse * lambertTerm;	
		
		vec3 E = normalize(eyeVec);
		vec3 R = reflect(-L, N);
		float spec = pow( max(dot(R, E), 0.0), shininess );
						 
		c += specular * spec;
		
		
		// Suppress the reverse projection.
		if( gl_TexCoord[0].q>0.0 ) {
			vec4 ProjMapColor = texture2DProj(image, gl_TexCoord[0]);
			c += ProjMapColor*lambertTerm;
		}
	}
  
	gl_FragColor = c;			
}

  