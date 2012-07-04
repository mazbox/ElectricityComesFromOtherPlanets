#include "testApp.h"

#define TRACK_1_CHANNEL 21
#define SLEEP_CHANNEL 30
#define HI_NIBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NIBBLE(b) ((b) & 0x0F)

bool simulateWinState = false;
//--------------------------------------------------------------
void testApp::setup(){
	simulateCrazyWin = false;
	lastTimeSentWinState = 0;
	winstate = 0;
	ofSetFrameRate(30);
	settings.load("settings.xml");
	ofBackground(0);
	gui.setEnabled(true);
	for(int i = 0; i < NUM_TRACKS; i++) {

		gui.addSegmented("track clip " + ofToString(i+1), trackClips[i], "OFF|1|2|3|4|5|6|7|8");
	}

	gui.addSegmented("Fade Shape", mixer.gainType, "LIN|LOG|SQR|SQRT");
	clipFadeInTime = 0.4;
	clipFadeOutTime = 1.2;
	gui.addSlider("Clip Fade In Time", clipFadeInTime, 0.2, 3);
	gui.addSlider("Clip Fade Out Time", clipFadeOutTime, 0.2, 3);
	gui.addToggle("Simulate win state", simulateWinState);
	gui.addToggle("Simulate crazy win", simulateCrazyWin);
	gui.addColumn();
	for(int i = 0; i < NUM_TRACKS; i++) {
		for(int j = 0; j < NUM_CLIPS; j++) {
			clipVolumes[i][j] = 0.5;
		}
		gui.addSliderBank("clip volumes " + ofToString(i+1), clipVolumes[i], NUM_CLIPS);
	}

	gui.addPushButton("sync noteon");
	gui.addColumn();
	for(int i = 0; i < NUM_TRACKS; i++) {
		trackVolumes[i] = 0;
		gui.addSlider("track volume " + ofToString(i+1), trackVolumes[i], 0, 1);//->width = 300;
	}
	gui.addSlider("sleep volume", sleepVolume, 0, 1);
	gui.addSegmented("sleep on", sleepOn, "off|on");
	sleepOn = 0;
	learnMode = false;
	gui.addToggle("Learn mode", learnMode);

	gui.addListener(this);
	midiOut.listPorts();
	int outPort = 0;
	for(int i = 0; i < midiOut.portNames.size(); i++) {
        string s = midiOut.portNames[i];
        s = ofToLower(s);
        if(s.find("midi yoke")!=-1 && s.find("2")==-1) {
            outPort = i;            break;
        }
	}
	midiOut.openPort(outPort);

	printf("Outputting to %d (%s)\n", outPort, midiOut.portNames[outPort].c_str());
	midiIn.listPorts();
	int inPort = 0;
	for(int i = 0; i < midiIn.portNames.size(); i++) {
        string s = midiIn.portNames[i];
        s = ofToLower(s);
        if(s.find("midi yoke")!=-1 && s.find("2")!=-1) {
            inPort = i;
            break;
        }
	}
	printf("inputting from  %d (%s)\n", inPort, midiIn.portNames[inPort].c_str());
	midiIn.openPort(inPort);
	midiIn.addListener(this);

	int renderPort = settings.getInt("renderport", 12345);
	cams.setup(settings.getInt("camport", 24680));

	r1.setup(settings.get("render1", "192.168.0.5"), renderPort);
	r2.setup(settings.get("render2", "192.168.0.6"), renderPort);
	r3.setup(settings.get("render3", "192.168.0.7"), renderPort);
	r4.setup(settings.get("render4", "192.168.0.8"), renderPort);

	mixer.setup(&midiOut);
	for(int i = 0; i < NUM_TRACKS; i++) {
		for(int j = 0; j < NUM_CLIPS; j++) {
			clipVolumes[i][j] = 0;
			int channel = getClipCC(i+1, j);

			mixer.addChannel(channel, clipVolumes[i][j]);
			mixer.fadeTo(channel, 0, 0.5);
		}
	}


	//for(int i = 0; i < NUM_TRACKS; i++) {
	//	mixer.addChannel(TRACK_1_CHANNEL+i, trackVolumes[i]);
	//	mixer.fadeTo(TRACK_1_CHANNEL+i, 0, 3);
	//}
	mixer.addChannel(SLEEP_CHANNEL, sleepVolume);
	mixer.fadeTo(SLEEP_CHANNEL, 1, 3);

}


