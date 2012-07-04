#version 120

uniform sampler2D image;


void main(){
	
	vec4 c = vec4(0.0, 0.0, 0.0, 0.0);
	vec2 tc = gl_TexCoord[0].xy;
	
	
	
	// Suppress the reverse projection.
	if( gl_TexCoord[0].q>0.0) {
		vec4 ProjMapColor = texture2DProj(image, gl_TexCoord[0]);
		
		c += ProjMapColor.x * vec4(1.0, 1.0, 1.0, 1.0);//ProjMapColor;
	}


	
	gl_FragColor = c;			
}

  