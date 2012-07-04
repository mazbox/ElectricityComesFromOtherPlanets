#version 120


void main(){
	
	vec4 c = vec4(gl_FragCoord.z, gl_FragCoord.z, gl_FragCoord.z, gl_FragCoord.z);
	
	gl_FragColor = c;			
}

  