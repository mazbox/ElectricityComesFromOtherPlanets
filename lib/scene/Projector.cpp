/*
 *  Projector.cpp
 *  emptyExample
 *
 *  Created by Marek Bereza on 06/01/2011.
 *
 */

#include "Projector.h"
#include "constants.h"

Projector::Projector(string name, float x, float y, float width, float height): Viewport(name, x, y, width, height) {
	fov.fovY = 45;
	zNear = (0.01);
	zFar = (1000);
	this->name = name;

	isActive = false;
	rotateThenPosition = false;
	loadSettings();
}

void Projector::customDraw() {
	
	// don't draw if we're drawing through this projector
	if(isActive) return;
//	glScalef(0.1, 0.1, 0.1);
	glColor3f(1, 0, 0);
	ofBox(0, 0, 0, 0.2);
	glBegin(GL_LINES);
	
	//printf("%f %f %f\n", pos.x, pos.y, pos.z);
	
	
	
	float z = -2;
	
	float h = z*atan(ofDegToRad(fov.fovY/2));
	float w = h*width/height;
	
	
	// half it because we're going 0.5 each side
	//w *= 0.5;
	//h *= 0.5;
	
	
//	0.5/tan(ofDegToRad(fov/2));
	
	
	glVertex3f(0, 0, 0);
	glVertex3f(-w, -h, z);
	
	glVertex3f(-w, -h, z);
	glVertex3f(-w, h, z);
	
	glVertex3f(-w, h, z);
	glVertex3f(0, 0, 0);
	
	
	
	glVertex3f(0, 0, 0);
	glVertex3f(w, h, z);
	
	glVertex3f(w, h, z);
	glVertex3f(w, -h, z);
	
	glVertex3f(w, -h, z);
	glVertex3f(0, 0, 0);
	
	glVertex3f(w, -h, z);
	glVertex3f(-w, -h, z);
	
	glVertex3f(-w, h, z);
	glVertex3f(w, h, z);
	
	
	
	glEnd();
}

void Projector::begin() {
	
	ofSetCoordHandedness(OF_RIGHT_HANDED);
	
	// autocalculate near/far clip planes if not set by user
	float nc = zNear, fc = zFar;
	if(zNear == 0 || zFar == 0) {
		float dist = height * 0.5f / tanf(PI * fov.fovY / 360.0f);
		nc = (zNear == 0) ? dist / 100.0f : zNear;
		fc = (zFar == 0) ? dist * 10.0f : zFar;
	}
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	float aspect = width/height;
//	aspect = aspectAdjustment*ofGetWindowSize().x/ofGetWindowSize().y;
	gluPerspective(fov.fovY, aspect, nc, fc);
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(ofMatrix4x4::getInverseOf(getGlobalTransformMatrix()).getPtr());

	// this was ofViewport(x, y, width, height);
	// but changed it because we're drawing to an intermediate fbo now.
	ofViewport(0, 0, width, height);

	isActive = true;
	
	//printf("x: %f   Y: %f   w: %f   h: %f  \n", x, y, width, height);
}

void Projector::end() {
	//ofPopView();
	isActive = false;
	ofSetupScreen();
}