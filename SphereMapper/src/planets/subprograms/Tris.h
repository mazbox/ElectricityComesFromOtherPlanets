//
//  TriProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PlanetProgram.h"

#pragma once

class Tri1: public PlanetSubprogram<TriProgram> {
public:

    int startingCorner;
    bool switcheroo;


    Trigger trig1;

    void init() {
        float secondsPerBeat = 60.f/112.f;
        trig1.setDuration(secondsPerBeat*4.f);
        startingCorner = 0;
        switcheroo = false;

    }

    void noteOn(int note) {
        if(note==0) {
            trig1.trigger();
            startingCorner++;
            if(startingCorner>2) startingCorner = 0;
            switcheroo ^= true;

        }
        //printf("Note: %d\n", note);
    }

    void update() {
        float t = ofGetElapsedTimef()*2;

        p->moveLight(5*cos(t), 5*sin(t), 10);
        //p->light->setAttenuation(1, 0.4, 0.4);
    }



    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();


        printf("Draw\n");
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];
		c0.a = alpha;
		c1.a = alpha;

        if(switcheroo) swapColours(c0, c1);




        float f = trig1.getValue(t);
        f = easeOutQuad(f);

        p->t1->drawSlide(f, startingCorner, c0, c1);
        p->t2->drawSlide(f, startingCorner, c0, c1);

        p->t3->drawSlide(f, startingCorner, c0, c1);
        p->t4->drawSlide(f, startingCorner, c0, c1);

        p->s1->drawSlide(f, startingCorner, c0, c1);
        p->s2->drawSlide(f, startingCorner, c0, c1);
    }
};









class Tri0: public PlanetSubprogram<TriProgram> {
    void noteOn(int note) {
		
        /*
		 for(int i = 0; i < note/2; i++) {
		 printf(" ");
		 }
		 printf("%d\n", note);*/
    }
	
    void update() {
        float t = ofGetElapsedTimef()*2;
        p->moveLight(7*cos(t), 7*sin(t), 8);
        //light->setAttenuation(1, 0.4, 0.4);
    }
    void draw(float alpha) {
		
        float f = ofGetElapsedTimef()*0.2;
        f -= (int)f;
        ofFloatColor c0 = p->colours[3];
        ofFloatColor c1 = p->colours[0];
        ofFloatColor c2 = p->colours[1];
        ofFloatColor c3 = p->colours[2];
		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;
		
        p->t1->drawGrad(f, c0, c1, c2);
        p->t2->drawGrad(f, c1, c2, c3);
        p->t3->drawGrad(f, c2, c3, c0);
        p->t4->drawGrad(f, c3, c0, c1);
		
        p->s1->drawGrad(f, c0, c1, c2);
        p->s2->drawGrad(f, c1, c2, c3);
    }
	
};






class Tri2: public PlanetSubprogram<TriProgram> {



    Trigger triga;
    Trigger trig1;
    void init() {
        float secondsPerBeat = 60.f/112.f;
        triga.setDuration(secondsPerBeat/4.f);
        trig1.setDuration(secondsPerBeat*4.f);

    }

    void noteOn(int note) {

        if(note==16) {
            triga.trigger();
        } else if(note==12) {
            trig1.trigger();
        } else {
            //    printf("Note: %d\n", note);
        }
    }

    void update() {
        float t = ofGetElapsedTimef()*2;
        p->moveLight(5*cos(t), 5*sin(t), 10);
        //light->setAttenuation(1, 0.4, 0.4);
    }



    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();




        float f = trig1.getValue(t);
        float f1 = easeOutCubic(f);
        float f2 = easeOutQuad(f);
        float f3 = easeOutQuint(f);
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];
        ofFloatColor c2 = p->colours[4];
		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
        p->t1->drawSlide(f1, 0, c0, c1);
        p->t2->drawSlide(f2, 0, c0, c1);
        p->t3->drawSlide(f3, 0, c0, c1);
        p->t4->drawSlide(f2, 0, c0, c1);

        float tfa = triga.getValue(t);
        p->s1->drawFade(tfa, c0, c2);
        p->s2->drawFade(tfa, c0, c2);


    }
};
class Tri3: public PlanetSubprogram<TriProgram> {

public:
    int lastNote;
    Trigger trig1;
    Trigger trig2;

