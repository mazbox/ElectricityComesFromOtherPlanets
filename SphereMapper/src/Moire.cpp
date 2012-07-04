/**
 *  Moire.cpp
 *
 *  Created by Marek Bereza on 18/06/2012.
 */

#include "Moire.h"


ofImage *Moire::bg = NULL;

#include "tricks/animation/animation.h"

void Moire::setup(int shapeId) {

    if(bg==NULL) {
        bg = new ofImage();
        bg->loadImage("bg.png");
        bg->setAnchorPercent(0.5,0.5);

    }

    lastTime = 0;
    rotSpeed = 0;
    lastBgPing = 0;
    rot = 0;
    maxRotSpeed = 10;
    img.loadImage("win/"+ofToString(shapeId)+".png");

    img.setAnchorPercent(0.5, 0.5);


}

void Moire::ping() {
    rotSpeed = maxRotSpeed;
    pingBg();
    lastTime = ofGetElapsedTimef();
}

void Moire::pingBg() {
 lastBgPing = ofGetElapsedTimef();
}



void Moire::draw() {




    ofEnableBlendMode(OF_BLENDMODE_ADD);
    float bgA = ofMap(ofGetElapsedTimef()-lastBgPing, 0, 2, 0,1, true);

    if(bgA<0.1) bgA = ofMap(bgA, 0, 0.1, 0, 1);
    else bgA = ofMap(bgA, 0.1, 1.0, 1.0, 0.0);
    if(bgA>0) {
        glColor4f(1,1,1,bgA);
        bg->draw(0, 0, 5,5);
    }

    rot += rotSpeed;
    rotSpeed *= 0.99;
    float t = ofMap(ofGetElapsedTimef() - lastTime, 0, 16, 0, 1, true);


	float s = tricks::animation::easeOutQuint(t);
	float a = ofMap(s, 0.6, 1, 1, 0, true);

	ofFloatColor f(239.f/255.f, 22.f/255.f, 49.f/255.f);


    s -= a*0.2;
    s = ofMap(s, 0, 1, 0.2, 1);

	glPushMatrix();
        glScalef(s,-s,s);

        glColor4f(f.r, f.g, f.b, a);
        img.draw(0, 0, 3.5, 3.5);
    glPopMatrix();



    glPushMatrix();

        glScalef(s,-s,s);
        glRotatef(rot, 0, 0, 1);

        glColor4f(1.f-f.r, 1.f-f.g, 1.f-f.b, a);
        img.draw(0, 0, 3.5, 3.5);

    glPopMatrix();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}
