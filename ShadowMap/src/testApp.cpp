#include "testApp.h"
#include "ofxSimpleGuiToo.h"
bool enableShader = false;

ofVec3f pos;
ofVec3f rot;
float floorY = 0;
float stageRot = 0;
bool lightsEyeView = false;

ofMatrix4x4 lightMat;
ofMatrix4x4 cameraMat;


ofShader depthShader;
ofShader shadowShader;
ofImage image;

ofFbo shadowMap;
//--------------------------------------------------------------
void testApp::setup(){
	
	ofDisableArbTex();
	
		
	shadowMap.allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F);
	
	//ofDisableSetupScreen();
	ofBackground(0,0,0);
	ofSetFrameRate(60);
	
	gui.addToggle("Enable shader", enableShader);
	
	gui.addSlider("pos.x", pos.x, -1, 1);
	gui.addSlider("pos.y", pos.y, -1, 5);
	gui.addSlider("pos.z", pos.z, -4, 4);
	
	gui.addSlider("rot.x", rot.x, -180, 180);
	gui.addSlider("rot.y", rot.y, -180, 180);
	gui.addSlider("rot.z", rot.z, -180, 180);
	gui.addSlider("floor.y", floorY, -1, 1);
	gui.addSlider("stageRot", stageRot, -180, 180);
	gui.addToggle("lightsEyeView", lightsEyeView);
	gui.loadFromXML();
	gui.setAutoSave(true);
	//ofDisableSetupScreen();
	
	image.loadImage("image.jpg");
	//image.getTextureReference().setTextureWrap(GL_REPEAT, GL_REPEAT);
	image.getTextureReference().setTextureWrap(GL_CLAMP, GL_CLAMP);
	depthShader.load("depth.vert", "depth.frag");
	shadowShader.load("shadow.vert", "shadow.frag");
	
}




void addUniformMatrix(ofShader &shad, string name, const ofMatrix4x4 &mat) {
	GLint prog = shad.getProgram();
	GLint loc = glGetUniformLocation(prog, name.c_str());
	glUniformMatrix4fv(loc, 1, false, mat.getPtr());
 
}




//--------------------------------------------------------------
void testApp::update(){
	
	ofVec3f lookVec = ofVec3f() - pos;
	
	lookVec = ofVec3f(0, 0, -1);
	lookVec.rotate(rot.y, ofVec3f(1, 0, 0));
	lookVec.rotate(-rot.x, ofVec3f(0, 1, 0));
	lookVec.rotate(rot.z, ofVec3f(0, 0, 1));
	
	cameraMat.makeIdentityMatrix();
	cameraMat.rotate(stageRot, 0, 1, 0);
	cameraMat.translate(0,0, -3);
	
	ofVec3f rightVec = lookVec.getCrossed(ofVec3f(0, 1, 0));
	ofVec3f upVec = rightVec.getCrossed(lookVec);
	lightMat.makeLookAtViewMatrix(pos, pos + lookVec, upVec);
}


void drawFloor(bool filled) {
	if(filled) {
		glBegin(GL_QUADS);
	} else {
		glBegin(GL_LINE_LOOP);
	}
	glVertex3f(-1, floorY, -1);
	glVertex3f(1, floorY, -1);
	glVertex3f(1, floorY, 1);
	glVertex3f(-1, floorY, 1);
	glEnd();
	
	if(filled) {
		glBegin(GL_QUADS);
	} else {
		glBegin(GL_LINE_LOOP);
	}

	glVertex3f(0, floorY+0.4, -1);
	glVertex3f(1, floorY+0.4, -1);
	glVertex3f(1, floorY+0.4, 1);
	glVertex3f(0, floorY+0.4, 1);
	
	glEnd();
}


void drawAxes() {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();
}


void drawCamera() {
	drawAxes();
	glColor3f(1, 0, 0);
	ofBox(0, 0, 0, 0.2);
	glBegin(GL_LINES);
	glNormal3f(0, 1, 0);
	
	float h = 2;
	float w = h;
	
	w *= 0.4;
	h *= 0.4;
	
	float z = -1;
	glVertex3f(0, 0, 0);
	glVertex3f(-w, -h, z);
	
	glVertex3f(-w, -h, z);
	glVertex3f(-w, h, z);
	
	glVertex3f(-w, h, z);
	glVertex3f(0, 0, 0);
	
	
	
	glVertex3f(0, 0, 0);
	glVertex3f(w, h, z);
	
	glVertex3f(w, h, z);
	glVertex3f(w, -h, z);
	
	glVertex3f(w, -h, z);
	glVertex3f(0, 0, 0);
	
	glVertex3f(w, -h, z);
	glVertex3f(-w, -h, z);
	
	glVertex3f(-w, h, z);
	glVertex3f(w, h, z);
	
	
	
	glEnd();

}

void drawScene(bool filled) {
	drawFloor(filled);
	if(!filled) {
		ofNoFill();
	}
	ofSphere(0, 0, 0, 0.1);
	ofSphere(0, -0.2, 0, 0.1);
	ofSphere(0.2, -0.2, 0, 0.1);
	ofBox(0.5, 0, 0.5, 0.1);
	ofBox(1.0, -0.3, 0.5, 0.1);
	ofBox(1.5, -0.4, 0.5, 0.2);
	ofBox(0, 0, 0.4, 0.3);
	ofBox(0.5, -2, 0.5, 0.4);
	if(!filled) {
		ofFill();
	}
}
void setupProjection() {
	glEnable(GL_DEPTH_TEST);
	
	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
	
	glViewport( 0, 0, ofGetWidth(), ofGetHeight() );
	
	glMatrixMode( GL_PROJECTION );   // Select the projection matrix
	glLoadIdentity();                // and reset it
	
	
	// Calculate the aspect ratio of the view
	gluPerspective( 45.0f, (float)ofGetWidth() / (float)ofGetHeight(),
					   0.1f, 1000.0f );
		
	
}


//--------------------------------------------------------------
void testApp::draw(){
	shadowMap.begin();
	{
		ofClear(0, 0, 0, 0);
		setupProjection();
	
		glMatrixMode( GL_MODELVIEW );    // Select the modelview matrix
		glLoadIdentity();
	
		glLoadMatrixf(lightMat.getPtr());

		depthShader.begin();
		
		glColor3f(1, 1, 1);
		drawScene(true);
	

		depthShader.end();
	}
	shadowMap.end();
	
	

	setupProjection();
	
	shadowShader.begin();
	{
		
		shadowShader.setUniformTexture("depth", shadowMap, 0);
		addUniformMatrix(shadowShader, "lightMat", lightMat);
		
		glMatrixMode( GL_MODELVIEW );    // Select the modelview matrix
		glLoadIdentity();
	
		glLoadMatrixf(cameraMat.getPtr());
		glColor3f(1, 1, 1);
		drawScene(true);
	}
	shadowShader.end();
	
	
	

	glPushMatrix();
	// put the light into the scene
	glMultMatrixf(lightMat.getInverse().getPtr());
	drawCamera();
	glPopMatrix();

	

	ofSetupScreen();
	glColor3f(1, 1, 1);
	if(lightsEyeView) shadowMap.getTextureReference(0).draw(0, 0);
	glDisable(GL_DEPTH_TEST);
	if(gui.isOn()) {
		gui.draw();
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key==' ') {
		gui.toggleDraw();
	} else {
		
	}
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