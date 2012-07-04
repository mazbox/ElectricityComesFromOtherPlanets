#pragma once

#include "ofMain.h"
#include "Midi2OSC.h"
#include "SimpleGui.h"
#include "ofxSettings.h"

class testApp : public ofBaseApp, public Midi2OSCListener, public xmlgui::Listener {

public:
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	void noteOnBlip();
	void noteOffBlip();
	void ccBlip();
	void save();
	void load();
	float lastNoteOnBlipTime, lastNoteOffBlipTime, lastCCBlipTime;
	Midi2OSC midi2osc;
	
	
	// gui stuff
	xmlgui::SimpleGui gui;
	List *midiInputs;
	int selectedMidiInput;
	int oscPort;
	string oscHost;
	void controlChanged(xmlgui::Control *ctrl);
	
	ofxSettings settings;
};
