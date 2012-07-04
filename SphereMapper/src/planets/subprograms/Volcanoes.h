//
//  VolcanoProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PlanetProgram.h"

#pragma once

class Volcano1: public PlanetSubprogram<VolcanoProgram> {
public:

	Trigger trig;
	bool switcheroo;
	bool odd;
	void init() {
	    odd = false;
		switcheroo = false;
		trig.trigger(60.f/112.f);
	}
	void noteOn(int note) {
		if(note==0) {
		    if(odd) {
                trig.trigger();
                switcheroo ^= true;
		    }
		    odd ^= true;
		}
		printf("%d\n", note);
	}

	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();


		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		if(switcheroo) swapColours(c0, c1);

		p->centre.drawFans(trig.getValue(t), c0, c1);
		for(int i = 0; i < 4 ; i++) {
			p->quarters[i].drawFadeFan(trig.getValue(t), c0, c1);
		}
	}
};

class Volcano0: public PlanetSubprogram<VolcanoProgram> {

public:

	void draw(float alpha) {

		float t = ofGetElapsedTimef();
		t /= 4.f;
		t -= (int) t;




		ofFloatColor c0 = p->colours[3];
		ofFloatColor c1 = p->colours[1];
		ofFloatColor c2 = p->colours[2];


		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;


		p->centre.drawGrad(t, c0, c1, c2);
		for(int i = 0; i < 4 ; i++) {
			p->quarters[i].drawGrad(t, c0, c1, c2);
		}
	}
};

class Volcano2: public PlanetSubprogram<VolcanoProgram> {
public:

	Trigger trig;
	bool switcheroo;
	void init() {
		switcheroo = false;
		trig.trigger(60.f/112.f);
	}
	void noteOn(int note) {
		if(note==12) {
			trig.trigger();
			switcheroo ^= true;
		}
		printf("%d\n", note);
	}

	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();


		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;

		if(switcheroo) swapColours(c0, c1);

		p->centre.drawFans(trig.getValue(t), c0, c1);
		for(int i = 0; i < 4 ; i++) {
			p->quarters[i].drawSmoothFan(trig.getValue(t), c0, c1);
		}
	}
};

class Volcano3: public PlanetSubprogram<VolcanoProgram> {
public:

	Trigger trig;
	Trigger weep;

	bool switcheroo;
	void init() {
		switcheroo = false;
		trig.trigger(60.f/112.f);
		weep.trigger(1);
	}

	void noteOn(int note) {
		if(note==24) {

			trig.trigger();
			switcheroo ^= true;
		} else if(note==28) {
            weep.trigger();
		}
		printf("%d\n", note);
	}

	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();


		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		ofFloatColor c2 = p->colours[2];
		c2.a = alpha;
        float w = ofMap(easeOutElastic(weep.getValue(t)),-0.5,1.5, 0.2,0.9);
        w *= fadeDown(weep.getValue(t));
		p->centre.drawZoom(w, c2, c1);

		if(switcheroo) swapColours(c0, c1);

		for(int i = 0; i < 4 ; i++) {
			p->quarters[i].drawSmoothFan(trig.getValue(t), c0, c1);
		}
	}
};


class Volcano4: public PlanetSubprogram<VolcanoProgram> {
public:

	Trigger bd;
	Trigger sd;

	bool switcheroo;
	void init() {
		switcheroo = false;
		bd.trigger(20.f/112.f);
		sd.trigger(0.5);
	}

	void noteOn(int note) {
		if(note==36) {

			bd.trigger();
			switcheroo ^= true;
		} else if(note==38) {
            sd.trigger();
		}

	}

	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();


		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];
		ofFloatColor c2 = p->colours[1];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;

        int offset = switcheroo?1:0;
        float b = fadeDown(bd.getValue(t));
        b = easeOutQuad(b);
		p->centre.fan[0+offset]->drawFade(b, c2, c1);
		p->centre.fan[2+offset]->drawFade(b, c2, c1);


		for(int i = 0; i < 4 ; i++) {
			p->quarters[i].drawFadeFan(fadeDown(sd.getValue(t)), c0, c1);
		}
	}
};

class Volcano5: public PlanetSubprogram<VolcanoProgram> {
public:

	Trigger bd;
	Trigger sd;
    Trigger org;
	bool switcheroo;

	void init() {
		switcheroo = false;
		bd.setDuration(40.f/112.f);
		sd.trigger(0.5f);
        org.trigger(60.f/112.f);
	}