    void init() {
        lastNote = 0;
        trig1.setDuration(120.f/112.f);
        trig2.setDuration(0.8);
    }
    void update() {
        float t = ofGetElapsedTimef();
        p->moveLight(5*cos(t), 5*sin(t), 10);
        //light->setAttenuation(1, 0.4, 0.4);
    }
    void noteOn(int note) {

        if(note==26 && lastNote!=26) {
            trig1.trigger();
        } else if(note==28 && lastNote!=28) {
            trig2.trigger();
        }

        lastNote = note;
        //for(int i = 0; i < note/2; i++) {
        //    printf(" ");
        //}
        //printf("%d\n", note);
    }
    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        float f = trig1.getValue(t);
        f = upDown(f);
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];
		
		c0.a = alpha;
		c1.a = alpha;

		
        p->t1->drawSlide(f, 0, c1, c0);
        float g = easeInOutCubic(f);
        p->t2->drawSlide(g, 0, c0, c1);
        g = easeOutCubic(f);
        p->t3->drawSlide(g, 0, c1, c0);
        g = easeInOutQuad(f);
        p->t4->drawSlide(g, 0, c0, c1);

        f = trig1.getValue(t);
        f = upDown(f);
        f = easeOutCubic(f);
        p->s1->drawSlide(f, 1, c1, c0 );
        p->s2->drawSlide(f, 1, c1, c0);
    }

};
class Tri4: public PlanetSubprogram<TriProgram> {
    void noteOn(int note) {

        /*
                for(int i = 0; i < note/2; i++) {
                    printf(" ");
                }
                printf("%d\n", note);*/
    }

    void update() {
        float t = ofGetElapsedTimef()*2;
        p->moveLight(7*cos(t), 7*sin(t), 8);
        //light->setAttenuation(1, 0.4, 0.4);
    }
    void draw(float alpha) {

        float f = ofGetElapsedTimef()*0.2;
        f -= (int)f;
        ofFloatColor c0 = p->colours[3];
        ofFloatColor c1 = p->colours[0];
        ofFloatColor c2 = p->colours[1];
        ofFloatColor c3 = p->colours[2];
		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;
		
        p->t1->drawGrad(f, c0, c1, c2);
        p->t2->drawGrad(f, c1, c2, c3);
        p->t3->drawGrad(f, c2, c3, c0);
        p->t4->drawGrad(f, c3, c0, c1);

        p->s1->drawGrad(f, c0, c1, c2);
        p->s2->drawGrad(f, c1, c2, c3);
    }

};


class Tri5: public PlanetSubprogram<TriProgram> {
public:

    int startingCorner;
    bool switcheroo;

bool sq;
    Trigger trig1;
    Trigger trig2;
    Trigger trig3;
    void update() {
        float t = ofGetElapsedTimef()*2;
        p->moveLight(7*cos(t), 7*sin(t), 12);

        //light->setAttenuation(1, 0.4, 0.4);
    }


    void init() {
        float secondsPerBeat = 60.f/112.f;
        trig1.setDuration(secondsPerBeat*4.f);
        startingCorner = 0;
        switcheroo = false;
        trig2.setDuration(0.6);
		trig3.setDuration(0.6);
    sq = false;
    }

    void noteOn(int note) {
        if(note==48) {
            trig1.trigger();
            startingCorner++;
            switcheroo ^= true;

        } else if(note==52) {

            sq ^= true;
            if(sq) {
				trig2.trigger();
            } else {
            trig3.trigger();
            }
        }
        printf("Note: %d\n", note);
    }





    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();


        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];
		c0.a = alpha;
		c1.a = alpha;


        if(switcheroo) swapColours(c0, c1);

        float f = trig1.getValue(t);
        f = easeOutQuad(f);


        p->leftFan->drawSmoothFan(f, c0, c1);



		if(switcheroo) swapColours(c0, c1);

		f = trig2.getValue(t);
        f = easeOutQuad(f);
        float f2 = trig3.getValue(t);
        f2 = easeOutQuad(f2);

        p->s1->drawSweepInOut(f, c0, c1);
        p->s2->drawSweepInOut(f2, c0, c1);
    }
};










