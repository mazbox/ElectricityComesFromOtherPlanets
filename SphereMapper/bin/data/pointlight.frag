#version 120

varying vec4 diffuse,ambientGlobal, ambient;
varying vec3 normal,lightDir,halfVector;
varying float dist;

uniform float quadAtt;
uniform float linAtt;
uniform float constAtt;

void main()
{
	
	vec3 n,halfV,viewV,ldir;
	float NdotL,NdotHV;
	vec4 color = ambientGlobal;
	float att;
	// a fragment shader can't write a varying variable, hence we need
	// a new variable to store the normalized interpolated normal 
	n = normalize(normal);
	// compute the dot product between normal and normalized lightdir 

	//float quadAtt = 0.02;
	//float linAtt = 0.1;
	//float constAtt = 0.7;
	NdotL = max(dot(n,normalize(lightDir)),0.0);
	if (NdotL > 0.0) {

		att = 1.0 / (constAtt +
				linAtt * dist +
				quadAtt * dist * dist);
		color += att * (diffuse * NdotL + ambient);
		halfV = normalize(halfVector);

		NdotHV = max(dot(n,halfV),0.0);
		color += att * gl_FrontMaterial.specular * gl_LightSource[0].specular *
						pow(NdotHV,gl_FrontMaterial.shininess);
	}
	

	gl_FragColor = color;
}