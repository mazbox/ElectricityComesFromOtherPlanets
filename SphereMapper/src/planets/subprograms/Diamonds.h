//
//  VolcanoProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PlanetProgram.h"

#pragma once

class Diamond1: public PlanetSubprogram<DiamondProgram> {
public:
    Trigger triga;
    Trigger trigb;
    void init() {
        triga.setDuration(1);
        trigb.setDuration(0.3);
    }

    void noteOn(int note) {
        if(note==1) {
            triga.trigger();

        } else if (note==0) {
            trigb.trigger();
        }
    }

    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();


        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];
		c0.a = alpha;
		c1.a = alpha;

		
        float fd = fadeDown(triga.getValue(t));
        //if(switcheroo) swapColours(c0, c1);
        p->fan.drawSmoothFan(fd, c0*fd + c1*(1.f-fd), c1);

        float ad = fadeDown(trigb.getValue(t));
        p->ladder.drawFadeSkip(ad, 0, 2, c0, c1);

        /*
        p->fan.drawSmoothFan(fd, c0,c1);

        float fu = trig.getValue(t);
        p->ladder.drawStep(fu, c1,c0);*/


    }


};
class Diamond0: public PlanetSubprogram<DiamondProgram> {
	void draw(float alpha) {
		ofFloatColor c0 = p->colours[0];
		ofFloatColor c1 = p->colours[1];
		ofFloatColor c2 = p->colours[2];
		ofFloatColor c3 = p->colours[3];
		
		
		
		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;
		
		float t = ofGetElapsedTimef();
		
		t/= 4.f;
		t -= (int) t;
		
		p->fan.drawGrad(t, c0, c1, c2);
		p->ladder.drawGrad(t, c0, c1, c2);
	}
};


class Diamond2: public PlanetSubprogram<DiamondProgram> {
public:
    Trigger trig;
    Trigger triga;
    Trigger trigb;

    int pos;
    bool switcheroo;
    void init() {
        switcheroo = false;
        trig.setDuration(0.3);
        triga.setDuration(0.3);
        trigb.setDuration(0.3);
        pos = 0;
    }

    void noteOn(int note) {
        if(note==12) {
            trig.trigger();
            pos++;
            pos %= p->fan.fan.size();

        } else if(note==14) {
            triga.trigger();
        } else if(note==16) {
            trigb.trigger();
        }
    }

    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();
        ofFloatColor c2 = p->colours[0];
        ofFloatColor c3 = p->colours[1];
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];
		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;
        float fd = fadeDown(trig.getValue(t));
        //fd = fadeDown(triga.getValue(t));
        //if(switcheroo) swapColours(c0, c1);
        p->ladder.drawFadeSkip(fd, 0, 2, c0, c1);

        p->fan.drawOne(fd, pos, c2, c1);
        //p->ladder.drawFadeSkip(fd, 1, 2, c2, c1);



    }


};

class Diamond3: public PlanetSubprogram<DiamondProgram> {
public:
    Trigger trig;
    Trigger triga;
    Trigger trigb;

    bool switcheroo;
    void init() {
        switcheroo = false;
        trig.setDuration(0.3);
        triga.setDuration(0.6);

    }

    void noteOn(int note) {
        if(note==24) {
            trig.trigger();
            switcheroo = !switcheroo;
        } else if(note==26) {
            triga.trigger();
        }
    }

    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();
        ofFloatColor c2 = p->colours[0];
        ofFloatColor c3 = p->colours[1];
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];
		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;
        float fd = fadeDown(trig.getValue(t));
        //if(switcheroo) swapColours(c0, c1);
        p->ladder.drawFadeSkip(fd, switcheroo?1:0, 2, c0, c1);

        fd = fadeDown(triga.getValue(t));
        p->fan.drawFadeFan(fd,c3,c1);
        /*
        p->fan.drawSmoothFan(fd, c0,c1);

        float fu = trig.getValue(t);
        p->ladder.drawStep(fu, c1,c0);*/


    }


};

class Diamond4: public PlanetSubprogram<DiamondProgram> {
public:
    Trigger trig;
    Trigger triga;
    Trigger trigb;

    bool switcheroo;
    void init() {
        switcheroo = false;
        trig.setDuration(0.9);
        triga.setDuration(0.6);
        trigb.setDuration(0.6);

    }

    void noteOn(int note) {
        if(note==36 || note==40) {
            triga.trigger();
        } else if(note==38) {
            trigb.trigger();
        } else if (note==43) {
            trig.trigger();
            switcheroo ^= true;
        }
    }

    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();
        ofFloatColor c2 = p->colours[0];
        ofFloatColor c3 = p->colours[1];
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;
        float fa = fadeDown(triga.getValue(t));
        float fb = fadeDown(trigb.getValue(t));

        p->ladder.drawFanAlternate(fa, fb, c0, c1);


        if(switcheroo) swapColours(c0, c1);
        float fd = fadeDown(trig.getValue(t));
        fd = easeInCubic(fd);
        p->fan.drawZoom(fd,c0,c1);
        /*
        p->fan.drawSmoothFan(fd, c0,c1);

        float fu = trig.getValue(t);
        p->ladder.drawStep(fu, c1,c0);*/


    }


};


class Diamond5: public PlanetSubprogram<DiamondProgram> {
public:
    Trigger trig;
    Trigger triga;
    Trigger trigb;

    bool switcheroo;
    void init() {
        switcheroo = false;
        trig.setDuration(0.9);
        triga.setDuration(0.6);
        trigb.setDuration(0.6);

    }

    void noteOn(int note) {
        if(note==48 || note==52) {
            triga.trigger();
        } else if(note==50) {
            trigb.trigger();
        } else if (note==55 || note==53) {
            trig.trigger();
            switcheroo ^= true;
        }
    }

    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();

