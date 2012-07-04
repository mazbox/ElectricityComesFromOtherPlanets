#include "testApp.h"
#include "ofxSettings.h"

float lastTimeSent;
//------------------------------------------------------------
void testApp::setup(){
	lastTimeSent = ofGetElapsedTimef();
	for(int i = 0; i < 8; i++) {
		rawVals[i] = 0;
		vals[i] = 0;
		lastVals[i] = -1;
	}
	settings.load("osc.xml");
	osc1.setup(settings.get("oscHost1", "localhost"), settings.getInt("oscPort", 24680));
	osc2.setup(settings.get("oscHost2", "localhost"), settings.getInt("oscPort", 24680));
}

//--------------------------------------------------------------
void testApp::update(){
	if(ofGetElapsedTimef()-lastTimeSent>0.3) { // once a 1/3 of second
		lastTimeSent = ofGetElapsedTimef();

		ofxOscMessage m1;
		ofxOscMessage m2;

		m1.setAddress("/sensor/1");
		m2.setAddress("/sensor/2");

		for(int i = 0; i < 8; i++) {
			if(i<4) {
				m1.addIntArg(vals[i]);
			} else {
				m2.addIntArg(vals[i]);
			}
			lastVals[i] = vals[i];
		}
		osc1.sendMessage(m1);
		osc2.sendMessage(m2);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	//ofEnableAlphaBlending();
	ofBackground(22, 33, 44);

	float colWidth = (float)ofGetWidth()/(float)8.f;
	float rowHeight = (float) ofGetHeight()/ 9.f;

	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 9; j++) {
			if(j==8) {
				ofSetHexColor(0x000000);
			} else {
			    float a = ofMap(j, 0, 8, 0.2, 0.01);
				glColor3f(a, a, a);
			}
			ofRect(i*colWidth, j*rowHeight, colWidth, rowHeight);
			ofNoFill();
			glColor4f(1,1,1,0.4);
			ofRect(i*colWidth, j*rowHeight, colWidth, rowHeight);

			ofFill();
		}
	}
	for(int i = 0; i < 8; i++) {
		ofSetHexColor(0xFFFFFF);

		ofDrawBitmapString("#"+ofToString(i+1)+":"+ofToString(vals[i]), i*colWidth+3, 15);

		ofSetHexColor(0xFFFFAA);
		ofLine(colWidth*i, 0, colWidth*i, ofGetHeight());
		ofSetHexColor(0xFF6666);
		float v = ofMap(rawVals[i], 0, 9, ofGetHeight(), 0);
		ofLine(colWidth*i, v, colWidth*(i+1), v);
	}

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
	mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	// no tomfoolery please.
	if(x<0 || y<0 || x>ofGetWidth()-1 || y>ofGetHeight()-1) return;
	float colWidth = (float)ofGetWidth()/8.f;
	float rowHeight = (float)ofGetHeight()/9.f;
	int which = x/colWidth;

	rawVals[which] = (float) (ofGetHeight() - y) / rowHeight;
	if(rawVals[which]>=8.9) rawVals[which] = 8.9;
	vals[which] = rawVals[which]; // truncate

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	mousePressed(x, y, button);
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