void testApp::exit() {
	midiOut.closePort();
}



void testApp::controlChanged(xmlgui::Control *ctrl) {

	string trackClipName = "track clip ";
	if(ctrl->id.find(trackClipName)==0) {
		int sensorId = ofToInt(ctrl->id.substr(trackClipName.size()));
		//printf("Firing clip %d to %d\n", sensorId, ctrl->getInt());
		//triggerClip(sensorId, ctrl->getInt());
		//triggerNote(sensorId, 36 + ctrl->getInt());

	}
	if(ctrl->id=="sleep on") {
		triggerNote(9, 36 + ctrl->getInt());
	}
	/*
	string onName = "on";
	if(ctrl->id.find(onName)==0) {
		int sensorId = ofToInt(ctrl->id.substr(onName.size()));

		switchSensor(sensorId, ctrl->getBool());

	}*/

	if(ctrl->id=="sync noteon") {
		triggerNote(10, 36);
	}
	string trackVolumeName = "track volume ";
	string clipVolumeName = "clip volumes ";
	if(ctrl->id.find(trackVolumeName)==0) {
		int sensorId = ofToInt(ctrl->id.substr(trackVolumeName.size()));
	//	printf("Setting track %d volume to %f\n", sensorId, ctrl->getFloat());
		//moveSensor(sensorId, ctrl->getFloat());
		//sendCC(3, 20+sensorId, ctrl->getFloat());
	} else if(ctrl->id.find(clipVolumeName)==0) {
		int sensorId = ofToInt(ctrl->id.substr(clipVolumeName.size()));

		SliderBank *sb = (SliderBank*) ctrl;
		if(sb->lastSliderTouched>=0 && sb->lastSliderTouched<8) {
		//	printf("Want to change clip volume %d on channel %d\n", sb->lastSliderTouched, sensorId);
			int cc  = getClipCC(sensorId, sb->lastSliderTouched);
			if(cc==63) cc = 100;
			sendCC(3, cc, sb->getFloatArray()[sb->lastSliderTouched]);
		}
	}
	if(ctrl->id=="sleep volume") {
		sendCC(3, 30, ctrl->getFloat());
	}
	/*
	if(ctrl->id=="BG Loop Note") {
		startBGClip();
	}*/
}

int testApp::getClipCC(int sensorId, int clipIndex) {
	return 32+(sensorId-1)*8 + clipIndex;
}

void testApp::sendCC(int channel, int cc, float val) {
	int v = ofMap(val, 0, 1, 0, 127);
	//printf("Sending cc %d  to %d\n", cc, v);
	midiOut.sendControlChange(channel,cc, v);
}

void testApp::triggerNote(int channel, int note) {
	midiOut.sendNoteOn(channel, note, 127);
	noteOns.push_back(NoteOn(channel, note));
}

#define _MIDI_NOTE_ON 9
#define _MIDI_NOTE_OFF 8
#define _MIDI_CC 11



