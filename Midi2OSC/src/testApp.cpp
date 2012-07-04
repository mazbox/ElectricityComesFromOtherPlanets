#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0);
	
	
	
	ofSetWindowTitle("Midi2OSC");
	
	lastNoteOnBlipTime = lastNoteOffBlipTime = lastCCBlipTime = -100;
	
	midi2osc.setListener(this);
	ofSetFrameRate(60);
	

	
	midiInputs = (List*)gui.addList("midi input", selectedMidiInput, midi2osc.getMidiPorts());
	gui.addPushButton("Refresh");
	gui.addTextField("OSC Host", oscHost);
	gui.addIntField("OSC Port", oscPort);
	gui.addPushButton("Reconnect");
	
	gui.setEnabled(true);
	gui.addListener(this);
	load();
	midi2osc.setup(oscHost, oscPort);
	if(selectedMidiInput==-1) {
		selectedMidiInput = 0;
	}
	midi2osc.openMidiPort(selectedMidiInput);
}


void testApp::controlChanged(xmlgui::Control *ctrl) {
	if(ctrl->id=="Refresh") {
		string selection = midiInputs->getSelectedString();
		midiInputs->items = midi2osc.getMidiPorts();
		midiInputs->setSelection(selection);
		if(selectedMidiInput>-1) {
			midi2osc.openMidiPort(selectedMidiInput);
		}
	} else if(ctrl->id=="midi input") {
		midi2osc.openMidiPort(selectedMidiInput);
		
	} else if(ctrl->id=="Reconnect") {
		midi2osc.reconnectOsc(oscHost, oscPort);
	}
	save();
}

void testApp::save() {
	settings.set("midiPort", midiInputs->getSelectedString());
	settings.set("oscPort", oscPort);
	settings.set("oscHost", oscHost);
}

void testApp::load() {
	settings.load("settings.xml");
	oscPort = settings.getInt("oscPort", 12345);
	oscHost = settings.get("oscHost", "localhost");
	string mport = settings.get("midiPort", "");
	int foundIndex = -1;
	for(int i = 0; i < midiInputs->items.size(); i++) {
		if(midiInputs->items[i]==mport) {
			foundIndex = i;
		}
	}
	
	// choose which port we want and set selectedMidiInput
	selectedMidiInput = foundIndex;
}


void testApp::noteOnBlip() {
	lastNoteOnBlipTime = ofGetElapsedTimef();
}

void testApp::noteOffBlip() {
	lastNoteOffBlipTime = ofGetElapsedTimef();
}

void testApp::ccBlip() {
	lastCCBlipTime = ofGetElapsedTimef();
}
void testApp::exit() {

}
//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

	float blipHeight = 20;

	float a = ofMap(ofGetElapsedTimef() - lastNoteOnBlipTime, 0, 0.5, 1, 0, true);
	float b = ofMap(ofGetElapsedTimef() - lastNoteOffBlipTime, 0, 0.5, 1, 0, true);
	float c = ofMap(ofGetElapsedTimef() - lastCCBlipTime, 0, 0.5, 1, 0, true);
	
	
	float w3 = ofGetWidth()/3.f;
	glColor3f(a, 0, 0);
	ofRect(0, ofGetHeight()-blipHeight, w3, blipHeight);
	
	glColor3f(0, b, 0);
	ofRect(w3, ofGetHeight()-blipHeight, w3, blipHeight);
	
	glColor3f(0, 0, c);
	ofRect(w3*2, ofGetHeight()-blipHeight, w3, blipHeight);
	
	glColor3f(0, 0, 0);
	ofDrawBitmapString("note on", 5, ofGetHeight() - 5);
	ofDrawBitmapString("note off", 1+w3, ofGetHeight() - 5);
	ofDrawBitmapString("control", 5+w3*2, ofGetHeight() - 5);
	
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