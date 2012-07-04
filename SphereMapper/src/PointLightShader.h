//#ifndef STRINGIFY

//#endif

#include "ofMain.h"
//#define STRINGIFY(A) #A
class PointLightShader {
public:
	ofShader shader;
	
	void setup() {

		shader.load("shader/pointlight.vert", "shader/pointlight.frag");

	}
	void begin() { shader.begin(); }
	void end() { shader.end(); }
};



