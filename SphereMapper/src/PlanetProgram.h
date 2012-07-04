//
//  Program.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "Model.h"

// constants
#include "Colours.h"
#include "MidiNotes.h"

// shapes
#include "QuadFace.h"
#include "TriFace.h"
#include "Fan.h"
#include "Ladder.h"
#include "L.h"
#include "utils.h"
#include "Light.h"

// timing
#include "Trigger.h"
#include "tricks/animation/animation.h"
#include "PlanetSubprogram.h"
#include "utils.h"
#include "Stars.h"
#include "Moire.h"
#include "Moire2.h"

using namespace utils;
using namespace tricks::animation;


class PlanetProgram {
public:
	Model *model;
	ofVboMesh *mesh;
	Light *light;

	Stars stars;
	Moire moire;
    Moire2 moire2;
	ofFloatColor colours[5];

	PlanetSubprogramInterface *subprograms[9];

	virtual ~PlanetProgram() {}
	int position;
	int winState;
	int lastWinState;
	float lastTimePositionChanged;
	int lastPosition;
	float lastTimePersonEntered;
    int shapeId;

    void setWinState(int winState, int winMode) {
        if(winState>0) pingWinState();
        lastWinState = this->winState;
        this->winState = winState;
        for(int i = 0; i < 5; i++) {
            if(winState==0) {
                if(position==0) {
                    // this also prevents white on the sleep state
                    targetColours[i] = Colours::get(shapeId, i);
                } else {
                    targetColours[i] = Colours::get(position, i);
                }
            } else {
                targetColours[i] = Colours::get(1+((shapeId+winState-1)%8), i);
            }
        }
    }

	void init(int shapeId) {
	    winState = 0;
	    lastWinState = 0;
	    this->shapeId = shapeId;
		position = 0;
		lastTimePersonEntered = 0;
		constructGeometry();
		initializeSubprograms();
		for(int i = 0; i <= 8; i++) {
			subprograms[i]->setParent(this);
			subprograms[i]->init();
		}
		stars.setup();
		moire.setup(shapeId);
		moire2.setup(shapeId);
	}


    void pingWinState() {
        moire.ping();
    }


	virtual void constructGeometry() = 0;
	virtual void initializeSubprograms() = 0;

    virtual void positionChanged() {}

	void noteOn(int note) {
		if(getLastPositionAlpha()>0) {
			subprograms[lastPosition]->noteOn(note);

		}
		subprograms[position]->noteOn(note);
	}


	virtual void noteOff(int note) {}
	virtual void cc(int type, int val) {}


	void keyPressed(int key) {
		subprograms[position]->keyPressed(key);
	}

	float getLastPositionAlpha() {
		return ofMap(ofGetElapsedTimef(), lastTimePositionChanged, lastTimePositionChanged+1, 1, 0, true);
	}


	void update() {
		if(getLastPositionAlpha()>0) {
			subprograms[lastPosition]->update();
		}
		subprograms[position]->update();
		stars.update();

		//printf("Position: %d    winstate: %d\n", position, winState);
	}


	void moveLight(float x, float y, float z) {
       // light->pos.x = x;
		//light->pos.y = y;
		//light->pos.z = z;
	}

	virtual void drawPre() {
		glDisable(GL_DEPTH_TEST);
		ofDisableLighting();
		{
			float f = ofGetElapsedTimef()-lastTimePersonEntered;
			float dur = 0.5;
			f /= dur;

			/*if(f<1) {

				glPushMatrix();

				f = easeOutQuad(f);
				float t = ofMap(f, 0, 1, 1.2, 1);
				float a = ofMap(f, 0, 1, 1, 0);
				glScalef(t,t,t);
				glColor4f(1,1,1,a);
				model->drawModel();
				glPopMatrix();
				glColor4f(0, 0, 0, 1);
				model->drawModel();


			}*/
			moire.draw();
			moire2.draw();
			stars.draw();
		}
		glEnable(GL_DEPTH_TEST);
		ofEnableLighting();
	}
	virtual void drawPost() {}

