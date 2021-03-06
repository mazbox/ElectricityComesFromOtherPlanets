#pragma once
#include "Viewport.h"
#include "ofMain.h"
#include "Node.h"

/** 
 * \brief Represents an actual projector in the scene 
 * Started using ofNode, but not complete - rotation isn't implemented yet.
 */
class Projector: public Viewport, public Node {
public:
	string getName() {
		return name;
	}
	
	Projector(string name, float x, float y, float width, float height);
	void positionView();
	

	void update() {
		applyTransformation();
	}
	
	void customDraw();

	void begin();
	
	void end();
	
	// it's easier to position the camera if you rotate
	// it at the origin then move it back from that point
	// rather than positioning it then rotating it, but
	// we'll have the option to do both.
	bool rotateThenPosition;
public:


	
	void applyTransformation() {

		resetTransform();
		if(rotateThenPosition || true) {
			
			
			
			rotate(rot.y, 1, 0, 0);
			rotate(-rot.x, 0, 1, 0);
			rotate(rot.z, 0, 0, 1);
			
			ofVec3f p = pos;
			p.rotate(rot.y, ofVec3f(1, 0, 0));
			p.rotate(-rot.x, ofVec3f(0, 1, 0));
			p.rotate(rot.z, ofVec3f(0, 0, 1));
			setPosition(p);
			
			
			//			move(pos.x, -pos.y, pos.z);
		} else {
			move(pos.x, -pos.y, pos.z);
			rotate(rot.y, 1, 0, 0);
			rotate(-rot.x, 0, 1, 0);
			rotate(rot.z, 0, 0, 1);
		}		
	}
	

	float zNear;
	float zFar;
private:
	bool isActive;
};