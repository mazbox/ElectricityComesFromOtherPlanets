//
//  VolcanoProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PlanetProgram.h"

#pragma once

class Towers1: public PlanetSubprogram<TowersProgram> {
public:
    Trigger note1;
    Trigger note2;

    void init() {
        note1.setDuration(0.3);

        note2.setDuration(0.3);
    }

    void noteOn(int note) {
        if(note==0) {
            note1.trigger();
        } else if(note==1) {
            note2.trigger();
        }
    }




    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();


        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;

		
        float a = fadeDown(note1.getValue(t));
        float b = fadeDown(note2.getValue(t));


        p->lMid.drawFade(a, b, 0, 0, c0, c1);
        p->rMid.drawFade(b, a, 0, 0, c0, c1);

        p->lOut.drawFade(a, b, 0, 0, c0, c1);
        p->rOut.drawFade(b, a, 0, 0, c0, c1);

        /*
        		p->top->draw(c0);
        		p->bot->draw(c0);
        		p->left->draw(c0);
        		p->right->draw(c0);

        		*/


    }

};
class Towers0: public PlanetSubprogram<TowersProgram> {

public:
	void draw(float alpha) {

		ofFloatColor a = p->colours[0];
		ofFloatColor b = p->colours[1];
		ofFloatColor c = p->colours[2];
		ofFloatColor d = p->colours[3];

		a.a = alpha;
		b.a = alpha;
		c.a = alpha;
		d.a = alpha;
		
		
	//	QuadFace *top;
	//	QuadFace *bot;
	//	QuadFace *left;
	//	QuadFace *right;
		
		//Tower lMid, rMid, lOut, rOut;
		
		float t = ofGetElapsedTimef();
		
		t /= 4.0;
		t -= (int) t;
		
		p->lMid.drawGrad(t, a, b, c, d);
		p->rMid.drawGrad(t, a, b, c, d);
		p->lOut.drawGrad(t, a, b, c, d);
		p->rOut.drawGrad(t, a, b, c, d);
		p->top->drawGrad(t, a, b, c, d);
		p->bot->drawGrad(t, a, b, c, d);
		p->left->drawGrad(t, a, b, c, d);
		p->right->drawGrad(t, a, b, c, d);
	}
};


class Towers2: public PlanetSubprogram<TowersProgram> {
public:
    Trigger note1;
    Trigger note2;

    void init() {
        note1.setDuration(0.3);
        note2.setDuration(0.3);
    }

    void noteOn(int note) {
        if(note==12) {
            note1.trigger();
        } else if(note==14) {
            note2.trigger();
        }
    }




    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();


        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;

		
        float a = fadeDown(note1.getValue(t));
        float b = fadeDown(note2.getValue(t));


        p->lMid.drawFade(a, b, 0, 0, c0, c1);
        p->rMid.drawFade(b, a, 0, 0, c0, c1);

        p->lOut.drawFade(a, b, 0, 0, c0, c1);
        p->rOut.drawFade(b, a, 0, 0, c0, c1);

      


    }

};

class Towers3: public PlanetSubprogram<TowersProgram> {
public:
    Trigger note1;
    Trigger note2;
    Trigger note3;

    int pos;
    bool switcheroo;

    void init() {
        switcheroo = false;
        pos = 0;
        note1.setDuration(0.3);
        note2.setDuration(0.3);
        note3.setDuration(0.5);
    }


    void noteOn(int note) {
        if(note==24) {
            pos++;
            pos %= 4;
            if(pos==0) switcheroo ^= true;
            if(switcheroo) {
                note1.trigger();
            } else {
                note2.trigger();
            }
        } else if(note==26) {
            note3.trigger();
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

		
        float a = fadeDown(note1.getValue(t));
        float b = fadeDown(note2.getValue(t));
        float c = fadeDown(note3.getValue(t));

        p->lMid.drawFade(a, b, c, c, c0, c1, c2);
        p->rMid.drawFade(b, a, c, c, c0, c1, c2);

        p->lOut.drawFade(a, b, c, c, c0, c1, c2);
        p->rOut.drawFade(b, a, c, c, c0, c1, c2);

        p->top->drawFade(c, c2, c1);
        p->bot->drawFade(c, c2, c1);
        p->left->drawFade(b, c0, c1);
        p->right->drawFade(a, c0, c1);


    }

};


class Towers4: public PlanetSubprogram<TowersProgram> {
public:
    Trigger note1;
    Trigger note2;
    Trigger note3;

    int pos;
    bool switcheroo;
    bool sweep;
    void init() {
        sweep = false;
        switcheroo = false;
        pos = 0;
        note1.setDuration(0.3);
        note2.setDuration(0.3);
        note3.setDuration(0.5);
    }


