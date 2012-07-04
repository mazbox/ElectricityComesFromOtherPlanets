/**     ___           ___           ___                         ___           ___
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/
 *
 *  Description:
 *
 *  MixingDesk.h, created by Marek Bereza on 10/05/2012.
 */


#include "ofMain.h"
#include "ofxMidi.h"

#define GAIN_LINEAR 0
#define GAIN_LOG 1
#define GAIN_SQR 2
#define GAIN_SQRT 3

struct MixerTrack {
	float *value;


	float start;
	float end;
	float fadeStart;
	float fadeEnd;
	MixerTrack() {
	    value = NULL;
        start = end = fadeStart = fadeEnd = 0;
	}
	void print() {
		printf("start: %f     end: %f    fs: %f     fe: %f\n", start, end, fadeStart, fadeEnd);
	}
};

class MixingDesk {
public:
    int gainType;
	void setup(ofxMidiOut *midiOut) {
	    gainType = GAIN_LOG;

		this->midiOut = midiOut;
	}

	void addChannel(int channel, float &value) {
		tracks[channel] = MixerTrack();
		tracks[channel].value = &value;
		lastValues[channel] = -1;
	}


	void update() {
		map<int,MixerTrack>::iterator it;
		float t = ofGetElapsedTimef();
		for(it = tracks.begin(); it != tracks.end(); it++) {
			MixerTrack *tr = &(*it).second;
			if(tr->fadeStart<=t && tr->fadeEnd>=t) {
                //	printf("Fading channel %d\n", (*it).first);
                float *f = tr->value;
                float val = ofMap(t, tr->fadeStart, tr->fadeEnd, tr->start, tr->end, true);
                if(f!=NULL) {
                    *f = val;
                }
			}
		}

		// don't need to send these values constantly!
		for(it = tracks.begin(); it != tracks.end(); it++) {
			// only send when there's a 1% change in volume or more
			if(ABS(lastValues[(*it).first]-*(*it).second.value)>0.01) {
			    //if((*it).first==30) {
                //    printf("Sending values to sleep channel\n");
			   // }
			   int cc = (*it).first;
			   if(cc==63) cc = 100;
				midiOut->sendControlChange(3, cc, ofMap(mapGain(*(*it).second.value), 0, 1, 0, 110, true));
				lastValues[(*it).first] = *(*it).second.value;
			}
		}
	}


	float mapGain(float f) {
	    switch(gainType) {
            case GAIN_LINEAR:
                return f;
            case GAIN_LOG:
                return MAX(0, 1+0.7*log((f)));
            case GAIN_SQR:
                return f*f;
            case GAIN_SQRT:
                return sqrt(f);
            default: return f;
	    }

	}


	void fadeTo(int channel, float value, float time) {
	    if(tracks.find(channel)==tracks.end()) {
	        printf("MixingDesk: %d - no such channel!!!\n", channel);
	        return ;
	    }
		tracks[channel].start = *tracks[channel].value;
		tracks[channel].end = value;
		tracks[channel].fadeStart = ofGetElapsedTimef();
		tracks[channel].fadeEnd = tracks[channel].fadeStart + time;
		//tracks[channel].print();
	}
private:
	ofxMidiOut *midiOut;
	map<int,MixerTrack> tracks;
	map<int, float> lastValues;
};
