//
//  EditableRect.h
//  CamStrip
//
//  Created by Marek Bereza on 29/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

class EditableRect: public ofRectangle {
public:
	
	
	string name;

	void setup(string name) {
		dragging = false;
		overCorner = false;
		draggingCorner = false;
		this->name = name;
		load();
		setTransform(0, 0, 1);
	}
	void draw() {
		glPushMatrix();
		{
			glTranslatef(pos.x, pos.y, 0);
			glScalef(scale.x, scale.y, 1);
			ofNoFill();
			ofSetHexColor(0xFF0000);
			ofRect(*this);
			if(overCorner) {
				ofCircle(x+width, y+height, 5);
			}
			ofFill();
			ofDrawBitmapString(name, x, y);

		}
		glPopMatrix();
	}
	
	string getFilename() {
		string filename = "rect-"+name+".xml";
		return filename;
	}
	
	
	
	void mouseMoved(float x, float y) {
		ofVec2f m = transform(x, y);
		overCorner = isOverCorner(m);
	}
	
	
	bool mousePressed(float x, float y) {
		ofVec2f m = transform(x, y);
		if(isOverCorner(m)) {
			draggingCorner = true;
			lastMouse = m;
			return true;
			
		} else if(inside(m)) {
			dragging = true;
			lastMouse = m;
			return true;
		}
		return false;
	}
	
	bool mouseDragged(float x, float y) {
		if(draggingCorner) {
			ofVec2f m = transform(x, y);
			ofVec2f delta = m - lastMouse;
			
			this->width += delta.x;
			this->height += delta.y;
			
			lastMouse = m;
			return true;
			
		} if(dragging) {
			ofVec2f m = transform(x, y);
			ofVec2f delta = m - lastMouse;
			
			this->x += delta.x;
			this->y += delta.y;
		
			lastMouse = m;
			return true;
		}
		return false;
	}
	
	void mouseReleased(float x, float y) {
		save();
		dragging = false;
		overCorner = false;
		draggingCorner = false;
	}
	
	// yscale is optional, just set x for proportional scaling.
	void setTransform(float x, float y, float scaleX, float scaleY = -1) {
		this->pos = ofVec2f(x, y);
		this->scale.x = scaleX;
		if(scaleY==-1) {
			this->scale.y = scaleX;
		} else {
			this->scale.y = scaleY;
		}
	}
private:
	
	// these are the transformation parameters
	ofVec2f pos;
	ofVec2f scale;
	
	ofVec2f lastMouse;
	bool dragging;
	bool overCorner;
	bool draggingCorner;
	
	
	bool isOverCorner(ofVec2f &m) {
		return m.distanceSquared(ofVec2f(x+width, y+height))<25;
	}
	
	void save() {
		
		ofxXmlSettings xml;
		xml.addTag("rect");
		xml.addAttribute("rect", "x", (int)x, 0);
		xml.addAttribute("rect", "y", (int)y, 0);
		xml.addAttribute("rect", "width", (int)width, 0);
		xml.addAttribute("rect", "height", (int)height, 0);
		xml.saveFile(getFilename());
	}
	
	void load() {
		ofxXmlSettings xml;
		xml.loadFile(getFilename());
		x = xml.getAttribute("rect", "x", 0);
		y = xml.getAttribute("rect", "y", 0);
		width = xml.getAttribute("rect", "width", 20);
		height = xml.getAttribute("rect", "height", 20);
	}
	
	ofVec2f transform(float x, float y) {
		x -= pos.x;
		y -= pos.y;
		x /= scale.x;
		y /= scale.y;
		return ofVec2f(x, y);
	}
};

