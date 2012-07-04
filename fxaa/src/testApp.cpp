#include "testApp.h"
ofFbo fbo;
ofShader fxaa;
bool rotating = false;
bool shading = false;
ofLight light;

//--------------------------------------------------------------
void testApp::setup(){
	light.setDirectional();
	ofEnableArbTex();
	fbo.allocate(ofGetWidth()*2, ofGetHeight()*2);
	fxaa.load("v002.FXAA.vert","v002.FXAA.frag");
	ofSetFrameRate(30);
}

//--------------------------------------------------------------
void testApp::update(){

}
float t = 0;
//--------------------------------------------------------------
void testApp::draw(){
	ofEnableLighting();
	light.enable();
	if(rotating) t++;
	fbo.begin();
	glColor4f(1, 1, 1, 1);
	ofClear(0, 0, 0, 0);
	
	glPushMatrix();
	glScalef(2, 2, 2);
	glTranslatef(ofGetWidth()/2, ofGetHeight()/2, 0);
	glRotatef(t, 0, 1, 1);
	/*glBegin(GL_QUADS);
	glVertex2f(-100, -100);
	glVertex2f(100, -100);
	glVertex2f(100, 100);
	glVertex2f(-100, 100);
	
	glEnd();*/
	ofBox(0, 0, 0, 100);
	glPopMatrix();
	fbo.end();
	
	ofDisableLighting();

	if(shading) {
		fxaa.begin();
		fxaa.setUniformTexture("bgl_RenderedTexture", fbo.getTextureReference(0), 0);
		fxaa.setUniform1f("bgl_RenderedTextureWidth", fbo.getWidth());
		fxaa.setUniform1f("bgl_RenderedTextureHeight", fbo.getHeight());
	} else {
		fbo.getTextureReference(0).bind();
	}
	glBegin(GL_QUADS);
	
	glTexCoord2f(0, 0);
	glVertex2f(0, 0);
	
	glTexCoord2f(fbo.getWidth(), 0);
	glVertex2f(ofGetWidth(), 0);
	
	glTexCoord2f(fbo.getWidth(), fbo.getHeight());
	glVertex2f(ofGetWidth(), ofGetHeight());
	
	glTexCoord2f(0, fbo.getHeight());
	glVertex2f(0, ofGetHeight());
	
	glEnd();

	if(shading) {
		fxaa.end();
	} else {
		fbo.getTextureReference(0).unbind();
	}

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='g') shading ^= true;
	if(key=='h') rotating ^= true;
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