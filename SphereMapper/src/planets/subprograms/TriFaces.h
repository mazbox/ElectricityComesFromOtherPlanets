//
//  VolcanoProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PlanetProgram.h"

#pragma once

class TriFace1: public PlanetSubprogram<TriFaceProgram> {
public:
    bool switcheroo;
    Trigger trig;


    void init() {
        trig.setDuration(480.f/112.f);
        switcheroo = false;
    }

    void noteOn(int note) {
        if(note==0) {
            trig.trigger();
            switcheroo ^= true;
        }
    }


    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();


        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;

        if(switcheroo) swapColours(c0, c1);



        p->inner.drawSmoothFan(trig.getValue(t), c0, c1);

        p->bot.drawSmoothFan(trig.getValue(t), c0, c1);

        p->left.drawSmoothFan(trig.getValue(t), c0, c1);
        p->right.drawSmoothFan(trig.getValue(t), c0, c1);





    }



};
class TriFace0: public PlanetSubprogram<TriFaceProgram> {

public:
	void draw(float alpha) {
		float f = ofGetElapsedTimef();
		f /= 4.0;
		f -= (int) f;

        ofFloatColor c0 = p->colours[0];
        ofFloatColor c1 = p->colours[1];
        ofFloatColor c2 = p->colours[2];
        ofFloatColor c3 = p->colours[3];

		//c1.setHue((float)c1.getHue()*0.999*255.f);
		//c1.setBrightness((c1.getBrightness()*0.8));
		c1.r *= 1.2;
		if(c1.r>1) c1.r = 1;
		c1.g *= 0.5;
		c1.b *= 0.5;

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;


		p->bot.drawGrad(f, c0, c1, c2);
        p->left.drawGrad(f, c0, c1, c2);
        p->right.drawGrad(f, c0, c1, c2);

        p->inner.drawGrad(f, c0, c1, c2);

	}
};

class TriFace2: public PlanetSubprogram<TriFaceProgram> {
public:
    bool switcheroo;
    Trigger trig;
    Trigger stab;

    int pos;
    void init() {
        pos = 0;
        trig.setDuration(480.f/112.f);
        stab.setDuration(0.4);
        switcheroo = false;
    }

    void noteOn(int note) {
        if(note==12) {
            trig.trigger();
            switcheroo ^= true;
        } else if(note==16) {
            stab.trigger();
            pos++;
            pos %= 3;
        }
    }


    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();


        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;

        float f = fadeDown(stab.getValue(t));
        p->bot.fan[pos]->drawFade(f, c0, c1);
        p->left.fan[pos]->drawFade(f, c0, c1);
        p->right.fan[pos]->drawFade(f, c0, c1);

        if(switcheroo) swapColours(c0, c1);



        p->inner.drawSmoothFan(trig.getValue(t), c0, c1);


    }



};
class TriFace3: public PlanetSubprogram<TriFaceProgram> {
public:
    bool switcheroo;
    Trigger trig;
    Trigger stab;

    int pos;
    void init() {
        pos = 0;
        trig.setDuration(120.f/112.f);
        stab.setDuration(0.4);
        switcheroo = false;
    }

    void noteOn(int note) {
        if(note==31) {
            trig.trigger();

        } else if(note==28) {
            stab.trigger();
            pos++;
            pos %= 2;
        }
    }


    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();


        ofFloatColor c0 = p->colours[2];
        ofFloatColor c2 = p->colours[0];
        ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;

        float f = fadeDown(stab.getValue(t));
        if(pos==0) {
            p->bot.fan[2]->drawFade(f, c2, c1);
            p->left.fan[2]->drawFade(f, c2, c1);
            p->right.fan[2]->drawFade(f, c2, c1);
            p->bot.fan[0]->drawFade(f, c2, c1);
            p->left.fan[0]->drawFade(f, c2, c1);
            p->right.fan[0]->drawFade(f, c2, c1);
        } else {
            p->bot.fan[pos]->drawFade(f, c0, c1);
            p->left.fan[pos]->drawFade(f, c0, c1);
            p->right.fan[pos]->drawFade(f, c0, c1);
        }




        //if(switcheroo) swapColours(c0, c1);



        p->inner.drawZoom(easeOutBack(trig.getValue(t))*0.5, c0, c1);


    }



};


class TriFace4: public PlanetSubprogram<TriFaceProgram> {
public:

    Trigger triga;
    Trigger trigb;
    Trigger trigc;


    int posa, posb, posc;
    Fan *fans[3];

    void init() {
        posa = posb = posc = 0;
        triga.setDuration(0.5);
        trigb.setDuration(0.3);
        trigc.setDuration(0.4);
        fans[0] = &p->left;
        fans[1] = &p->right;
        fans[2] = &p->bot;

    }

    void noteOn(int note) {
        if(note==40) {
            triga.trigger();
            posa = (posa+1) % 3;
        } else if(note==43) {
            trigb.trigger();
            posb = (posb+1) % 3;
        } else if(note==45) {
            trigc.trigger();
            posc = (posc+1) % 3;
        }
    }


    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();


        ofFloatColor c0 = p->colours[2];
        ofFloatColor c2 = p->colours[0];
        ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;

        float f = fadeDown(triga.getValue(t));
        p->inner.fan[posa]->drawFade(f, c0, c1);

        f = fadeDown(trigb.getValue(t));
        fans[posb]->fan[1]->drawFade(f, c0, c1);

        f = fadeDown(trigc.getValue(t));
        fans[posc]->fan[0]->drawFade(f, c0, c1);
        fans[posc]->fan[2]->drawFade(f, c0, c1);

    }



};