    void noteOn(int note) {
        if(note==36) {
            pos++;
            pos %= 8;
            if(pos==0) switcheroo ^= true;
            if(switcheroo) {
                note1.trigger();
            } else {
                note2.trigger();
            }
        } else if(note==38) {
            note3.trigger();
            sweep ^= true;
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

		
        float a = fadeDown(note1.getValue(t));
        float b = fadeDown(note2.getValue(t));
        float c = fadeDown(note3.getValue(t));

        p->lMid.drawFadeSweep(a, b, c, c, c0, c1, c2, sweep);
        p->rMid.drawFadeSweep(b, a, c, c, c0, c1, c2, sweep);

        p->lOut.drawFadeSweep(a, b, c, c, c0, c1, c2, sweep);
        p->rOut.drawFadeSweep(b, a, c, c, c0, c1, c2, sweep);


        if(sweep) {
            if(switcheroo) {
                p->top->drawSweep(c, c1, c2);
                p->bot->drawSweep(c, c1, c2);
            } else {
                p->top->drawSweep90(c, c1, c2);
                p->bot->drawSweep90(c, c1, c2);
            }
        } else {
            if(switcheroo) {
                p->top->drawSweep90(c, c2, c1);
                p->bot->drawSweep90(c, c2, c1);
            } else {
                p->top->drawSweep(c, c2, c1);
                p->bot->drawSweep(c, c2, c1);
            }
        }
        p->left->drawFade(b, c0, c1);
        p->right->drawFade(a, c0, c1);




    }

};

class Towers5: public PlanetSubprogram<TowersProgram> {
public:
    Trigger note1;
    Trigger note2;
    Trigger note3;

    int pos;
    bool switcheroo;
    bool sweep;
    void init() {
        sweep = false;
        switcheroo = false;
        pos = 0;
        note1.setDuration(0.3);
        note2.setDuration(0.3);
        note3.setDuration(1);
    }


    void noteOn(int note) {
        if(note==48) {
            pos++;
            pos %= 8;
            if(pos==0) switcheroo ^= true;
            if(switcheroo) {
                note1.trigger();
            } else {
                note2.trigger();
            }
        } else if(note==50) {

            note3.trigger();
            sweep ^= true;
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

		
        float a = fadeDown(note1.getValue(t));
        float b = fadeDown(note2.getValue(t));
        float c = fadeDown(note3.getValue(t));
        //c = easeInOutQuad(c);
        p->lMid.drawFadeSweep90(a, b, c, c, c0, c1, c2, sweep);
        p->rMid.drawFadeSweep90(b, a, c, c, c0, c1, c2, sweep);

        p->lOut.drawFadeSweep90(a, b, c, c, c0, c1, c2, sweep);
        p->rOut.drawFadeSweep90(b, a, c, c, c0, c1, c2, sweep);


        if(sweep) {

            p->top->drawSweep(c, c1, c2);
            p->bot->drawSweep(c, c1, c2);

        } else {

            p->top->drawSweep(c, c2, c1);
            p->bot->drawSweep(c, c2, c1);

        }
        p->left->drawFade(b, c0, c1);
        p->right->drawFade(a, c0, c1);




    }

};

class Towers6: public PlanetSubprogram<TowersProgram> {
public:
    Trigger notes[8];


    Trigger note3;

    Face *faces[8];
    Face *outers[10];
    int pos;

    void init() {
        pos = 0;

        for(int i = 0; i < 8; i++ ) {
            notes[i].setDuration(0.7);
        }
        note3.setDuration(0.5);
        faces[0] = p->lOut.out;
        faces[1] = p->lMid.out;
        faces[2] = p->rMid.in;
        faces[3] = p->rOut.in;
        faces[4] = p->rOut.out;
        faces[5] = p->rMid.out;
        faces[6] = p->lMid.in;
        faces[7] = p->lOut.in;

        outers[0] = p->lOut.up;
        outers[1] = p->lMid.up;
        outers[2] = p->rMid.up;
        outers[3] = p->rOut.up;
        outers[4] = p->rOut.down;
        outers[5] = p->rMid.down;
        outers[6] = p->lMid.down;
        outers[7] = p->lOut.down;
        outers[8] = p->top;
		outers[9] = p->bot;
    }