    void pingMiniWinState() {
        moire2.ping();
    }
	void draw() {



//		glDisable(GL_CULL_FACE);
		model->transformGL();
		this->drawPre();
		glEnable(GL_DEPTH_TEST);
		float la = getLastPositionAlpha();

        if(shapeId!=3 && shapeId!=5 && shapeId!=7) {
            glPushMatrix();
                glTranslatef(0, 0, -0.01);
                ofSetHexColor(0);
                glScalef(model->scale, model->scale, model->scale);
                model->model.draw(true);
            glPopMatrix();
        }
		//ofEnableBlendMode(OF_BLENDMODE_ADD);
		if(la>0) {
			glPushMatrix();
			glTranslatef(0, 0, -0.005);

			subprograms[lastPosition]->draw(la);
			glPopMatrix();
		}
		//ofEnableBlendMode(OF_BLENDMODE_ADD);
		subprograms[position]->draw(1.f - la);

		this->drawPost();
		model->restoreTransformGL();

	}

    ofFloatColor targetColours[5];

    void setPosition(int position) {
        if(position==this->position) return;
		if(this->position==0 && position!=0) {
			lastTimePersonEntered = ofGetElapsedTimef();
			stars.enliven();
			moire.pingBg();
		} else if(position!=0) {
			stars.flash();
		}

		lastTimePositionChanged = ofGetElapsedTimef();
		this->lastPosition = this->position;
        this->position = position;
        if(winState==0) {
            for(int i = 0; i < 5; i++) {
                if(position==0) {

                    // this stops white happening in the sleep state
                    targetColours[i] = Colours::get(shapeId, i);
                } else {
                    targetColours[i] = Colours::get(position, i);
                }
            }
        }
        positionChanged();
    }




    void setModel(Model *model) {
		this->model = model;
		mesh = model->model.getVboMesh();
	}


    void updateProgram() {
        // lerp colour here
        float d = 0.95;
        if(winState) {// lerp faster if it's the win state
            d = 0.85;
        }
        for(int i = 0; i < 5; i++) {
            colours[i] = targetColours[i] * (1.f-d) + colours[i] * d;
        }

        update();
    }



    void drawShaded() {
        ofSetHexColor(0xFFFFFF);
        model->transformGL();
		{
			glScalef(model->scale, model->scale, model->scale);
			model->model.draw(true);
			//mesh->drawFaces();
		}
		model->restoreTransformGL();
    }
	void drawOutline() {
        //ofSetHexColor(0x00FF00);
        model->transformGL();
		{
			glScalef(model->scale, model->scale, model->scale);
			//model->model.draw(false);
			model->drawOutline();
			//mesh->drawFaces();
		}
		model->restoreTransformGL();
    }




    ofVec3f &mp(int i) {
        return mesh->getVerticesPointer()[i];
    }


    QuadFace *createQuadFace(const ofVec3f &a, const ofVec3f &b, const ofVec3f &c, const ofVec3f &d) {
        ofVec3f n = getNormal(a,b,c);
        return new QuadFace(n,a,b,c,d);
    }



    ofVec3f getIntersection(int a, int b, int c, int d) {
        ofVec3f aa = mesh->getVerticesPointer()[a];
        ofVec3f bb = mesh->getVerticesPointer()[b];
        ofVec3f cc = mesh->getVerticesPointer()[c];
        ofVec3f dd = mesh->getVerticesPointer()[d];
        return utils::lineLineIntersection(aa,bb,cc,dd);
    }


	void drawDebug() {
		ofDisableLighting();
		model->transformGL();
		{

			ofVec3f *v = mesh->getVerticesPointer();
			int numVertices = mesh->getNumVertices();

			glBegin(GL_TRIANGLES);
			for(int i = 0; i < numVertices; i+=3) {
				ofFloatColor c = Colours::get(i%Colours::size(), 2);
				glColor4f(c.r, c.g, c.b, 0.3);
				for(int j = 0; j < 3; j++) {
					glVertex3f(v[i+j].x, v[i+j].y, v[i+j].z);
				}
			}

			glEnd();

			ofSetHexColor(0xFFFFFF);
			mesh->drawWireframe();



			ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);



			for(int i = 0; i < numVertices; i+=3) {


				int triNum = i/3;
				ofVec3f centre = (v[i] + v[i+1] + v[i+2])/3.f;
				ofDrawBitmapString(ofToString(triNum), centre);
				for(int j = 0; j < 3; j++) {
					ofDrawBitmapString(ofToString(i+j), centre*0.2 + v[i+j]*0.8);
				}
			}


		}
		model->restoreTransformGL();
	}

};
