
#include "ofMain.h"

#pragma once

class Moire2 {
public:
    int shapeId;

    void setup(int shapeId) {
        this->shapeId = shapeId;

        img.loadImage("win2/"+ofToString(shapeId)+".png");
        img.setAnchorPercent(0.5, 0.5);
        lastTime = 0;
        rotSpeed = 0;
        rot = 0;
        if(shapeId==4 || shapeId==8) {
        maxRotSpeed = 14;
        } else {
            maxRotSpeed = 5;
        }
    }

    void ping() {
        lastTime = ofGetElapsedTimef();
        rotSpeed = maxRotSpeed;
    }


    void draw() {



    ofEnableBlendMode(OF_BLENDMODE_ADD);

    rot += rotSpeed;
    rotSpeed *= 0.99;
    float t = ofMap(ofGetElapsedTimef() - lastTime, 0, 7, 0, 1, true);


	float s = tricks::animation::easeOutQuint(t);
	//s = s;
	float a = ofMap(s, 0.6, 1, 1, 0, true);

	ofFloatColor f(239.f/255.f, 22.f/255.f, 49.f/255.f);


    s -= a*0.2;
    s = ofMap(s, 0, 1, 0.3, 1, true);

	glPushMatrix();
        if(shapeId==6) glTranslatef(-0.1, 0, 0);
        glScalef(s,-s,s);

        glColor4f(f.r, f.g, f.b, a);
        img.draw(0, 0, 4, 4);
    glPopMatrix();



    glPushMatrix();
 if(shapeId==6) glTranslatef(-0.05, 0, 0);
        glScalef(s,-s,s);
        glRotatef(rot, 0, 0, 1);

        glColor4f(1.f-f.r, 1.f-f.g, 1.f-f.b, a);
        img.draw(0, 0, 4, 4);

    glPopMatrix();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    }

    ofImage img;
    float rot;
    float rotSpeed;
    float maxRotSpeed;
    float lastTime;
};