        ofFloatColor c2 = p->colours[0];
        ofFloatColor c3 = p->colours[1];
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;
		
        float fa = fadeDown(triga.getValue(t));
        float fb = fadeDown(trigb.getValue(t));

        p->ladder.drawSweepAlternate(fa, fb, c0, c1);


        if(switcheroo) swapColours(c0, c1);
        float fd = fadeDown(trig.getValue(t));
        fd = easeInCubic(fd);
        p->fan.drawFans(fd,c0,c1);
        /*
        p->fan.drawSmoothFan(fd, c0,c1);

        float fu = trig.getValue(t);
        p->ladder.drawStep(fu, c1,c0);*/


    }


};
class Diamond6: public PlanetSubprogram<DiamondProgram> {
public:
    Trigger trig;
    Trigger triga;
    Trigger trigb;

    int pos;
    bool sw1;
    bool sw2;
    void init() {
        sw1 = sw2 = false;
        trig.setDuration(0.3);
        triga.setDuration(0.3);
        trigb.setDuration(0.3);
        pos = 0;

    }

    void noteOn(int note) {
        if(note==65) {
            trig.trigger();
            pos++;
            pos %= p->fan.fan.size();

        } else if(note==60 || note==64) {
            triga.trigger();
            sw1 ^= true;
        } else if(note==62) {
            trigb.trigger();
            sw2^=true;
        }
    }

    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();
        ofFloatColor c2 = p->colours[0];
        ofFloatColor c3 = p->colours[1];
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;
		
        float fd = fadeDown(trig.getValue(t));
        p->fan.drawOne(fd, pos, c2, c1);
        //fd = fadeDown(triga.getValue(t));
        ofFloatColor ca = c0;
        ofFloatColor cb = c1;
        if(sw1) swapColours(ca, cb);
        float fa = fadeDown(triga.getValue(t));

        p->ladder.drawGrowSkip(fa, 0, ca, cb);

        ca = c2;
        cb = c1;
        if(sw2) swapColours(ca, cb);
        float fb = fadeDown(trigb.getValue(t));

        p->ladder.drawGrowSkip(fb, 1, ca, cb);

        //p->ladder.drawFadeSkip(fd, 1, 2, c2, c1);



    }


};

class Diamond7: public PlanetSubprogram<DiamondProgram> {
public:
    Trigger trig;
    Trigger triga;
    Trigger trigb;

    bool switcheroo;
    bool sw1;
    bool sw2;
    void init() {
        sw1 = sw2 = false;
        trig.setDuration(0.4);
        triga.setDuration(0.3);
        trigb.setDuration(0.3);
        switcheroo = false;

    }

    void noteOn(int note) {
        if(note==77) {
            trig.trigger();
            switcheroo ^= true;

        } else if(note==72 || note==76) {
            triga.trigger();
            sw1 ^= true;
        } else if(note==74) {
            trigb.trigger();
            sw2^=true;
        }
    }

    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();
        ofFloatColor c2 = p->colours[0];
        ofFloatColor c3 = p->colours[1];
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];


		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;
		
        ofFloatColor ca = c0;
        ofFloatColor cb = c1;
        if(switcheroo) swapColours(ca, cb);
        float fd = fadeDown(trig.getValue(t));
        p->fan.drawFans2(fd, ca, cb);
        //fd = fadeDown(triga.getValue(t));

        ca = c0;
        cb = c1;
        if(sw1) swapColours(ca, cb);
        float fa = fadeDown(triga.getValue(t));

        p->ladder.drawGrowSkip(fa, 0, ca, cb);

        ca = c2;
        cb = c1;
        if(sw2) swapColours(ca, cb);
        float fb = fadeDown(trigb.getValue(t));

        p->ladder.drawGrowSkip(fb, 1, ca, cb);

        //p->ladder.drawFadeSkip(fd, 1, 2, c2, c1);



    }


};

class Diamond8: public PlanetSubprogram<DiamondProgram> {
public:
    Trigger trig;
    Trigger triga;
    Trigger trigb;

    bool switcheroo;
    bool sw1;
    bool sw2;
    void init() {
        sw1 = sw2 = false;
        trig.setDuration(0.4);
        triga.setDuration(0.3);
        trigb.setDuration(0.3);
        switcheroo = false;

    }

    void noteOn(int note) {
        if(note==89) {
            trig.trigger();
            switcheroo ^= true;

        } else if(note==80 || note==88) {
            triga.trigger();
            sw1 ^= true;
        } else if(note==86) {
            trigb.trigger();
            sw2^=true;
        }
    }

    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();
        ofFloatColor c2 = p->colours[0];
        ofFloatColor c3 = p->colours[1];
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;
        ofFloatColor ca = c0;
        ofFloatColor cb = c1;
        if(switcheroo) swapColours(ca, cb);
        float fd = fadeDown(trig.getValue(t));
        if(switcheroo) {
			p->fan.drawFans2(fd, ca, cb);
        } else {
			p->fan.drawFans(fd, ca, cb);
        }
        //fd = fadeDown(triga.getValue(t));

        ca = c0;
        cb = c1;
        if(sw1) swapColours(ca, cb);
        float fa = fadeDown(triga.getValue(t));

        p->ladder.drawGrowSkip(fa, 0, ca, cb);

        ca = c2;
        cb = c1;
        if(sw2) swapColours(ca, cb);
        float fb = fadeDown(trigb.getValue(t));

        p->ladder.drawGrowSkip(fb, 1, ca, cb);

        //p->ladder.drawFadeSkip(fd, 1, 2, c2, c1);



    }


};
