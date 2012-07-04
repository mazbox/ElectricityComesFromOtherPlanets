#include "testApp.h"



#include "DepthFBO.h"


DepthFBO depthFbo;
ofCamera light;
ofCamera cam;
ofFbo outputFbo;
ofShader shader;
//--------------------------------------------------------------
void testApp::setup(){
	light.cacheMatrices();
	cam.cacheMatrices();
	glEnable (GL_DEPTH_TEST);
	depthFbo.allocate(1024, 1024);
	outputFbo.allocate(1024, 1024);
	shader.load("shadow.vert", "shadow.frag");
}

void addUniformMatrix(string name, const ofMatrix4x4 &mat) {
	GLint prog = shader.getProgram();
	GLint loc = glGetUniformLocation(prog, name.c_str());
	glUniformMatrix4fv(loc, 1, false, mat.getPtr());
}


void testApp::exit() {

}



//--------------------------------------------------------------
void testApp::update(){
	float angle = ofGetElapsedTimef();
	light.setPosition(20*cos(angle), -15, 20*sin(angle));
	light.lookAt(ofVec3f(0, 0, 0));
	cam.setPosition(10, -10, 10);
	cam.lookAt(ofVec3f(0, 0, 0));
	//light.setNearClip(5);
	//light.setFarClip(70);
	
}

void drawScene() {
	glBegin(GL_QUADS);
	glVertex3f(-10, -1, -10);
	glVertex3f(-10, -1, 10);
	glVertex3f(10, -1, 10);
	glVertex3f(10, -1, -10);
	glEnd();
	
	ofBox(0, -3, 0, 5);
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0);
	glColor3f(1, 1, 1);
	
	//cam.begin();
	//drawScene();
	//cam.end();
	
	depthFbo.begin();
	ofClear(0, 0, 0);
	light.begin(ofRectangle(0, 0, 1024, 1024));
	
	drawScene();
	light.end();
	depthFbo.end();
	
	
	glPolygonOffset( 1.0f, 1.0f );
	glEnable( GL_POLYGON_OFFSET_FILL );
	glClear( GL_DEPTH_BUFFER_BIT );
	
	outputFbo.begin();
	ofClear(0, 0, 0);
	cam.begin(ofRectangle(0, 0, 1024, 1024));
	shader.begin();
	shader.setUniformTexture("depthTexture", depthFbo.getTextureReference(), 0);
	ofVec3f pos = light.getPosition();
	shader.setUniform3f("lightPos", pos.x, pos.y, pos.z);
	addUniformMatrix("shadowTransMatrix", light.getModelViewProjectionMatrix().getInverse());//*cam.getModelViewProjectionMatrix());
	drawScene();
	shader.end();
	cam.end();
	outputFbo.end();
	glDisable( GL_POLYGON_OFFSET_FILL );
	
	depthFbo.draw(0, 0, 256, 256);
	outputFbo.draw(256, 0, 256, 256);
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}