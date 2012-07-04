/**
 * ofxPolygonMask.cpp
 * emptyExample
 *
 * Created by Marek Bereza on 12/03/2011.
 *
 */
#include "QuadMask.h"
#define SQR_DIST_POINT_GRAB 36 // 6 pixels	
#define DIST_POINT_GRAB 6
#include <vector>
QuadMask::QuadMask() {
	filePath = "";

	selectedPoint = lastSelectedPoint = focusedPoint = -1;

	selected = false;
	enabled = false;
	editing = false;

	points.push_back(ofVec2f(120, 0));
	points.push_back(ofVec2f(240, 0));
	points.push_back(ofVec2f(240, 240));
	points.push_back(ofVec2f(120, 240));

	setTransform(0, 0, 320, 240);
	x = 0;
	y = 0;
	width = 320;
	height = 320;
}



void QuadMask::setup(string file) {
	
	if(file=="" && filePath=="") {
		printf("QuadMask: Couldn't write file because no path was specified\n");
		return;
	}
	if(file!="") filePath = file;
	ofxXmlSettings xml;
	xml.loadFile(file);
	xml.pushTag("points");

	int numTags = xml.getNumTags("point");
	for(int i = 0; i < numTags && i < 4; i++) {
		
		points[i] = 
						 ofVec2f(
								 xml.getAttribute("point", "x", 0.f, i),
								 xml.getAttribute("point", "y", 0.f, i)
								 );
	}
	setEnabled(enabled);
	setEnableEditing(editing);
}

void QuadMask::save(string file) {
	if(file=="" && filePath=="") {
		printf("QuadMask: Couldn't write file because no path was specified\n");
		return;
	}
	if(file!="") filePath = file;
	ofxXmlSettings xml;
	xml.addTag("points");
	xml.pushTag("points");
	for(int i = 0; i < points.size(); i++) {
		xml.addTag("point");
		xml.addAttribute("point", "x", points[i].x, i);
		xml.addAttribute("point", "y", points[i].y, i);
	}
	xml.saveFile(filePath);
	
}




void QuadMask::draw(ofEventArgs &args) {

	if(points.size()==0) return;
	
	ofNoFill();
	ofSetColor(255, 0, 0);
	
	// do a normal fill of the inside
	ofBeginShape();
	
	for(int i = 0; i < points.size(); i++) {
		ofVertex(points[i].x, points[i].y);
	}
	
	ofEndShape(true);
	
	ofEnableAlphaBlending();
	
	
	
	if(editing) {
		ofNoFill();
		
		ofSetHexColor(0xFF0000);
		// do a normal fill of the inside
		
		for(int i = 0; i < points.size(); i++) {
			if(i==focusedPoint) ofSetHexColor(0x00FF00);
			else ofSetHexColor(0xFF0000);
			ofCircle(points[i].x, points[i].y, DIST_POINT_GRAB);
		}
		ofFill();
	}
}


int QuadMask::sqrDist(int x1, int y1, int x2, int y2) {
	int distX = x1 - x2;
	int distY = y1 - y2;
	return distX*distX + distY*distY;
}

float QuadMask::distToCentre(ofVec3f a, ofVec3f b, ofVec3f p) {
	ofVec2f c((a.x+b.x)*0.5, (a.y+b.y)*0.5);
	float x = c.x - p.x;
	float y = c.y - p.y;
	return sqrt(x*x + y*y);
	
}


void QuadMask::mousePressed(ofMouseEventArgs &m) {
	
		
	for(int i = 0; i < points.size(); i++) {
		if(sqrDist(m.x, m.y, points[i].x, points[i].y)<SQR_DIST_POINT_GRAB) { // 5 pixels distance
			selectedPoint = i;
			focusedPoint = i;
	

		}
	}
}

void QuadMask::mouseDragged(ofMouseEventArgs &m) {
	if(selectedPoint!=-1) {
		points[selectedPoint].x = m.x;
		points[selectedPoint].y = m.y;	
	}
}

void QuadMask::mouseReleased(ofMouseEventArgs &m) {
	if(selectedPoint!=-1) {
		lastSelectedPoint = selectedPoint;
		selectedPoint = -1;
		save();
		
	}
}


void QuadMask::keyPressed(ofKeyEventArgs &k) {
	if(focusedPoint!=-1) {
		if(k.key==OF_KEY_UP) {
			points[focusedPoint].y--;
		} else if(k.key==OF_KEY_DOWN) {
			points[focusedPoint].y++;
		} else if(k.key==OF_KEY_LEFT) {
			points[focusedPoint].x--;
		} else if(k.key==OF_KEY_RIGHT) {
			points[focusedPoint].x++;
		} else if(k.key==OF_KEY_BACKSPACE) {
			points.erase(points.begin()+focusedPoint);
			focusedPoint = -1;
		}
	}
}

void QuadMask::keyReleased(ofKeyEventArgs &k) {

}







void QuadMask::toggleEditing() {
	setEnableEditing(!editing);
}

void QuadMask::setEnableEditing(bool editing) {
	if(this->editing!=editing) {
		this->editing = editing;
		if(this->editing) {
			// add events
			ofAddListener(ofEvents().keyPressed, this, &QuadMask::keyPressed);
			ofAddListener(ofEvents().keyReleased, this, &QuadMask::keyReleased);
			ofAddListener(ofEvents().mousePressed, this, &QuadMask::mousePressed);
			ofAddListener(ofEvents().mouseDragged, this, &QuadMask::mouseDragged);
			ofAddListener(ofEvents().mouseReleased, this, &QuadMask::mouseReleased);			
		} else {
			// remove events
			ofRemoveListener(ofEvents().keyPressed, this, &QuadMask::keyPressed);
			ofRemoveListener(ofEvents().keyReleased, this, &QuadMask::keyReleased);
			ofRemoveListener(ofEvents().mousePressed, this, &QuadMask::mousePressed);
			ofRemoveListener(ofEvents().mouseDragged, this, &QuadMask::mouseDragged);
			ofRemoveListener(ofEvents().mouseReleased, this, &QuadMask::mouseReleased);
		}
	}
}
bool QuadMask::isEditing() {
	return editing;
}


void QuadMask::toggleEnabled() {
	setEnabled(!enabled);
}

void QuadMask::setEnabled(bool enabled) {
	if(this->enabled!=enabled) {
		this->enabled = enabled;
		if(this->enabled) {
			// add events
			ofAddListener(ofEvents().draw, this, &QuadMask::draw);
		} else {
			// remove events
			ofRemoveListener(ofEvents().draw, this, &QuadMask::draw);
		}
	}
}
bool QuadMask::isEnabled() {
	return enabled;
}


void QuadMask::setTransform(float x, float y, float width, float height) {
	transform.set(x, y, width, height);
}