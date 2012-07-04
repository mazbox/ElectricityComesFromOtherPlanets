#pragma once

#include "ofMain.h"


namespace utils{
    bool lineLineIntersectSegment(ofVec3f p1, ofVec3f p2, ofVec3f p3, ofVec3f p4, ofVec3f &pa, ofVec3f &pb);
    ofVec3f lineLineIntersection(ofVec3f p1, ofVec3f p2, ofVec3f p3, ofVec3f p4);
	float fadeDown(float in);

    float fadeUp(float in);
	float upDown(float in);
    float getPart(float trig, float from, float to, bool invert = false);

    void swapColours(ofFloatColor &c0, ofFloatColor &c1);

    ofVec3f getNormal(ofVec3f a, ofVec3f b, ofVec3f c);
}
