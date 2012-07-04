//
//  Node.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once 
#include "ofxSettings.h"
class FoV {
public:
	float fovY;
	FoV() {
		fovY = 60;
	}
};

class Node {
	
public:
	
	
	// these are for the gui
	// and get put into the 
	// matrix when applyTransformation()
	// is called, (usually in update())
	ofVec3f pos;
	ofVec3f rot;
	
	FoV fov;
	
	string filename;
	
	virtual string getName() = 0;
	
	// you need to put this stuff in
	virtual void applyTransformation() = 0; 

	

	
	void loadSettings(string filename = "") {
		updateFilename(filename);
		ofxSettings s;
		s.load(this->filename);
		pos = s.getVec3("pos", pos);
		rot = s.getVec3("rot", rot);
		fov.fovY = s.getFloat("fovy", fov.fovY);
	}
	
	void saveSettings(string filename = "") {
		updateFilename(filename);
		ofxSettings s;
		s.load(this->filename);
		s.set("pos", pos);
		s.set("rot", rot);
		s.set("fovy", fov.fovY);
	}
private:
	void updateFilename(string filename = "") {
		
		if(filename!="") {
			this->filename = filename;
		}
		if(this->filename=="") {
			this->filename = "settings/"+getName() + ".xml";
		}
		
	}
};
// dummy node for gui stuff
class ANode: public Node {
	string getName() { return "dummy"; }
	void applyTransformation() {}
};