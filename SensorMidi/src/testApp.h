#pragma once

#include "ofMain.h"
#include "SimpleGui.h"
#include "ofxMidi.h"
#include "ofxOsc.h"
#include "ofxSettings.h"
#include "MixingDesk.h"

#define NUM_TRACKS 8
#define NUM_CLIPS 8
struct NoteOn {
	NoteOn(int channel, int note) {
		this->channel = channel;
		this->note = note;
		this->time = ofGetElapsedTimef();
	}
	float time;
	int channel;
	int note;
};



class testApp : public ofBaseApp, public xmlgui::Listener, public ofxMidiListener {

public:
	MixingDesk mixer;
	void setup();
	void update();
	void draw();
	void exit();
	void newMidiMessage(ofxMidiEventArgs& eventArgs);

	void controlChanged(xmlgui::Control *ctrl);
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	float clipFadeInTime;
	float clipFadeOutTime;

	ofxMidiIn  midiIn;
	ofxMidiOut midiOut;

	ofxOscReceiver cams;

	ofxOscSender r1;
	ofxOscSender r2;
	ofxOscSender r3;
	ofxOscSender r4;
	ofxSettings settings;
	void positionChanged(int track, int position, bool hasActuallyChanged);
	xmlgui::SimpleGui gui;
	int trackClips[NUM_TRACKS];
	float clipVolumes[NUM_TRACKS][NUM_CLIPS];
	float trackVolumes[NUM_TRACKS];
	float sleepVolume;
	int sleepOn;
	void triggerNote(int channel, int note);
	bool learnMode;
	void sendCC(int channel, int cc, float val);
	void sendMidiOverOsc(const unsigned char &channel, const unsigned char &type, const unsigned char &b1, const unsigned char &b2);
	void sendMidiOverOsc(ofxOscSender *r, const unsigned char &channel, const unsigned char &type, const unsigned char &b1, const unsigned char &b2);
	deque<NoteOn> noteOns;
	int getClipCC(int sensorId, int clipIndex);
	float lastTimeSentWinState;
	int winstate;
	bool simulateCrazyWin;
};
