//
//  QuadFace.h
//  SphereMapper
//
//  Created by Marek Bereza on 16/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "Face.h"

class QuadFace: public Face {
public:
    QuadFace(ofMesh *mesh, int a, int b, int c, int d) {
        verts.push_back(mesh->getVerticesPointer()[a]);
        verts.push_back(mesh->getVerticesPointer()[b]);
        verts.push_back(mesh->getVerticesPointer()[c]);
        verts.push_back(mesh->getVerticesPointer()[d]);


        ofVec3f n = getNormal(mesh->getVerticesPointer()[a],mesh->getVerticesPointer()[b],mesh->getVerticesPointer()[c]);

        norms.push_back(n);
        norms.push_back(n);
        norms.push_back(n);
        norms.push_back(n);
    }

    QuadFace(const ofVec3f &n, const ofVec3f &a, const ofVec3f &b, const ofVec3f &c, const ofVec3f &d) {
        verts.push_back(a);
        verts.push_back(b);
        verts.push_back(c);
        verts.push_back(d);

        norms.push_back(n);
        norms.push_back(n);
        norms.push_back(n);
        norms.push_back(n);

    }



    ofFloatColor fourWayColourLerp(float amt, const ofFloatColor &a, const ofFloatColor &b,const ofFloatColor &c,const ofFloatColor &d) {
        amt *= 4.f;
        if(amt<1.f) {
            return a * (1.f-amt) + b * amt;
        } else if(amt<2.f) {
            amt -= 1.f;
            return b * (1.f-amt) + c *amt;
        } else if(amt<3.f) {
            amt -= 2.f;
            return c * (1.f-amt) + d * amt;
        } else {
            amt -= 3.f;
            return d * (1.f-amt) + a * amt;
        }
    }
    void drawGrad(float rotation, const ofFloatColor &a, const ofFloatColor &b,const ofFloatColor &c, const ofFloatColor &d) {
        glBegin(GL_QUADS);
        ofFloatColor ax = fourWayColourLerp(rotation, a, b, c, d);
        ofFloatColor bx = fourWayColourLerp(rotation, b, c, d, a);
        ofFloatColor cx = fourWayColourLerp(rotation, c, d, a, b);
        ofFloatColor dx = fourWayColourLerp(rotation, d, a, b, c);

        ofSetColor(ax);
        normAndVert(0);
        ofSetColor(bx);
        normAndVert(1);
        ofSetColor(cx);
        normAndVert(2);
        ofSetColor(dx);
        normAndVert(3);

        glEnd();
    }

    void drawGrow(float pos, int corner, const ofFloatColor &x, const ofFloatColor &y) {
        int a = corner;
        int b = (corner+1) % 4;
        int c = (corner+2) % 4;
        int d = (corner+3) % 4;
        float ipos = 1.f - pos;
        ofVec3f f = verts[a]*ipos + verts[b]*pos;
        ofVec3f g = verts[b]*ipos + verts[c]*pos;
        ofVec3f h = verts[d]*ipos + verts[c]*pos;
        ofVec3f k = verts[a]*ipos + verts[d]*pos;
        ofVec3f e = verts[a]*ipos + verts[c]*pos;


        ofSetColor(x);
        glBegin(GL_QUADS);
        normAndVert(a);
        vert(f);
        vert(e);
        vert(k);

        glEnd();

        ofSetColor(y);
        glBegin(GL_TRIANGLE_FAN);

        normAndVert(norms[0], e);
        vert(f);
        vert(b);
        vert(g);
        vert(c);
        vert(h);
        vert(d);
        vert(k);


        glEnd();
    }


