#include "utils.h"
#include <float.h>

ofVec3f utils::lineLineIntersection(ofVec3f p1, ofVec3f p2, ofVec3f p3, ofVec3f p4) {
    ofVec3f pa, pb;
    utils::lineLineIntersectSegment(p1,p2,p3,p4,pa,pb);
    return (pa+pb)/2.f;
}


// from the bourkster.
bool utils::lineLineIntersectSegment(ofVec3f p1, ofVec3f p2, ofVec3f p3, ofVec3f p4, ofVec3f &pa, ofVec3f &pb) {


   float mua = 0;
   float mub = 0;

   ofVec3f p13,p43,p21;

   float d1343,d4321,d1321,d4343,d2121;
   float numer,denom;
   p13 = p1 - p3;
   p43 = p4 - p3;


   if (ABS(p43.x) < FLT_EPSILON && ABS(p43.y) < FLT_EPSILON && ABS(p43.z) < FLT_EPSILON)
      return false;

   p21 = p2 - p1;

   if (ABS(p21.x) < FLT_EPSILON && ABS(p21.y) < FLT_EPSILON && ABS(p21.z) < FLT_EPSILON)
      return false;

   d1343 = p13.x * p43.x + p13.y * p43.y + p13.z * p43.z;
   d4321 = p43.x * p21.x + p43.y * p21.y + p43.z * p21.z;
   d1321 = p13.x * p21.x + p13.y * p21.y + p13.z * p21.z;
   d4343 = p43.x * p43.x + p43.y * p43.y + p43.z * p43.z;
   d2121 = p21.x * p21.x + p21.y * p21.y + p21.z * p21.z;

   denom = d2121 * d4343 - d4321 * d4321;
   if (ABS(denom) < FLT_EPSILON)
      return false;
   numer = d1343 * d4321 - d1321 * d4343;

   mua = numer / denom;
   mub = (d1343 + d4321 * mua) / d4343;

   pa = p1 + p21 * mua;
   pb = p3 + p43 * mub;

   return true;
}


float utils::upDown(float in) {
    if(in<0) return 0;

    if(in>1) return 0;
    if(in<0.5) return in * 2.f;
    else return (1-in)*2.f;
}

float utils::fadeDown(float in) {
	if(in==0) return 0;
	else if(in==1) return 0;
	else return 1.f-in;
}

float utils::fadeUp(float in) {
	if(in==0) return 0;
	else if(in==1) return 0;
	else return in;
}

float utils::getPart(float trig, float from, float to, bool invert) {
	if(trig<from) return 0;
	if(trig>to) return 1;
	if(invert) return 1.f-((trig-from)/(to-from));
	else return (trig - from)/(to - from);
}

void utils::swapColours(ofFloatColor &c0, ofFloatColor &c1) {
	ofFloatColor c = c0;
	c0 = c1;
	c1 = c;
}

ofVec3f utils::getNormal(ofVec3f a, ofVec3f b, ofVec3f c) {
	ofVec3f dir = (b-a).getCrossed(c-a);
	return dir.getNormalized();
}
