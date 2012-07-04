//
//  TowersProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "PlanetProgram.h"

#pragma once


class TowersProgram: public PlanetProgram {
public:

    struct Tower {
        Face *in;
        Face *out;
        QuadFace *up;
        QuadFace *down;
		
		void drawGrad(float rotation, const ofFloatColor &a, const ofFloatColor &b, const ofFloatColor &c, const ofFloatColor &d) {
			up->drawGrad(rotation, a, b, c, d);
			down->drawGrad(rotation, a, b, c, d);
			in->drawGrad(rotation, a, b, c, d);
			out->drawGrad(rotation, a, b, c, d);
		}
        void draw(const ofFloatColor &c) {
            in->draw(c);
            out->draw(c);
            up->draw(c);
            down->draw(c);
        }
        void drawFadeInner(float amt, const ofFloatColor &a, const ofFloatColor &b) {
            in->drawFade(amt, a, b);
            out->draw(b);
            up->draw(b);
            down->draw(b);
        }

        void drawFadeOuter(float amt, const ofFloatColor &a, const ofFloatColor &b) {
            out->drawFade(amt, a, b);
            in->draw(b);
            up->draw(b);
            down->draw(b);
        }
        void drawFade(float a1, float a2, float a3, float a4, const ofFloatColor &a, const ofFloatColor &b) {
            in->drawFade(a1, a, b);
            out->drawFade(a2, a, b);
            up->drawFade(a3, a, b);
            down->drawFade(a4, a, b);
        }
        void drawFade(float a1, float a2, float a3, float a4, const ofFloatColor &a, const ofFloatColor &b, const ofFloatColor &c) {
            in->drawFade(a1, a, b);
            out->drawFade(a2, a, b);
            up->drawFade(a3, c, b);
            down->drawFade(a4, c, b);
        }
        void drawFadeSweep(float a1, float a2, float a3, float a4, const ofFloatColor &a, const ofFloatColor &b, const ofFloatColor &c, bool sweepDir = false) {
            in->drawFade(a1, a, b);
            out->drawFade(a2, a, b);
            if(sweepDir) {
                up->drawSweep(a3, b, c);
                down->drawSweep(a4, b, c);
            } else {
                up->drawSweep(a3, c, b);
                down->drawSweep(a4, c, b);
            }
        }
        void drawFadeSweep90(float a1, float a2, float a3, float a4, const ofFloatColor &a, const ofFloatColor &b, const ofFloatColor &c, bool sweepDir = false) {
            in->drawFade(a1, a, b);
            out->drawFade(a2, a, b);
            if(sweepDir) {
                up->drawSweep90(a3, b, c);
                down->drawSweep90(a4, b, c);
            } else {
                up->drawSweep90(a3, c, b);
                down->drawSweep90(a4, c, b);
            }
        }

    };



    QuadFace *top;
    QuadFace *bot;
    QuadFace *left;
    QuadFace *right;

    Tower lMid, rMid, lOut, rOut;



	void constructGeometry();
	void initializeSubprograms();

};