class Tri6: public PlanetSubprogram<TriProgram> {
    bool switch2;

    Trigger fanTrig;

    int lastNote;
    void init() {
        lastNote = 0;
        float j = 480.f/112.f;
        fanTrig.setDuration(j);
        switch2 = false;
    }


    void noteOn(int note) {

        if(note==60) {
            fanTrig.trigger();
            switch2 ^= 1;
        }
        lastNote = note;

        for(int i = 0; i < note/2; i++) {
            //     printf(" ");
        }
        // printf("%d\n", note);

    }

    void update() {
        float t = ofGetElapsedTimef()*4;
        p->moveLight(5*cos(t), 5*sin(t), 10);
        //light->setAttenuation(1, 0.4, 0.4);
    }



    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();





        float f = fanTrig.getValue(t);
        f = fadeDown(f);
        printf("%f\n", f);
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[1];
		
		c0.a = alpha;
		c1.a = alpha;

        if(switch2) swapColours(c0, c1);
        p->fan2->drawSmoothFan(f, c0, c1);
        p->fan1->drawSmoothFan(f, c0, c1);





    }

};


class Tri7: public PlanetSubprogram<TriProgram> {
    bool switch2;

    Trigger fanTrig;

    int lastNote;
    void init() {
        lastNote = 0;
        float secondsPerBeat = 60.f/112.f;
        fanTrig.setDuration(secondsPerBeat*3);
        switch2 = false;
    }


    void noteOn(int note) {

        if(note==76) {
            fanTrig.trigger();
            switch2 ^= 1;
        }
        lastNote = note;

        for(int i = 0; i < note/2; i++) {
            //     printf(" ");
        }
        // printf("%d\n", note);

    }

    void update() {
        float t = ofGetElapsedTimef()*4;
        p->moveLight(5*cos(t), 5*sin(t), 10);
        //light->setAttenuation(1, 0.4, 0.4);
    }



    void draw(float alpha) {
        float t = ofGetElapsedTimef();
        ofEnableLighting();





        float f = fanTrig.getValue(t);
        f = fadeDown(f);
        printf("%f\n", f);
        ofFloatColor c0 = p->colours[2];
        ofFloatColor c1 = p->colours[3];
		
		c0.a = alpha;
		c1.a = alpha;

        if(switch2) swapColours(c0, c1);
        p->fan2->drawSmoothFan(f, c1, c0);
        p->fan1->drawSmoothFan(f, c0, c1);





    }

};
class Tri8: public PlanetSubprogram<TriProgram> {
    Trigger trig;
    int pos;
    int lastNote;
    void init() {
        lastNote = 0;
        pos = 0;
        trig.setDuration(0.5);
    }

    void noteOn(int note) {
        if(note==88 && lastNote!=88) {
            trig.trigger();
            pos++;
            pos %= 3;
        }
        lastNote = note;
        printf("%d\n", note);
    }
    void swapTriFaces(TriFace *&a, TriFace *&b) {
        TriFace *tmp = a;
        a = b;
        b = tmp;
    }
    void draw(float alpha) {
        float f = trig.getValue(ofGetElapsedTimef());
        ofFloatColor ce0 = p->colours[2];
        ofFloatColor ce1 = p->colours[4];
		
		ce0.a = alpha;
		ce1.a = alpha;

        TriFace *a1 = p->t1;
        TriFace *b1 = p->s1;
        TriFace *c1 = p->t2;
        TriFace *a2 = p->t3;
        TriFace *b2 = p->s2;
        TriFace *c2 = p->t4;
        if(pos==1) {
            swapTriFaces(a1, b1);
            swapTriFaces(a2, c2);

        } else if(pos==2) {
            swapTriFaces(a1, c1);
            swapTriFaces(a2, b2);
        }
        a1->drawFade(f, ce0, ce1);
        a2->drawFade(f, ce0, ce1);
        b1->draw(ce0);
        b2->draw(ce0);
        c1->draw(ce0);
        c2->draw(ce0);

    }
};