	void noteOn(int note) {
		if(note==48) {

			bd.trigger();
			switcheroo ^= true;
		} else if(note==50) {
            sd.trigger();
		} else if(note==52) {
            org.trigger();
		}

	}

	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();


		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];
		ofFloatColor c2 = p->colours[1];
		ofFloatColor wt = p->colours[4];


		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		wt.a = alpha;

        int offset = switcheroo?1:0;
        float b = fadeDown(bd.getValue(t));
        b = easeOutQuint(b);
		p->centre.drawZoom(b, c0, c1);


		for(int i = 0; i < 4 ; i++) {
			p->quarters[i].drawSmoothFan(fadeDown(sd.getValue(t)), c2, c1);
		}
	}
};
class Volcano6: public PlanetSubprogram<VolcanoProgram> {
public:

	Trigger trigs[12];
	TriFace *faces[12];
	Trigger weep;
    int pos;
	bool switcheroo;
	void init() {
	    pos = 0;
		switcheroo = false;
		for(int i = 0; i < 12; i++) {
            trigs[i].setDuration(3);
		}
		for(int i = 0; i < 4; i++) {
		faces[i*3+0] = p->quarters[i].fan[0];
		faces[i*3+1] = p->quarters[i].fan[1];
		faces[i*3+2] = p->quarters[i].fan[2];
		}
		weep.setDuration(1);

	}

	void noteOn(int note) {
		if(note==60) {
			trigs[pos].trigger();
			pos = (pos+1) % 12;
		} else if(note==64) {
            weep.trigger();
		}
	}

	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();


		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];
		ofFloatColor c2 = p->colours[2];
		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;

        float w = ofMap(easeOutElastic(weep.getValue(t)),-0.5,1.5, 0.2,0.9);
        w *= fadeDown(weep.getValue(t));
		p->centre.drawZoom(w, c2, c1);


		for(int i = 0; i < 12 ; i++) {
			faces[i]->drawFade(fadeDown(trigs[i].getValue(t)), c0, c1);
		}
	}
};



class Volcano7: public PlanetSubprogram<VolcanoProgram> {
public:

	Trigger bd;
	Trigger sd;
    Trigger org;
    int pos;

	void init() {
        pos = 0;
		bd.setDuration(80.f/112.f);
		sd.trigger(0.5f);
        org.trigger(60.f/112.f);
	}

	void noteOn(int note) {
		if(note==72) {
            pos = (pos+1) % 4;
			bd.trigger();

		} else if(note==74) {
            sd.trigger();
            pos = -1;
		} else if(note==76) {
            org.trigger();
		}

	}

	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();


		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];
		ofFloatColor c2 = p->colours[1];
		ofFloatColor wt = p->colours[4];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		wt.a = alpha;

        float b = bd.getValue(t);
        b = easeOutQuint(b);
        if(pos>-1) {
            for(int i = 0; i < pos; i++) {
                p->centre.fan[i]->draw(c0);

            }
            p->centre.fan[pos]->drawFade(b, c0, c1);
        }


		for(int i = 0; i < 4 ; i++) {
			p->quarters[i].drawSmoothFan(fadeDown(sd.getValue(t)), c2, c1);
		}
	}
};

class Volcano8: public PlanetSubprogram<VolcanoProgram> {
public:

	Trigger bd;
	Trigger sd;
    Trigger org;
    int pos;

	void init() {
        pos = 0;
		bd.setDuration(30.f/112.f);
		sd.trigger(0.5f);
        org.trigger(60.f/112.f);
	}

	void noteOn(int note) {
		if(note==84) {
            pos = (pos+1) % 4;
			bd.trigger();

		} else if(note==86) {
            sd.trigger();
            pos = -1;
		} else if(note==88) {
            org.trigger();
		}

	}

	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();


		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];
		ofFloatColor c2 = p->colours[1];
		ofFloatColor wt = p->colours[4];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		wt.a = alpha;

        float b = bd.getValue(t);
        b = easeOutQuint(b);
        if(pos>-1) {
            for(int i = 0; i < pos; i++) {
                p->centre.fan[i]->draw(c0);

            }
            p->centre.fan[pos]->drawSlide(b, 0, c0, c1);
        }


		for(int i = 0; i < 4 ; i++) {
			p->quarters[i].drawFadeFan(1-fadeDown(sd.getValue(t)), c1, c2);
		}
	}
};
