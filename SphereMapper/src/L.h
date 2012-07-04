#pragma once

#include "ofMain.h"
#include "QuadFace.h"
#include "utils.h"

struct L {

	QuadFace *q1;
	QuadFace *q2;
	QuadFace *q3;
	ofVec3f n;
	ofVec3f p1;
	
	void set(ofMesh *m, int o1, int o2, int o3, int i1, int i2, int i3) {

		p1 = getIntersection(m, o1, o2, i2, i3);
		ofVec3f p2 = getIntersection(m, i1, i2, o2, o3);

		n = getNormal(p1, m->getVerticesPointer()[o2], p2);
		q1 = new QuadFace(n, m->getVerticesPointer()[o1], p1, m->getVerticesPointer()[i2], m->getVerticesPointer()[i1]);
		
				
		q3 = new QuadFace(n, p2, m->getVerticesPointer()[o3], m->getVerticesPointer()[i3], m->getVerticesPointer()[i2]);
		
		q2 = new QuadFace(n, p1, m->getVerticesPointer()[o2], p2, m->getVerticesPointer()[i2]);

		
		q1->flipNormals();
		q2->flipNormals();
		q3->flipNormals();
	}

    ofVec3f getNormal(ofVec3f a, ofVec3f b, ofVec3f c) {
        ofVec3f dir = (b-a).getCrossed(c-a);
        return dir.getNormalized();
    }


    void drawEdge(float t, const ofFloatColor &a, const ofFloatColor &b) {
        q2->drawGrow(t, 3, a, b);
        q1->drawSweep90(1.f-t, b, a);
        q3->drawSweep90(1.f-t, b, a);
    }
	
	void drawGrad(float rotation, const ofFloatColor &a, const ofFloatColor &b,const ofFloatColor &c, const ofFloatColor &d) {
		
		
		ofFloatColor ax = q1->fourWayColourLerp(rotation, a, b, c, d);
        ofFloatColor bx = q1->fourWayColourLerp(rotation, b, c, d, a);
        ofFloatColor cx = q1->fourWayColourLerp(rotation, c, d, a, b);
        ofFloatColor dx = q1->fourWayColourLerp(rotation, d, a, b, c);

		
		

		glBegin(GL_TRIANGLE_FAN);
		glNormal3f(n.x, n.y, n.z);
		

		ofSetColor(ax);
		glVertex3f(q1->verts[2].x,q1->verts[2].y,q1->verts[2].z);
		//glColor3f(0, 1, 0);
		

		ofSetColor(bx);
		glVertex3f(q1->verts[3].x,q1->verts[3].y,q1->verts[3].z);		
		
		// 2
		//glColor3f(0, 0, 1);
		
		
		glVertex3f(q1->verts[0].x,q1->verts[0].y,q1->verts[0].z);

		
		glVertex3f(p1.x, p1.y, p1.z);
		
		ofSetColor(cx);
		glVertex3f(q2->verts[1].x,q2->verts[1].y,q2->verts[1].z);

		
		glVertex3f(q3->verts[1].x,q3->verts[1].y,q3->verts[1].z);

		ofSetColor(dx);
		glVertex3f(q3->verts[2].x,q3->verts[2].y,q3->verts[2].z);
		
		glEnd();
	}
	
	void draw(const ofFloatColor &c) {
		q1->draw(c);
		q2->draw(c);
		q3->draw(c);
	}

	 ofVec3f getIntersection(ofMesh *m, int a, int b, int c, int d) {
        ofVec3f aa = m->getVerticesPointer()[a];
        ofVec3f bb = m->getVerticesPointer()[b];
        ofVec3f cc = m->getVerticesPointer()[c];
        ofVec3f dd = m->getVerticesPointer()[d];
        return utils::lineLineIntersection(aa,bb,cc,dd);
    }
    void drawFade(float t, const ofFloatColor &a, const ofFloatColor &b) {
		ofFloatColor c = a * t + b * (1.f-t);
        q1->draw(c);
        q2->draw(c);
        q3->draw(c);
	}
};