    void noteOn(int note) {
        if(note==60) {
            pos++;
            pos %= 8;
            notes[pos].trigger();
            note3.trigger();

        } else if(note==91) {

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



        for(int i = 0; i < 8; i++) {

            float a = notes[i].getValue(t);
            //float b = fadeDown(note2.getValue(t));
            //float c = fadeDown(note3.getValue(t));
            //c = easeInOutQuad(c);
            faces[i]->drawSweepInOut(a, c0, c1);
        }
        float b = fadeDown(note3.getValue(t));
        for(int i = 0; i < 10; i++) {


            //float b = fadeDown(note2.getValue(t));
            //float c = fadeDown(note3.getValue(t));
            //c = easeInOutQuad(c);
            outers[i]->drawFade(b, c2, c1);
        }

        p->left->draw(c1);
        p->right->draw(c1);





    }

};




class Towers7: public PlanetSubprogram<TowersProgram> {
public:
    Trigger notes[8];


    Trigger note2, note3;

    Face *faces[8];
    Face *tops[5];
    Face *bots[5];
    int pos;

    void init() {
        pos = 0;

        for(int i = 0; i < 8; i++ ) {
            notes[i].setDuration(0.7);
        }
        note3.setDuration(0.5);
        note2.setDuration(0.5);
        faces[0] = p->lOut.out;
        faces[1] = p->lMid.out;
        faces[2] = p->rMid.in;
        faces[3] = p->rOut.in;
        faces[4] = p->rOut.out;
        faces[5] = p->rMid.out;
        faces[6] = p->lMid.in;
        faces[7] = p->lOut.in;

        tops[0] = p->lOut.up;
        tops[1] = p->lMid.up;
        tops[2] = p->rMid.up;
        tops[3] = p->rOut.up;
		tops[4] = p->top;

        bots[0] = p->rOut.down;
        bots[1] = p->rMid.down;
        bots[2] = p->lMid.down;
        bots[3] = p->lOut.down;
		bots[4] = p->bot;
    }


    void noteOn(int note) {
        if(note==72) {
            pos++;
            pos %= 8;
            notes[pos].trigger();


			if(pos%2==0) {
				note2.trigger();
			} else {
				note3.trigger();
			}
        } else if(note==91) {

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

		
        for(int i = 0; i < 8; i++) {

            float a = notes[i].getValue(t);
            //float b = fadeDown(note2.getValue(t));
            //float c = fadeDown(note3.getValue(t));
            //c = easeInOutQuad(c);
            faces[i]->drawSweepInOut(a, c0, c1);
        }
        float f = fadeDown(note2.getValue(t));
        float b = fadeDown(note3.getValue(t));
        for(int i = 0; i < 5; i++) {


			tops[i]->drawFade(f, c2, c1);
            bots[i]->drawFade(b, c2, c1);
        }

        p->left->draw(c1);
        p->right->draw(c1);





    }

};

class Towers8: public PlanetSubprogram<TowersProgram> {
public:
    Trigger notes[8];


    Trigger note3;

    Face *faces[8];
    Face *outers[10];
    int pos;

    void init() {
        pos = 0;

        for(int i = 0; i < 8; i++ ) {
            notes[i].setDuration(0.7);
        }
        note3.setDuration(0.5);
        faces[0] = p->lOut.out;
        faces[1] = p->lMid.out;
        faces[2] = p->rMid.in;
        faces[3] = p->rOut.in;
        faces[4] = p->rOut.out;
        faces[5] = p->rMid.out;
        faces[6] = p->lMid.in;
        faces[7] = p->lOut.in;

        outers[0] = p->lOut.up;
        outers[1] = p->lMid.up;
        outers[2] = p->rMid.up;
        outers[3] = p->rOut.up;
        outers[4] = p->rOut.down;
        outers[5] = p->rMid.down;
        outers[6] = p->lMid.down;
        outers[7] = p->lOut.down;
        outers[8] = p->top;
		outers[9] = p->bot;
    }


    void noteOn(int note) {
        if(note==84) {
            pos++;
            pos %= 8;
            notes[pos].trigger();
            note3.trigger();

        } else if(note==91) {

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

		
        for(int i = 0; i < 8; i++) {

            float a = fadeDown(notes[i].getValue(t));
            //float b = fadeDown(note2.getValue(t));
            //float c = fadeDown(note3.getValue(t));
            //c = easeInOutQuad(c);
            faces[i]->drawFade(a, c0, c1);
        }
        float b = fadeDown(note3.getValue(t));
        for(int i = 0; i < 10; i++) {


            //float b = fadeDown(note2.getValue(t));
            //float c = fadeDown(note3.getValue(t));
            //c = easeInOutQuad(c);
            outers[i]->drawFade(b, c2, c1);
        }

        p->left->draw(c1);
        p->right->draw(c1);





    }

};