class TriFace5: public PlanetSubprogram<TriFaceProgram> {
public:

    Trigger triga;
    Trigger trigb;
    Trigger trigc;
    Trigger trigd;



    int posa, posb, posc;
    Fan *fans[3];

    void init() {
        posa = posb = posc = 0;
        triga.setDuration(0.5);
        trigb.setDuration(0.3);
        trigc.setDuration(0.3);
        trigd.setDuration(0.4);
        fans[0] = &p->left;
        fans[1] = &p->right;
        fans[2] = &p->bot;

    }

    void noteOn(int note) {
        if(note==48) {
            triga.trigger();
            posa = (posa+1) % 3;
        } else if(note==52) {
            trigb.trigger();
            posb = (posb+1) % 3;
        } else if(note==55) {
            trigc.trigger();
            posc = (posc+1) % 3;
        } else if(note==53) {
            trigd.trigger();
        }
    }


    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();


        ofFloatColor c0 = p->colours[2];
        ofFloatColor c2 = p->colours[0];
        ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;

        float f;
        f = triga.getValue(t);
        p->inner.fan[posa]->drawSlide(easeOutQuint(f), 0, c0, c1);

        f = fadeDown(trigb.getValue(t));
        fans[posb]->fan[1]->drawFade(f, c0, c1);

        f = fadeDown(trigc.getValue(t));
        fans[(posc+2)%3]->fan[0]->drawSlide(getPart(f, 0,0.5),0, c1, c2);
        fans[posc]->fan[2]->drawSlide(getPart(f,0.5, 1), 0, c1, c2);


    }



};

class TriFace6: public PlanetSubprogram<TriFaceProgram> {
public:

    Trigger centTrig[3];
    Trigger outTrig[9];
    TriFace *outs[9];



    int centPos;
    int randPos;
    void init() {
        centPos = 0;
        randPos = 0;

        for(int i = 0; i < 3; i++) {
            outs[i] = p->left.fan[2-i];
            outs[3+i] = p->right.fan[2-i];
            outs[6+i] = p->bot.fan[2-i];
        }


    }

    void noteOn(int note) {
        if(note==60) {
            centTrig[centPos].trigger();
            centPos = (centPos+1) % 3;
        } else if(note==62 || note==64 || note==66 || note==69 || note==71) {
           // int rd = ofRandom(1, 8);
            randPos ++;
            randPos %= 9;
            outTrig[randPos].trigger();
        }

    }


    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();


        ofFloatColor c0 = p->colours[2];
        ofFloatColor c2 = p->colours[0];
        ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;


        for(int i =  0; i < 3; i++) {
            float f;
            f = centTrig[i].getValue(t);
            p->inner.fan[i]->drawSweep(fadeDown(easeOutQuint(f)), c0, c1);
        }

        for(int i =  0; i < 9; i++) {
            float f;
            f = outTrig[i].getValue(t);
            outs[i]->drawFade(fadeDown(easeOutQuint(f)), c0, c1);
        }



    }



};


class TriFace7: public PlanetSubprogram<TriFaceProgram> {
public:

    Trigger centTrig;
    Trigger outTrig[9];
    TriFace *outs[9];



    int randPos;
    void init() {
        randPos = 0;
		centTrig.setDuration(1.5);
        for(int i = 0; i < 3; i++) {
            outs[i] = p->left.fan[2-i];
            outs[3+i] = p->right.fan[2-i];
            outs[6+i] = p->bot.fan[2-i];
        }


    }

    void noteOn(int note) {
        if(note==72) {
            centTrig.trigger();
        } else if(note==74) {
           // int rd = ofRandom(1, 8);
            randPos ++;
            randPos %= 9;
            outTrig[randPos].trigger();
        }

    }


    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();


        ofFloatColor c0 = p->colours[2];
        ofFloatColor c2 = p->colours[0];
        ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;


		float f;
		f = centTrig.getValue(t);
		p->inner.drawZoom(fadeDown(easeOutQuint(f)), c0, c1);


        for(int i =  0; i < 9; i++) {
            float f;
            f = outTrig[i].getValue(t);
            outs[i]->drawSweepInOut(fadeDown(easeOutQuint(f)), c0, c1);
        }



    }



};


class TriFace8: public PlanetSubprogram<TriFaceProgram> {
public:

    Trigger centTrig;
    Trigger outTrig[9];
    TriFace *outs[9];



    int randPos;
    bool switcheroo;
    void init() {
    	switcheroo = false;
        randPos = 0;
		centTrig.setDuration(1.5);
        for(int i = 0; i < 3; i++) {
            outs[i] = p->left.fan[2-i];
            outs[3+i] = p->right.fan[2-i];
            outs[6+i] = p->bot.fan[2-i];
        }


    }

    void noteOn(int note) {
        if(note==84) {
            centTrig.trigger();
            switcheroo ^= true;
        } else if(note==86) {
           // int rd = ofRandom(1, 8);
            randPos ++;
            randPos %= 9;
            outTrig[randPos].trigger();
        }

    }


    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();


        ofFloatColor c0 = p->colours[2];
        ofFloatColor c2 = p->colours[0];
        ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;



        for(int i =  0; i < 9; i++) {
            float f;
            f = outTrig[i].getValue(t);
            outs[i]->drawSweepInOut(fadeDown(easeOutQuint(f)), c0, c1);
        }

        float f;
        if(switcheroo) {
			swapColours(c0,c1);
        }
		f = centTrig.getValue(t);
		p->inner.drawFans(fadeDown(easeOutQuint(f)), c0, c1);




    }



};


