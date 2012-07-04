//
//  VolcanoProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PlanetProgram.h"

#pragma once

class Hex1: public PlanetSubprogram<HexProgram> {
public:
	Trigger trig;
    bool switcheroo;
    Trigger oth;
	void init() {
		switcheroo = false;
		trig.setDuration(240.f/112.f);
        trig.setDuration(240.f/112.f);
	}




	void noteOn(int note) {

		if(note==0 || note==5) {

			trig.trigger();
			switcheroo ^= true;
		}

		printf("Note: %d\n", note);
	}


	float getPart(float trig, float from, float to, bool invert = false) {
		if(trig<from) return 0;
		if(trig>to) return 1;
		if(invert) return 1.f-((trig-from)/(to-from));
		else return (trig - from)/(to - from);
	}

	void draw(float alpha) {


		float t = ofGetElapsedTimef();
		ofEnableLighting();

		ofFloatColor c2 = p->colours[1];
		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];
		ofFloatColor bl = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		bl.a = alpha;


		if(switcheroo) swapColours(c0, c1);




		float f = trig.getValue(t);
		f = easeOutQuint(f);
		float t1 = getPart(f, 0, 0.25);
		p->outerTopQuad->drawSweep(t1, c0, c1);
		p->outerBotQuad->drawSweep(t1, c0, c1);

		float t2 = getPart(f, 0.25, 0.50);

		p->topTri->drawFan(t2, 0, 1, c0, c1);
		p->botTri->drawFan(t2, 0, 1, c0, c1);



        float t3 = getPart(f, 0.50, 1);

        p->innerTopQuad->drawSweep(t3, c0, c1);
        p->innerBotQuad->drawSweep(t3, c0, c1);


	}


};
class Hex0: public PlanetSubprogram<HexProgram> {
public:

	void draw(float alpha) {
		ofFloatColor c0 = p->colours[0];
        ofFloatColor c1 = p->colours[1];
		ofFloatColor c2 = p->colours[2];
		ofFloatColor c3 = p->colours[3];
		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;


		float t=  ofGetElapsedTimef();
		t /= 4;
		t -= (int) t;
		p->innerBotQuad->drawGrad(t, c0, c1, c2, c3);
		p->innerTopQuad->drawGrad(t, c0, c1, c2, c3);
		p->outerTopQuad->drawGrad(t, c0, c1, c2, c3);
		p->outerBotQuad->drawGrad(t, c0, c1, c2, c3);
		p->topTri->drawGrad(t, c0, c1, c2);
		p->botTri->drawGrad(t, c0, c1, c2);

	}
};
class Hex2: public PlanetSubprogram<HexProgram> {

    void init() {
        bdTrig.setDuration(2);
        noteTrig.setDuration(0.4);
        pos = 0;
        faces[0] = p->outerTopQuad;
        faces[1] = p->topTri;
        faces[2] = p->outerBotQuad;
        faces[3] = p->botTri;
    }
    int pos;
    Trigger bdTrig;
    Trigger noteTrig;
    Face *faces[4];
    void noteOn(int note) {
        if(note==12) {
            bdTrig.trigger();

        } else if(note==19) {
            pos++;
            pos %= 4;
            noteTrig.trigger();
        }
    }

    void draw(float alpha) {
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[1];
		ofFloatColor black = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		black.a = alpha;


		float t = ofGetElapsedTimef();
		float f = bdTrig.getValue(t);
		f = easeInQuad(f);
        p->innerTopQuad->drawFade(f, black, c0);
        p->innerBotQuad->drawFade(f, black, c0);

        f = noteTrig.getValue(t);
        f = easeInQuad(f);
        for(int i = 0; i < 4; i++) {
            if(i==pos) {
                faces[i]->drawFade(f, black, c1);
            } else {
                faces[i]->draw(black);
            }
        }


    }
};
class Hex3: public PlanetSubprogram<HexProgram> {

    void init() {
        bdTrig.setDuration(2);
        noteTrig.setDuration(0.4);
        pos = 0;
        faces[0] = p->outerTopQuad;
        faces[1] = p->topTri;
        faces[2] = p->outerBotQuad;
        faces[3] = p->botTri;
		switcheroo = false;
    }
    int pos;
    Trigger bdTrig;
    Trigger noteTrig;
    Face *faces[4];
    bool switcheroo;
    void noteOn(int note) {
        if(note==24||note==29) {
            bdTrig.trigger();
			switcheroo ^= true;
        } else if(note==31) {
            pos++;
            pos %= 4;
            noteTrig.trigger();

        }
    }

    void draw(float alpha) {
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[1];
		ofFloatColor black = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		black.a = alpha;

		float t = ofGetElapsedTimef();
		float f;


        f = noteTrig.getValue(t);
        f = easeInQuad(f);
        for(int i = 0; i < 4; i++) {
            if(i==pos) {
                faces[i]->drawFade(f, black, c1);
            } else {
                faces[i]->draw(black);
            }
        }

        if(switcheroo) swapColours(black, c0);
        f = bdTrig.getValue(t);
		f = easeInQuad(f);
        p->innerTopQuad->drawSweep(f, black, c0);
        p->innerBotQuad->drawSweep(f, black, c0);


    }
};

