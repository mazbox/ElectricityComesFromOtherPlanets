#include "testApp.h"
#include "ofxSimpleGuiToo.h"

ofCamera cam;
ofLight light;	
int stepA = 4;
int stepB = 4;
int twist = 5;
//--------------------------------------------------------------
void testApp::setup(){
	gui.addSlider("StepA", stepA, 1, 20);
	gui.addSlider("StepB", stepB, 1, 20);
	gui.addSlider("twist", twist, 1, 20);
	//cam.setFov(45);
//	cam.setFarClip(100);
	//cam.setNearClip(0.1);
	cam.setPosition(0, 0, -10);
	cam.lookAt(ofVec3f(0, 0, 0));
	light.setPosition(5, 5, 5);
	light.enable();
	light.setSpotlight();
	
	ofEnableLighting();
}

//--------------------------------------------------------------
void testApp::update(){

}

void drawShape() {

	float dist = 1;
	vector<vector<ofVec3f> > rings;
	
	for(float a = 0; a < PI*2; a += PI/stepA) {
		ofMatrix4x4 mat;
		mat.glRotate(ofRadToDeg(a), 0, 1, 0);
		mat.glTranslate(2, 0, 0);
		mat.glRotate(ofRadToDeg(a/(float)twist), 0, 0, 1);

		rings.push_back(vector<ofVec3f>());
		
		for(float b = 0; b < PI * 2; b += PI / stepB) {
			ofVec3f p = ofVec3f(dist * cos(b), dist * sin(b), 0);
			p = mat.preMult(p);
			rings.back().push_back(p);
		}
	}
	
	
	
	for(int i = 0; i < rings.size()-1; i++) {
		glBegin(GL_TRIANGLES);
		for(int j = 0; j < rings[i].size()-1; j++) {
			ofVec3f a = rings[i][j];
			ofVec3f b = rings[i+1][j];
			ofVec3f c = rings[i+1][j+1];
			ofVec3f d = rings[i][j+1];
			
			ofVec3f  abcN = (b-a).getCrossed(c-a);
			abcN.normalize();
			glNormal3f(abcN.x, abcN.y, abcN.z);
			glVertex3f(a.x, a.y, a.z);
			glVertex3f(b.x, b.y, b.z);
			glVertex3f(c.x, c.y, c.z);
			
			ofVec3f  acdN = (c-a).getCrossed(d-a);
			acdN.normalize();
			glNormal3f(acdN.x, acdN.y, acdN.z);
			glVertex3f(a.x, a.y, a.z);
			glVertex3f(c.x, c.y, c.z);
			glVertex3f(d.x, d.y, d.z);
			
			//glVertex3f(rings[i][j].x, rings[i][j].y, rings[i][j].z);
			//glVertex3f(rings[i+1][j].x, rings[i+1][j].y, rings[i+1][j].z);
			//glVertex3f(rings[i][j+1].x, rings[i][j+1].y, rings[i][j+1].z);
			
		}
		glEnd();
	}

}


//--------------------------------------------------------------
void testApp::draw(){
	glEnable(GL_DEPTH_TEST);
	ofEnableLighting();
	ofBackground(0, 0, 0);
	ofSetHexColor(0xFFFFFF);
	cam.begin();
	
	glPushMatrix();
	glRotatef(mouseX, 0, 1, 0);
	glRotatef(mouseY, 1, 0, 0);
	
	drawShape();
	
	glPopMatrix();
	
	cam.end();
	ofDisableLighting();
	gui.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key==' ') {
		gui.toggleDraw();
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