//
//  Midi2OSC.h
//  Midi2OSC
//
//  Created by Marek Bereza on 16/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once 
#include "ofxMidi.h"
#include "ofxOsc.h"

#define HI_NIBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NIBBLE(b) ((b) & 0x0F)

// for visualizing stuff
class Midi2OSCListener {
public:	
	virtual void noteOnBlip() = 0;
	virtual void noteOffBlip() = 0;
	virtual void ccBlip() = 0;
};

class Midi2OSC: public ofxMidiListener {

public:
	~Midi2OSC() {
		deleteMidi();
	}
	
	Midi2OSC(): ofxMidiListener() {
		listener = NULL;
		midiIn = new ofxMidiIn();
	}
	void setup(string host, int port, int midiPort = 0) {
		midiIn->openPort(midiPort);
		//midiIn.openPort(0);
		midiIn->addListener(this);
		
		osc.setup(host, port);
	}
	
	static const int NOTE_ON = 9;
	static const int NOTE_OFF = 8;
	static const int CC = 11;
	
	void reconnectOsc(string host, int port) {
		osc.setup(host, port);
	}
	
	
	void openMidiPort(int midiPort) {
		restartMidi();
		try {
			midiIn->openPort(midiPort);
		} catch(int i) {}
	}
	vector<string> getMidiPorts() {
		restartMidi();
		midiIn->portNames.clear();
		midiIn->listPorts();
		return midiIn->portNames;
	}
	
	void newMidiMessage(ofxMidiEventArgs& eventArgs) {
		int type = HI_NIBBLE(eventArgs.status);
		int chan = LO_NIBBLE(eventArgs.status);
		
		// ignore anything else but note on/off and cc's
		if(type==NOTE_ON || type==NOTE_OFF || type==CC) {
			if(this->listener!=NULL) {
				if(type==NOTE_ON) this->listener->noteOnBlip();
				else if(type==NOTE_OFF) this->listener->noteOffBlip();
				else if(type==CC) this->listener->ccBlip();
			}
			
			// send an osc message
			ofxOscMessage m;
			if(type==NOTE_ON) {
				m.setAddress("/note/on");
			} else if(type==NOTE_OFF) {
				m.setAddress("/note/off");
			} else if(type==CC) {
				m.setAddress("/cc");
			}

			m.addIntArg(chan);
			m.addIntArg(eventArgs.byteOne);
			m.addIntArg(eventArgs.byteTwo);
			
			osc.sendMessage(m);
		}
		//printf("Type: %d   chan: %d   byte 1: %d   byte 2: %d\n", type, chan, eventArgs.byteOne, eventArgs.byteTwo);
	}
	
	void setListener(Midi2OSCListener *listener) {
		this->listener = listener;
	}
	
private:
	Midi2OSCListener *listener;
	ofxMidiIn *midiIn;
	ofxOscSender osc;
	
	void deleteMidi() {
		midiIn->closePort();
		midiIn->removeListener(this);
		delete midiIn;
	}
	
	void restartMidi() {
		deleteMidi();
		midiIn = new ofxMidiIn();
		midiIn->addListener(this);
	}
};