class Hex4: public PlanetSubprogram<HexProgram> {

    void init() {
        bdTrig.setDuration(0.63);
        noteTrig.setDuration(1);
        note2Trig.setDuration(1);

        pos = 0;

        faces[0] = p->outerTopQuad;
        faces[1] = p->topTri;
        faces[2] = p->outerBotQuad;
        faces[3] = p->botTri;
		switcheroo = false;
    }
    int pos;
    Trigger bdTrig;
    Trigger noteTrig;
    Trigger note2Trig;

    Face *faces[4];
    bool switcheroo;
    void noteOn(int note) {
        if(note==36) {
            bdTrig.trigger();

			if(pos%2==0) pos++; // ensure pos is odd, so next time it's incremented, it should be even
        } else if(note==43) {
            //pos++;
            //pos %= 4;
            noteTrig.trigger();
			switcheroo ^= true;
        } else if(note==41) {
			note2Trig.trigger();
        }
    }

    void draw(float alpha) {
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[1];
		ofFloatColor black = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		black.a = alpha;

		float t = ofGetElapsedTimef();
		float f;


        f = fadeDown(noteTrig.getValue(t));
        f = easeInCubic(f);
        float f2 = fadeDown(note2Trig.getValue(t));
        f2 = easeInCubic(f2);


		int offset = switcheroo?2:0;


		faces[offset]->drawFade(f, c1, black);

			faces[offset+1]->drawFade(f2, c1, black);



        //if(switcheroo) swapColours(black, c0);
        f = bdTrig.getValue(t);
		f = easeInQuad(fadeDown(f));
        if(switcheroo) {
        	p->innerTopQuad->drawFade(f, black, c0);
        } else {
        	p->innerBotQuad->drawFade(f, black, c0);
        }

    }
};

class Hex5: public PlanetSubprogram<HexProgram> {

    void init() {
        bdTrig.setDuration(0.3);
        noteTrig.setDuration(0.4);
        topBot = 0;
        switcheroo = false;
    }

    int topBot;
    bool switcheroo;

    Trigger bdTrig;
    Trigger noteTrig;

    Face *faces[4];

    void noteOn(int note) {
        if(note==59) {
            bdTrig.trigger();
            switcheroo ^= 1;
        } else if(note==48 || note==52 || note==55) {
            topBot ^= 1;

            noteTrig.trigger();

        }
    }

    void draw(float alpha) {
        ofEnableLighting();
        ofFloatColor c2 = p->colours[2];
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[1];
		ofFloatColor bl = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		bl.a = alpha;

		float t = ofGetElapsedTimef();
		float f = bdTrig.getValue(t);
		f = fadeDown(f);
		f = easeInQuad(f);
		if(switcheroo) swapColours(c0, bl);
        p->innerTopQuad->drawSweep90(f, c0, bl);
        p->innerBotQuad->drawSweep90(f, bl, c0);

        f = noteTrig.getValue(t);

        QuadFace *a = p->outerBotQuad;
        TriFace *b = p->botTri;
        if(topBot==1) {
            a = p->outerTopQuad;
            b = p->topTri;
        }
        b->drawFan(getPart(f, 0.5, 1),0,1, c1, c2);
        a->drawSweep(getPart(f, 0, 0.5), c1, c2);

    }
};
class Hex6: public PlanetSubprogram<HexProgram> {

    void init() {
        bdTrig.setDuration(60.f/112.f);
        noteTrig.setDuration(0.4);
        topBot = 0;
        switcheroo = false;
    }

    int topBot;
    bool switcheroo;

    Trigger bdTrig;
    Trigger noteTrig;

    Face *faces[4];

    void noteOn(int note) {
        if(note==67 || note==60 ||note==64) {
            bdTrig.trigger();
            switcheroo ^= 1;
        } else if(note==71) {
            topBot ^= 1;
			printf("Toggle %d\n", topBot);
            noteTrig.trigger();

        }
       // printf("note: %d\n", note);
    }
    void update() {
		float t = ofGetElapsedTimef()*4;
		p->moveLight(5*cos(t), 5*sin(t), 10);
		//light->setAttenuation(1, 0.4, 0.4);
	}
    void draw(float alpha) {
        ofEnableLighting();
        ofFloatColor c2 = p->colours[2];
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[1];
		ofFloatColor bl = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		bl.a = alpha;

		float t = ofGetElapsedTimef();
		float f = bdTrig.getValue(t);
		f = fadeDown(f);
		f = easeOutQuad(f);
		if(switcheroo) {
            p->innerTopQuad->drawSweep90((1-f), bl, c0);
		} else {
            p->innerBotQuad->drawSweep90(f, c0, bl);
		}

        //f = noteTrig.getValue(t);
        t /= 3;
        t -= (int)t;
        p->topTri->drawGrad(t, p->colours[2],p->colours[1],p->colours[2]);
        p->botTri->drawGrad(t, p->colours[2],p->colours[1],p->colours[2]);
        p->outerTopQuad->drawGrad(t, p->colours[2],p->colours[1],p->colours[2], p->colours[1]);
        p->outerBotQuad->drawGrad(t, p->colours[2],p->colours[1],p->colours[2], p->colours[1]);

/*
        QuadFace *a = p->outerBotQuad;
        TriFace *b = p->botTri;
        if(topBot==1) {
            a = p->outerTopQuad;
            b = p->topTri;
        }
        b->drawFan(getPart(f, 0.5, 1),0,1, c1, c2);
        a->drawSweep(getPart(f, 0, 0.5), c1, c2);*/

    }
};

