/*
 *  Model.h
 *  emptyExample
 *
 *  Created by Marek Bereza on 06/01/2011.
 *
 */

#pragma once
#include "ofxOBJModel.h"
#include "ofMain.h"
#include "ofxSettings.h"
#include "Node.h"
/**
 * \brief Represents the physical surfaces to project onto in the scene
 */
class Model: public ofNode, public Node { //: public ofNode {
public:
	ofxOBJModel model;
	bool solid;
	bool disableWhite;

	bool editing;
	float scale;

	string name;


	void setEditing(bool editing) {
		this->editing = editing;
		//printf("editing set to %d on model %x\n", editing, this);
	}
	string getName() {
		return name;
	}

	void save() {
		model.save();
	}

	Model(string objPath): ofNode() {
		load(objPath);
		name = objPath;
		scale = 1;
		editing = false;
		solid = false;
	}

	void load(string path) {
		model.load(path);
		ofVec3f a, b;
		model.getBounds(a, b);
		ofVec3f size = b - a;
		printf("bounds: %f %f %f\n", size.x,size.y, size.z);
		// only swap y and z if y is small
		if(size.y*2<size.x) {
			model.swapYZ();
			printf("Auto YZing\n");
		} else {
		printf("Not YZing\n");}

		model.createFlatProjectionTexCoords();

		// only scale the model down if it's really too big.
		if(size.x>25) {
			model.scale(0.01);
		}
	}


	Model() {
		scale = 1;
		disableWhite = false;
		solid = false;
		editing = false;
		model.load(settings.get("model file", "scene.obj"));
	}

	void setScale(float scale) {
		this->scale = scale;
	}

	ofVec3f editPoint;

	void drawOutline() {
		glDisable(GL_DEPTH_TEST);

		if(editing) {
			glPointSize(10);
			ofSetHexColor(0xFF0000);
			glBegin(GL_POINTS);
			glVertex3f(editPoint.x, editPoint.y, editPoint.z);
			glEnd();
			glPointSize(1);
		}
		if(editing) ofSetColor(0,255,0);
		else ofSetColor(255,255,255);
		//if(editing) printf("editing %x\n", this);
		model.draw(false);

	}

	void drawSolid() {
		solid = true;
		disableWhite = true;
		draw();
		disableWhite = false;
		solid = false;
	}

	void customDraw() {
		printf("customDraw\n");
		if(!disableWhite) glColor3f(1,1,1);
		if(editing) {
			ofSetColor(0,255,0);
			printf("editing\n");
		}
		glPushMatrix();
		glScalef(scale, scale, scale);
		model.draw(solid);
		glPopMatrix();
	}



	void drawModel() {
		glPushMatrix();
		glScalef(scale, scale, scale);
		model.draw(true);
		glPopMatrix();

	}

	void applyTransformation() {

		resetTransform();

		move(pos.x, -pos.y, pos.z);
		rotate(rot.y, 1, 0, 0);
		rotate(-rot.x, 0, 1, 0);
		rotate(rot.z, 0, 0, 1);

	}



};
