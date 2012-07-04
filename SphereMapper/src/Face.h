//
//  Face.h
//  SphereMapper
//
//  Created by Marek Bereza on 16/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"

class Face {
public:

    void drawFade(float t, const ofFloatColor &a, const ofFloatColor &b) {

        // only draw fades for shapes that are 3-4 sides
        if(verts.size()<3 || verts.size()>4) {
            printf("Face doesn't have 3 or 4 sides\n");
            return;
        }

        if(verts.size()==4) {
            glBegin(GL_QUADS);
        } else {
            glBegin(GL_TRIANGLES);
        }

        ofFloatColor c = a * t + b * (1.f-t);

        ofSetColor(c);
        for(int i = 0; i < verts.size(); i++) {
            norm(norms[i]);
            vert(verts[i]);
        }
        glEnd();
    }
    ofVec3f getNormal(ofVec3f a, ofVec3f b, ofVec3f c) {
        //ofVec3f dir = (b-a).getCrossed(c-a);
        ofVec3f dir = (c-a).getCrossed(b-a);
        return dir.getNormalized();
    }
    void draw(const ofFloatColor &a) {

        // only draw fades for shapes that are 3-4 sides
        if(verts.size()<3 || verts.size()>4) {
            printf("Face doesn't have 3 or 4 sides\n");
            return;
        }

        if(verts.size()==4) {
            glBegin(GL_QUADS);
        } else {
            glBegin(GL_TRIANGLES);
        }


        ofSetColor(a);
        for(int i = 0; i < verts.size(); i++) {
            norm(norms[i]);
            vert(verts[i]);
        }
        glEnd();
    }
    virtual void drawSweepInOut(float pos, const ofFloatColor &a, const ofFloatColor &b) = 0;

    virtual void drawSweep(float pos, const ofFloatColor &a, const ofFloatColor &b) = 0;
	virtual void drawGrad(float pos, const ofFloatColor &a, const ofFloatColor &b, const ofFloatColor &c, const ofFloatColor &d) = 0;

virtual void drawSweep90(float pos, const ofFloatColor &a, const ofFloatColor &b) = 0;


    void flipNormals() {
        for(int i = 0; i < norms.size(); i++) {
            norms[i] = -norms[i];
        }
    }


    vector<ofVec3f> verts;
    vector<ofVec3f> norms;

    void vert(const ofVec3f &v) {
        glVertex3f(v.x, v.y, v.z);
    }

    void norm(const ofVec3f &v) {
        glNormal3f(v.x, v.y, v.z);
    }

    void normAndVert(const ofVec3f &n, const ofVec3f &v) {
        norm(n);
        vert(v);
    }
    void vert(int index) {
        vert(verts[index]);
    }
    void normAndVert(int index) {
        norm(norms[index]);
        vert(verts[index]);
    }
};