class Hex7: public PlanetSubprogram<HexProgram> {

    void init() {
        bdTrig.setDuration(240.f/112.f);
		spike.setDuration(0.7);
		pos = 0;
    }
    Trigger bdTrig;
	Trigger spike;

    bool switcheroo;
    int pos;
    void noteOn(int note) {
        if(note==72) {
            bdTrig.trigger();
			pos++;
			if(pos>2) pos = 0;
        } else if(note==74) {
			spike.trigger();
        }
    }

    void draw(float alpha) {
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];
		ofFloatColor black = p->colours[3];
		c0.a = alpha;
		c1.a = alpha;
		black.a = alpha;


		float t = ofGetElapsedTimef();
		float f = fadeDown(bdTrig.getValue(t));

        //f = easeInCubic(f);
		float sp = fadeDown(spike.getValue(t));
		float pf = f;
		f *= 4;
		f = (int) f;
		f /= 4.f;

		f = f*0.5 + pf *0.5;
		//f = MIN(f+sp*0.1, 1);

		if(pos==0) {
			p->outerTopQuad->drawSweep(f, c0, c1);
			p->innerTopQuad->drawSweep(f, c0, c1);
			p->innerBotQuad->drawSweep(f, c0, c1);
			p->outerBotQuad->drawSweep(f, c0, c1);
			p->topTri->drawSweep(f, c0, c1);
			p->botTri->drawSweep(f, c0, c1);
		} else if(pos==1) {
			p->outerTopQuad->drawSweep90(f, c0, c1);
			p->innerTopQuad->drawSweep90(f, c0, c1);
			p->innerBotQuad->drawSweep90(f, c0, c1);
			p->outerBotQuad->drawSweep90(f, c0, c1);
			p->topTri->drawSweep90(f, c0, c1);
			p->botTri->drawSweep90(f, c0, c1);
		} else if(pos==2) {
			p->outerTopQuad->drawSweep180(f, c0, c1);
			p->innerTopQuad->drawSweep180(f, c0, c1);
			p->innerBotQuad->drawSweep180(f, c0, c1);
			p->outerBotQuad->drawSweep180(f, c0, c1);
			p->topTri->drawSweep180(f, c0, c1);
			p->botTri->drawSweep180(f, c0, c1);
		}


    }
};

class Hex8: public PlanetSubprogram<HexProgram> {

    void init() {
        bdTrig.setDuration(240.f/112.f);
		spike.setDuration(0.7);
		pos = 0;
    }
    Trigger bdTrig;
	Trigger spike;

    bool switcheroo;
    int pos;
    void noteOn(int note) {
        if(note==84) {
            bdTrig.trigger();
			pos++;
			if(pos>2) pos = 0;

        } else if(note==86) {
			spike.trigger();
        }
    }

    void draw(float alpha) {
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];
		ofFloatColor black = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;
		black.a = alpha;
		float t = ofGetElapsedTimef();
		float f = fadeDown(bdTrig.getValue(t));

        //f = easeInCubic(f);
		//float sp = fadeDown(spike.getValue(t));
		//f = MIN(f+sp*0.1, 1);

		float sf = f;
		f *= 4;
		f = (int) f;
		f /= 4.f;
		f = f*0.5 + sf * 0.5;

		if(pos%2==1) {
			swapColours(c0,c1);
		}
		if(pos==0) {
			p->outerTopQuad->drawSweep(f, c0, c1);
			p->innerTopQuad->drawSweep(f, c0, c1);
			p->innerBotQuad->drawSweep(f, c0, c1);
			p->outerBotQuad->drawSweep(f, c0, c1);
			p->topTri->drawSweep(f, c0, c1);
			p->botTri->drawSweep(f, c0, c1);
		} else if(pos==1) {
			p->outerTopQuad->drawSweep90(f, c0, c1);
			p->innerTopQuad->drawSweep90(f, c0, c1);
			p->innerBotQuad->drawSweep90(f, c0, c1);
			p->outerBotQuad->drawSweep90(f, c0, c1);
			p->topTri->drawSweep90(f, c0, c1);
			p->botTri->drawSweep90(f, c0, c1);
		} else if(pos==2) {
			p->outerTopQuad->drawSweep180(f, c0, c1);
			p->innerTopQuad->drawSweep180(f, c0, c1);
			p->innerBotQuad->drawSweep180(f, c0, c1);
			p->outerBotQuad->drawSweep180(f, c0, c1);
			p->topTri->drawSweep180(f, c0, c1);
			p->botTri->drawSweep180(f, c0, c1);
		}


    }
};
