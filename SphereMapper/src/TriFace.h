//
//  TriFace.h
//  SphereMapper
//
//  Created by Marek Bereza on 16/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "Face.h"

// this has nothing to do with the TriFaceProgram
class TriFace: public Face {
public:
    TriFace(ofMesh *mesh, int a, int b, int c) {
        verts.push_back(mesh->getVerticesPointer()[a]);
        verts.push_back(mesh->getVerticesPointer()[b]);
        verts.push_back(mesh->getVerticesPointer()[c]);

        ofVec3f n = getNormal(mesh->getVerticesPointer()[a],mesh->getVerticesPointer()[b],mesh->getVerticesPointer()[c]);

        norms.push_back(n);
        norms.push_back(n);
        norms.push_back(n);


    }

    void drawSweep(float pos, const ofFloatColor &a, const ofFloatColor &b) {
        drawSlide(pos, 0, a, b);
    }
    void drawSweep90(float pos, const ofFloatColor &a, const ofFloatColor &b) {
        drawSlide(pos, 2, a, b);
    }
    void drawSweep180(float pos, const ofFloatColor &a, const ofFloatColor &b) {
        drawSlide(pos, 1, a, b);
    }

    void drawSweepInOut(float pos, const ofFloatColor &a, const ofFloatColor &b) {
    	pos = 1.f - pos;
        if(pos<0.5) {
            drawSweep(pos*2, a, b);
        } else {
            drawSweep((pos-0.5)*2, b, a);
        }
    }
    void drawSlide(float amount, int corner, const ofFloatColor &c0, const ofFloatColor &c1) {
        int a = corner;
        int b, c;
        getOthers(a, b, c);

        ofVec3f ab = verts[a]*(1.f - amount) + verts[b]*amount;
        ofVec3f ac = verts[a] *(1.f - amount) + verts[c]*amount;


        ofSetColor(c0);
        glBegin(GL_TRIANGLES);
        normAndVert(a);
        vert(ab);
        vert(ac);

        ofSetColor(c1);
        vert(ab);
        normAndVert(b);
        normAndVert(c);

        vert(ab);
        vert(ac);
        normAndVert(c);

        glEnd();


    }


    ofFloatColor threeWayColourLerp(float amt, const ofFloatColor &a, const ofFloatColor &b,const ofFloatColor &c) {
        amt *= 3.f;
        if(amt<1.f) {
            return a * (1.f-amt) + b * amt;
        } else if(amt<2.f) {
            amt -= 1.f;
            return b * (1.f-amt) + c *amt;
        } else {
            amt -= 2.f;
            return c * (1.f-amt) + a * amt;
        }
    }
	
	void drawGrad(float pos, const ofFloatColor &a, const ofFloatColor &b, const ofFloatColor &c, const ofFloatColor &d) {
		drawGrad(pos, a, b, c);
	}
    
	void drawGrad(float rotation, const ofFloatColor &a, const ofFloatColor &b,const ofFloatColor &c) {
        glBegin(GL_TRIANGLES);
		float alph = a.a;
        ofFloatColor ax = threeWayColourLerp(rotation, a, b, c);
        ofFloatColor bx = threeWayColourLerp(rotation, b, c, a);
        ofFloatColor cx = threeWayColourLerp(rotation, c, a, b);
		ax.a = alph;
		bx.a = alph;
		cx.a = alph;	
        ofSetColor(ax);
        normAndVert(0);
        ofSetColor(bx);
        normAndVert(1);
        ofSetColor(cx);
        normAndVert(2);

        glEnd();
    }

    void drawFan(float amount, int axis, int from, const ofFloatColor &a, const ofFloatColor &b) {
        glBegin(GL_TRIANGLES);
        ofSetColor(a);
        int other = getOther(axis, from);
        ofVec3f to = verts[from]*(1.f-amount) + verts[other]*amount;
        ofVec3f toN = norms[from]*(1.f-amount) + norms[other]*amount;


        normAndVert(axis);
        normAndVert(from);


        normAndVert(toN, to);


        ofSetColor(b);
        normAndVert(axis);
        normAndVert(toN, to);
        normAndVert(other);
        glEnd();
    }

    // if you give this 1 and 2, it gives you 0,
    // if you give it 0 and 2, it gives you 1,
    // if you give it 1 and 0, it gives you 2
    int getOther(int a, int b) {
        return 3 - (a + b);
    }

    void getOthers(int a, int &b, int &c) {
        if(a==0) {
            b = 1;
            c = 2;
        } else if(a==1) {
            b = 2;
            c = 0;
        } else { //if(a==2) {
            b = 0;
            c = 1;
        }
    }
};