void testApp::sendMidiOverOsc(ofxOscSender *r, const unsigned char &channel, const unsigned char &type, const unsigned char &b1, const unsigned char &b2) {
   // printf("maybe\n");
	if(type==_MIDI_NOTE_ON) {
	//    printf("yes\n");
		ofxOscMessage m;
		m.setAddress("/note/on");
		m.addIntArg(channel);
		m.addIntArg(b1);
		//m.addIntArg(b2);

		r->sendMessage(m);
	}


}
void testApp::sendMidiOverOsc(const unsigned char &channel, const unsigned char &type, const unsigned char &b1, const unsigned char &b2) {

	int chan = channel - 8;
	//printf("sending midi %d %d\n", chan, b1);
	// TODO: check the octave here to see if we need to bother sending.
	/*if(chan>=1 && chan<=8) {

		// check whether to send.
		sendMidiOverOsc(&r1, chan, type, b1, b2);
		sendMidiOverOsc(&r2, chan, type, b1, b2);
		sendMidiOverOsc(&r3, chan, type, b1, b2);
		sendMidiOverOsc(&r4, chan, type, b1, b2);
	}*/


	//printf("Receiving on channel %d\n", channel);
	switch(chan) {
		case 1:
		case 2:
			sendMidiOverOsc(&r1, chan, type, b1, b2);
			break;
		case 3:
		case 4:
			sendMidiOverOsc(&r2, chan, type, b1, b2);
			break;

		case 5:
		case 6:
			sendMidiOverOsc(&r3, chan, type, b1, b2);
			break;
		case 7:
		case 8:
			sendMidiOverOsc(&r4, chan, type, b1, b2);
			break;


	}
}
void testApp::newMidiMessage(ofxMidiEventArgs& eventArgs) {



	unsigned char status = eventArgs.status;
	unsigned char channel = eventArgs.channel;//LO_NIBBLE(status);
	unsigned char type = HI_NIBBLE(status);
	//printf("status: %x  channel %d\n", status, channel);
	if(type==_MIDI_NOTE_ON) {// || type==_MIDI_NOTE_OFF || type==_MIDI_CC) {

		if(channel==9 && (eventArgs.byteOne==96 || eventArgs.byteOne==98)) {
            if(eventArgs.byteOne==98) {

            // do mini win state.
            for(int i = 0; i < NUM_TRACKS; i++) {
                int prev = -1;
                if(i>0) prev = trackClips[i-1];

                int next = 0;
                if(i<NUM_TRACKS-1) next = trackClips[i+1];

                if((trackClips[i]==prev || trackClips[i]==next) && trackClips[i]!=0) {
                    // send mini win state
                    ofxOscMessage m;
                    m.setAddress("/mini");
                    m.addIntArg(i+1);
                    switch(i) {
                        case 0:
                        case 1:
                            r1.sendMessage(m);
                            break;
                        case 2:
                        case 3:
                            r2.sendMessage(m);
                            break;
                        case 4:
                        case 5:
                            r3.sendMessage(m);
                            break;
                        case 6:
                        case 7:
                            r4.sendMessage(m);
                            break;
                    }
                }

            }


            } else if(eventArgs.byteOne==96) {
			// winstate
			int val = trackClips[0];
			bool allTheSame = true;
			bool allOn = true;
			for(int i = 1; i < NUM_TRACKS; i++) {
				if(val!=trackClips[i]) {
					allTheSame = false;
				}
				if(trackClips[i]==0) {
					allOn = false;
				}
			}

			bool winning = ((allTheSame && (val==1 || val==2 || val==7 || val==8)) || allOn) || simulateWinState;
			int winstateType = 0;

			if(allTheSame && (val==1 || val==2 || val==7 || val==8)) {
				winstateType = 2;
			} else if(allOn) {
				winstateType = 1;
			}

			if(simulateCrazyWin) {
				winstateType = 2;
			}


			// we only want to tick winstates 0 and 1 on 96 and 98, and then winstates 2 and 3 on all

			if((winstateType==2 ) || (winstateType<=1 && eventArgs.byteOne!=100)) {
				if(winning) {
					if(winstateType>=2) {
						winstate += ofRandom(1, 8);
					}
					winstate %= 8;
					winstate++;
				} else {
					winstate = 0;
				}


				ofxOscMessage m;
				m.setAddress("/winstate");

				m.addIntArg(winstate);
				m.addIntArg(winstateType);

				r1.sendMessage(m);
				r2.sendMessage(m);
				r3.sendMessage(m);
				r4.sendMessage(m);
				printf("winstate %d %d\n", winstate,winstateType);

			}
            }


		} else {


			sendMidiOverOsc(channel, type, eventArgs.byteOne, eventArgs.byteTwo);
		}
	}

	//printf("midi in: chan: %d   status: %x    b1: %x  b2: %x  timestamp: %f\n", eventArgs.channel, eventArgs.status, eventArgs.byteOne, eventArgs.byteTwo, eventArgs.timestamp);
}