    void drawSweep(float pos, const ofFloatColor &a, const ofFloatColor &b) {
        // 2 quads
        glBegin(GL_QUADS);
        ofSetColor(a);

        ofVec3f mpa = verts[0] *(1.f - pos) + verts[1]*pos;
        ofVec3f mpb = verts[3] *(1.f - pos) + verts[2]*pos;

        ofVec3f mpan = norms[0] *(1.f - pos) + norms[1]*pos;
        ofVec3f mpbn = norms[3] *(1.f - pos) + norms[2]*pos;


        normAndVert(0);

        normAndVert(mpan, mpa);
        normAndVert(mpbn, mpb);
        normAndVert(3);

        ofSetColor(b);

        normAndVert(mpan, mpa);
        normAndVert(1);
        normAndVert(2);
        normAndVert(mpbn, mpb);


        glEnd();
    }
    void drawSweep180(float pos, const ofFloatColor &a, const ofFloatColor &b) {
        // 2 quads
        glBegin(GL_QUADS);
        ofSetColor(a);

        ofVec3f mpa = verts[2] *(1.f - pos) + verts[3]*pos;
        ofVec3f mpb = verts[1] *(1.f - pos) + verts[0]*pos;

        ofVec3f mpan = norms[2] *(1.f - pos) + norms[3]*pos;
        ofVec3f mpbn = norms[1] *(1.f - pos) + norms[0]*pos;


        normAndVert(2);

        normAndVert(mpan, mpa);
        normAndVert(mpbn, mpb);
        normAndVert(1);

        ofSetColor(b);

        normAndVert(mpan, mpa);
        normAndVert(3);
        normAndVert(0);
        normAndVert(mpbn, mpb);


        glEnd();
    }

    void drawSweepInOut(float pos, const ofFloatColor &a, const ofFloatColor &b) {
        if(pos<0.5) {
            drawSweep(pos*2, a, b);
        } else {
            drawSweep((pos-0.5)*2, b, a);
        }
    }

    void drawSweepInOut90(float pos, const ofFloatColor &a, const ofFloatColor &b) {
        if(pos<0.5) {
            drawSweep90(pos*2, a, b);
        } else {
            drawSweep90((pos-0.5)*2, b, a);
        }
    }

    void drawSweepInOut270(float pos, const ofFloatColor &a, const ofFloatColor &b) {
        if(pos<0.5) {
            drawSweep270(pos*2, a, b);
        } else {
            drawSweep270((pos-0.5)*2, b, a);
        }
    }

    void drawSweep90(float pos, const ofFloatColor &a, const ofFloatColor &b) {
        // 2 quads
        glBegin(GL_QUADS);
        ofSetColor(a);

        ofVec3f mpa = verts[1] *(1.f - pos) + verts[2]*pos;
        ofVec3f mpb = verts[0] *(1.f - pos) + verts[3]*pos;

        ofVec3f mpan = norms[1] *(1.f - pos) + norms[2]*pos;
        ofVec3f mpbn = norms[0] *(1.f - pos) + norms[3]*pos;


        normAndVert(1);

        normAndVert(mpan, mpa);
        normAndVert(mpbn, mpb);
        normAndVert(0);

        ofSetColor(b);

        normAndVert(mpan, mpa);
        normAndVert(2);
        normAndVert(3);
        normAndVert(mpbn, mpb);


        glEnd();
    }

	void drawSweep270(float pos, const ofFloatColor &a, const ofFloatColor &b) {
        // 2 quads
        glBegin(GL_QUADS);
        ofSetColor(a);

        ofVec3f mpa = verts[3] *(1.f - pos) + verts[0]*pos;
        ofVec3f mpb = verts[2] *(1.f - pos) + verts[1]*pos;

        ofVec3f mpan = norms[3] *(1.f - pos) + norms[0]*pos;
        ofVec3f mpbn = norms[2] *(1.f - pos) + norms[1]*pos;


        normAndVert(3);

        normAndVert(mpan, mpa);
        normAndVert(mpbn, mpb);
        normAndVert(2);

        ofSetColor(b);

        normAndVert(mpan, mpa);
        normAndVert(0);
        normAndVert(1);
        normAndVert(mpbn, mpb);


        glEnd();
    }



};
