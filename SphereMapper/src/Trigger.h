//
//  Trigger.h
//  SphereMapper
//
//  Created by Marek Bereza on 16/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

class Trigger {


public:

	Trigger() {
		setDuration(1);
		time = -100;
	}


	void setDuration(float duration) {
		this->duration = duration;
	}


	void trigger(float currTime = -1) {
		if(currTime==-1) this->time = ofGetElapsedTimef();
		else this->time = currTime;
	}

	float getValue(float currTime = -1) {
		if(currTime==-1) currTime = ofGetElapsedTimef();
		float val = (currTime - time)/duration;
		if(val>1) {
            return 1;
        } else {
            return val;
        }

	}



private:
	float time;
	float duration;
};