void testApp::positionChanged(int track, int position, bool hasActuallyChanged) {
        if(hasActuallyChanged) {
            bool allOff = true;
            for(int i = 0; i < NUM_TRACKS; i++) {
                if(trackClips[i]!=0) {
                    allOff = false;
                }
            }


            if(allOff) {
            //	printf("All off, going to sleep\n");
                for(int i = 0; i < NUM_TRACKS; i++) {
                    for(int j = 0; j < NUM_CLIPS; j++) {
                        mixer.fadeTo(getClipCC(i+1, j), 0, 1);
                    }
                }

                mixer.fadeTo(SLEEP_CHANNEL, 1, 1);

            } else {

                // fade out sleep
                if(sleepVolume>0.1) {
                    mixer.fadeTo(SLEEP_CHANNEL, 0, 1);
                }


                if(clipVolumes[track][position-1]<0.9 && position>0) {
                //	printf("This happens\n");
                    for(int j = 0; j < NUM_CLIPS; j++) {
                        if(j+1==position) {
                    //		printf("Fading track %d pos %d to 1\n", track, position);
                            mixer.fadeTo(getClipCC(track+1, j), 1, clipFadeInTime);
                        } else {
                //			printf("Fading track %d pos %d to 0\n", track, position);
                            mixer.fadeTo(getClipCC(track+1, j), 0, clipFadeOutTime);
                        }
                    }

                } else if(position==0) {
                    for(int j = 0; j < NUM_CLIPS; j++) {
                        mixer.fadeTo(getClipCC(track+1, position-1), 0, clipFadeOutTime);
                    }
                }

            }

        }
	//}
	// send the position change to the renders
	ofxOscMessage m;
	m.setAddress("/sensor/position");
	m.addIntArg(track+1);
	m.addIntArg(position);

	//printf("Sending /sensor/position to all renders %d %d\n", track, position);
	r1.sendMessage(m);
	r2.sendMessage(m);
	r3.sendMessage(m);
	r4.sendMessage(m);
}

int camstripToTrack(int camstrip) {
	return camstrip;
}
//--------------------------------------------------------------
void testApp::update(){

	ofSetWindowTitle(
					 "SensorMidi - " + ofToString(ofGetWindowWidth())
					 + " x " + ofToString(ofGetWindowHeight())
					 + " - " + ofToString(ofGetFrameRate(), 2));


	ofxOscMessage m;
	while(cams.hasWaitingMessages()) {
		cams.getNextMessage(&m);
		int offset = 0;
		if(m.getAddress()=="/sensor/1") { // cameras 1!
			offset = 0;
		} else if(m.getAddress()=="/sensor/2") { // camera 2!
			offset = 4;
		} else {
			printf("Getting invalid OSC addresses in cam data\n");
		}
		if(!learnMode) {

			for(int i = 0; i < 4; i++) {
				int val = m.getArgAsInt32(i);

                bool actually = trackClips[camstripToTrack(i+offset)]!=val;
				trackClips[camstripToTrack(i+offset)] = val;
				//if(trackClips[camstripToTrack(i+offset)]!=val) {
                positionChanged(camstripToTrack(i+offset), val, actually);
				//}
			}


			for(int i = 0; i < NUM_TRACKS; i++) {
			    if(trackClips[i]==0) {
                    for(int j = 0; j < NUM_CLIPS; j++) {
                        if(clipVolumes[i][j]>0.9) {
                            mixer.fadeTo(getClipCC(i+1, j), 0, clipFadeOutTime);
                        }
                    }
			    }
            }
		}
	}

	if(!learnMode) {
		mixer.update();
	}

	while(!noteOns.empty() && ofGetElapsedTimef() - noteOns.front().time>0.1) {
		midiOut.sendNoteOn(noteOns.front().channel, noteOns.front().note, 0);
		noteOns.pop_front();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
   // ofxOscMessage m;
   // m.setAddress("/key/");
   // r1.sendMessage(m);
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
