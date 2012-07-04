/**
 *  Stars.cpp
 *
 *  Created by Marek Bereza on 06/06/2012.
 */

#include "Stars.h"


void Stars::setup() {
	for(int i = 0; i < 500; i++) {
		stars.push_back(Star());
	}
	minRad = 2;
	maxRad = 5;
	minBri = 0.7;
	maxBri = 1;
	shimmerAmount = 0.9;
	shimmerFrequency = 0.95;
	img.loadImage("4dust.png");
}

void Stars::update() {
	float currTime = ofGetElapsedTimef();
	float delta = currTime - lastFrame;
	lastFrame = currTime;
	for(int i = 0; i < stars.size(); i++) {
		stars[i].update(delta);
	}
}


void Stars::enliven() {
	for(int i = 0; i < stars.size(); i++) {
		if(stars[i].dead) {
			stars[i].setup();
		}
	}
}

void Stars::flash() {
	int count = 0;
	for(int i = 0; i < stars.size(); i++) {
		if(stars[i].dead) {
			stars[i].setupFast();
			count++;
		}
		if(count>stars.size()/2) break;
	}
}
void Stars::draw() {
	
	
	ofMesh meshToDraw;
	
	meshToDraw.setMode(OF_PRIMITIVE_TRIANGLES);
	//img.bind();
	int numImages = 4;
	float rad = 0.03;
	float radX = 0.01;
	float radY = 0.01;
	float imgOffset = img.getWidth()/((float)numImages);
	float imgH = img.getHeight();
	float t = ofGetElapsedTimef();
	ofFloatColor col(1,1,1,1);
	ofDisableNormalizedTexCoords();
	ofEnableAlphaBlending();
	for(int i = 0; i < stars.size(); i++) {
		if(stars[i].dead) continue;
		rad = 0.016;//ofMap(stars[i].pos.z, 0, MAX_DUST_Z, minRad, maxRad, true);
		
		float off = imgOffset*(i%numImages);
		radX = rad*stars[i].size;
		radY = radX;
		
		col.a = ofMap(stars[i].radius, 0.5, stars[i].maxRadius, maxBri, 0, true);
		col.a = sqrt(col.a);
		
		
	//	if(ofRandomuf()>shimmerFrequency) {
	//		col.a += ofRandom(shimmerAmount*0.5, shimmerAmount);
	//	}
		meshToDraw.addColor(col);
		meshToDraw.addTexCoord(ofVec2f(off, 0)); // top left
		meshToDraw.addVertex(ofVec3f(stars[i].pos.x - radX, stars[i].pos.y - radY));
		
		
		meshToDraw.addColor(col);
		meshToDraw.addTexCoord(ofVec2f(off+imgOffset, 0)); // top right
		meshToDraw.addVertex(ofVec3f(stars[i].pos.x + radX, stars[i].pos.y - radY));
		
		meshToDraw.addColor(col);
		meshToDraw.addTexCoord(ofVec2f(off+imgOffset, imgH)); // bottom right
		meshToDraw.addVertex(ofVec3f(stars[i].pos.x + radX, stars[i].pos.y + radY));
		
		meshToDraw.addColor(col);
		meshToDraw.addTexCoord(ofVec2f(off, 0)); // top left
		meshToDraw.addVertex(ofVec3f(stars[i].pos.x - radX, stars[i].pos.y - radY));
		
		meshToDraw.addColor(col);
		meshToDraw.addTexCoord(ofVec2f(off, imgH)); // bottom left
		meshToDraw.addVertex(ofVec3f(stars[i].pos.x - radX, stars[i].pos.y + radY));
		
		meshToDraw.addColor(col);
		meshToDraw.addTexCoord(ofVec2f(off+imgOffset, imgH)); // bottom right
		meshToDraw.addVertex(ofVec3f(stars[i].pos.x + radX, stars[i].pos.y + radY));
		
	}
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetHexColor(0xFFFFFF);
	img.bind();
	meshToDraw.draw();
	img.unbind();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}