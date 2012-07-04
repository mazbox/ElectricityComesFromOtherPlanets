/*
 *  Light.h
 *  Render
 *
 *  Simple subclass of ofLight for nicer custom drawing.
 * 
 *  Created by Marek Bereza on 07/03/2011.
 *
 */
#pragma once

#include "Node.h"
class Light: public ofLight, public Node {
public:
	
	Light(string name): ofLight() {
		this->name = name;
		loadSettings();
	}
	
	string name;
	
	string getName() { return name; }
	void customDraw() {
		ofNoFill();
		ofSetHexColor(0xFFFF00);
		ofBox(0, 0, 0, 0.2);
		ofFill();
	}
	
	virtual void applyTransformation()
	{
	 
	 resetTransform();
	 
	 move(pos.x, -pos.y, pos.z);
	 rotate(rot.y, 1, 0, 0);
	 rotate(-rot.x, 0, 1, 0);
	 rotate(rot.z, 0, 0, 1);
	 
	 }
	 
};