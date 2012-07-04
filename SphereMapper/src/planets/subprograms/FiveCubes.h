//
//  VolcanoProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PlanetProgram.h"

#pragma once

class FiveCubes1: public PlanetSubprogram<FiveCubesProgram> {
public:

	int pos;
	Trigger trig[5];
    //int s;
	void init() {
	    pos = 5;
	    for(int i = 0; i < 5; i++) {
            trig[i].setDuration(0.7);
	    }
	}


	void noteOn(int note) {

		if(note==0) {

			trig[pos].trigger();
            pos++;
            pos %= 5;


		} else if (note==1) {

           // s++;
          //  s %= 2;
           // if(s>1) s = 1;
		}

	}

    void update() {
		float t = ofGetElapsedTimef()*4;
		p->moveLight(5*cos(t), 5*sin(t), 10);
		//light->setAttenuation(1, 0.4, 0.4);
	}

	void draw(float alpha) {
		glEnable(GL_DEPTH_TEST);


		float t = ofGetElapsedTimef();

		ofEnableLighting();



		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;




		for(int i = 0; i < 5; i++) {

			float val = fadeDown(easeOutCubic(trig[i].getValue(t)));

			//p->cubes[i].inner->drawFade(val, c0, c1);
			//if(s)
			p->cubes[i].left->drawFade(val, c0, c1);
			p->cubes[i].right->draw(c1);
			p->cubes[i].inner->draw(c1);

			//else p->cubes[i].right->drawFade(val, c0, c1);
		}

		glDisable(GL_DEPTH_TEST);
	}
};




class FiveCubes0: public PlanetSubprogram<FiveCubesProgram> {
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

		float t = ofGetElapsedTimef();
		t /= 4;
		t -= (int) t;

		for(int i = 0; i < 5; i++) {


			p->cubes[i].inner->drawGrad(t, c0, c1, c2, c3);

			p->cubes[i].left->drawGrad(t, c0, c1, c2, c3);
			p->cubes[i].right->drawGrad(t, c0, c1, c2, c3);

		}
	}

};


class FiveCubes2: public PlanetSubprogram<FiveCubesProgram> {
public:

	int pos;
	Trigger trig[5];
	Trigger tamb;
    int s;
	void init() {
	    s = 0;
	    pos = 5;
	    tamb.setDuration(0.6);
	    for(int i = 0; i < 5; i++) {
            trig[i].setDuration(0.7);
	    }
	}


	void noteOn(int note) {

		if(note==12) {

			trig[pos].trigger();
            pos++;
            pos %= 5;


		} else if (note==16) {
		    tamb.trigger();

		} else if(note==14) {
            s++;
            s %= 2;
            if(s>1) s = 1;
		}

	}



	void draw(float alpha) {
		glEnable(GL_DEPTH_TEST);


		float t = ofGetElapsedTimef();

		ofEnableLighting();



		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];
		ofFloatColor wh = p->colours[1];

		c0.a = alpha;
		c1.a = alpha;
		wh.a = alpha;




        float tmb = fadeDown(tamb.getValue(t));
		for(int i = 0; i < 5; i++) {

            int ii = i;
            if(s) {
                ii = 4 - i;
            }
			float val = fadeDown(trig[ii].getValue(t));

			p->cubes[i].inner->drawFade(tmb, wh, c1);
			if(s) {
                p->cubes[i].left->drawFade(val, c0, c1);
                p->cubes[i].right->draw(c1);

			} else {
                p->cubes[i].left->draw(c1);
                p->cubes[i].right->drawFade(val, c0, c1);
            }
		}

		glDisable(GL_DEPTH_TEST);
	}
};




class FiveCubes3: public PlanetSubprogram<FiveCubesProgram> {
public:

	int pos;
	Trigger trig[5];
	Trigger tamb;
    int s;
	void init() {
	    s = 0;
	    pos = 5;
	    tamb.setDuration(0.6);
	    for(int i = 0; i < 5; i++) {
            trig[i].setDuration(0.7);
	    }
	}


	void noteOn(int note) {

		if(note==24) {

			trig[pos].trigger();
            pos++;
            pos %= 5;


		} else if (note==26) {
		    tamb.trigger();

		} else if(note==28) {
            s++;
            s %= 2;
            if(s>1) s = 1;
		}

	}



	void draw(float alpha) {
		glEnable(GL_DEPTH_TEST);


		float t = ofGetElapsedTimef();

		ofEnableLighting();



		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];
		ofFloatColor wh = p->colours[1];


		c0.a = alpha;
		c1.a = alpha;
		wh.a = alpha;



        float tmb = fadeDown(tamb.getValue(t));
		for(int i = 0; i < 5; i++) {


			float val = fadeDown(trig[i].getValue(t));

			p->cubes[i].inner->drawGrow(tmb, 0, wh, c1);

            p->cubes[i].left->drawFade(val, c0, c1);
            p->cubes[i].right->drawFade(val, c0, c1);

		}

		glDisable(GL_DEPTH_TEST);
	}
};

class FiveCubes4: public PlanetSubprogram<FiveCubesProgram> {
public:

	int pos;
	Trigger trig;
	Trigger tamb;
    int s;
    bool sw;
	void init() {
	    s = 0;
	    sw = false;
	    pos = 5;
	    tamb.setDuration(0.6);
		trig.setDuration(0.9);
	}


	void noteOn(int note) {

		if(note==36) {

			trig.trigger();

			sw ^= true;

		} else if (note==26) {
		    tamb.trigger();

		} else if(note==28) {
            s++;
            s %= 2;
            if(s>1) s = 1;
		}

	}



	void draw(float alpha) {
	//	glEnable(GL_DEPTH_TEST);


		float t = ofGetElapsedTimef();

		ofEnableLighting();



		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];
		ofFloatColor wh = p->colours[1];


		c0.a = alpha;
		c1.a = alpha;
		wh.a = alpha;


        float tmb = fadeDown(trig.getValue(t));


		if(sw) swapColours(c0,c1);

		float val = (easeInQuad(trig.getValue(t)));
		for(int i = 0; i < 5; i++) {

			//if(sw) {

				p->cubes[i].left->drawSweep90(val, c0, c1);
				p->cubes[i].right->drawSweep270(val, c0, c1);
				p->cubes[i].inner->drawGrow(tmb, 2, wh, c1);
			//}
		}
//


		//glDisable(GL_DEPTH_TEST);
	}
};

class FiveCubes5: public PlanetSubprogram<FiveCubesProgram> {
public:

	int pos;
	Trigger trig;
	Trigger tamb;
    int s;
    bool sw;
	void init() {
	    s = 0;
	    sw = false;
	    pos = 5;
	    tamb.setDuration(0.65);
		trig.setDuration(0.9);
	}


	void noteOn(int note) {

		if(note==48) {

			trig.trigger();

			sw ^= true;

		} else if (note==26) {
		    tamb.trigger();

		} else if(note==28) {
            s++;
            s %= 2;
            if(s>1) s = 1;
		}

	}



	void draw(float alpha) {
		glEnable(GL_DEPTH_TEST);


		float t = ofGetElapsedTimef();

		ofEnableLighting();



		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];
		ofFloatColor wh = p->colours[1];
		ofFloatColor bl = c1;

		c0.a = alpha;
		c1.a = alpha;
		wh.a = alpha;
		bl.a = alpha;


        float tmb = fadeDown(trig.getValue(t));


		if(sw) swapColours(c0,c1);
		if(sw) swapColours(bl,wh);
		float val = (easeInQuad(trig.getValue(t)));
		for(int i = 0; i < 5; i++) {

			//if(sw) {

				p->cubes[i].left->drawSweep(val, c0, c1);
				p->cubes[i].right->drawSweep180(val, c0, c1);
				p->cubes[i].inner->drawSweep(tmb, wh, bl);
			//}
		}
//


	//	glDisable(GL_DEPTH_TEST);
	}
};

class FiveCubes6: public PlanetSubprogram<FiveCubesProgram> {
public:

	int pos;
	Trigger trig;
	Trigger tamb;
    int s;
    bool sw;
	void init() {
	    s = 0;
	    sw = false;
	    pos = 5;
	    tamb.setDuration(0.65);
		trig.setDuration(0.5);
	}


	void noteOn(int note) {

		if(note==60) {

			trig.trigger();

			sw ^= true;

		} else if (note==26) {
		    tamb.trigger();

		} else if(note==28) {
            s++;
            s %= 2;
            if(s>1) s = 1;
		}

	}



	void draw(float alpha) {
	//	glEnable(GL_DEPTH_TEST);


		float t = ofGetElapsedTimef();

		ofEnableLighting();



		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];
		ofFloatColor wh = p->colours[1];
		ofFloatColor bl = c1;

		c0.a = alpha;
		c1.a = alpha;
		wh.a = alpha;
		bl.a = alpha;


        float tmb = fadeDown(trig.getValue(t));


		if(sw) swapColours(c0,c1);
		if(sw) swapColours(bl,wh);
		float val = (easeInQuad(tamb.getValue(t)));
		for(int i = 0; i < 5; i++) {

			//if(sw) {

				p->cubes[i].left->drawSweep(val, c0, c1);
				p->cubes[i].right->drawSweep(val, c0, c1);
				p->cubes[i].inner->drawSweep(tmb, wh, bl);
			//}
		}
//


		//glDisable(GL_DEPTH_TEST);
	}
};

class FiveCubes7: public PlanetSubprogram<FiveCubesProgram> {
public:

	int pos;
	Trigger trig[5];
	Trigger cymb;
    //int s;
	void init() {
	    pos = 5;
	    cymb.setDuration(0.5);
	    for(int i = 0; i < 5; i++) {
            trig[i].setDuration(0.7);
	    }
	}


	void noteOn(int note) {

		if(note==72) {

			trig[pos].trigger();
            pos++;
            pos %= 5;


		} else if (note==74) {
			cymb.trigger();
           // s++;
          //  s %= 2;
           // if(s>1) s = 1;
		}

	}

    void update() {
		float t = ofGetElapsedTimef()*4;
		p->moveLight(5*cos(t), 5*sin(t), 10);
		//light->setAttenuation(1, 0.4, 0.4);
	}

	void draw(float alpha) {
		glEnable(GL_DEPTH_TEST);


		float t = ofGetElapsedTimef();

		ofEnableLighting();



		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];
		ofFloatColor c2 = p->colours[1];
		ofFloatColor c3 = p->colours[0];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;


	float cy = fadeDown(easeInCubic(cymb.getValue(t)));

		for(int i = 0; i < 5; i++) {

			float val = fadeDown(easeOutCubic(trig[i].getValue(t)));

			p->cubes[i].inner->drawFade(cy, c3, c1);
			//if(s)
			p->cubes[i].left->drawSweepInOut270(val, c0, c1);
			p->cubes[4-i].right->drawSweepInOut90(val, c1, c2);
			//else p->cubes[i].right->drawFade(val, c0, c1);
		}

		glDisable(GL_DEPTH_TEST);
	}
};



class FiveCubes8: public PlanetSubprogram<FiveCubesProgram> {
public:

	int pos;
	Trigger trig[5];
	Trigger cymb;
    //int s;
	void init() {
	    pos = 5;
	    cymb.setDuration(0.5);
	    for(int i = 0; i < 5; i++) {
            trig[i].setDuration(0.7);
	    }
	}


	void noteOn(int note) {

		if(note==84) {

			trig[pos].trigger();
            pos++;
            pos %= 5;


		} else if (note==86) {
			cymb.trigger();
           // s++;
          //  s %= 2;
           // if(s>1) s = 1;
		}

	}

    void update() {
		float t = ofGetElapsedTimef()*4;
		p->moveLight(5*cos(t), 5*sin(t), 10);
		//light->setAttenuation(1, 0.4, 0.4);
	}

	void draw(float alpha) {
		glEnable(GL_DEPTH_TEST);


		float t = ofGetElapsedTimef();

		ofEnableLighting();



		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];
		ofFloatColor c2 = p->colours[1];
		ofFloatColor c3 = p->colours[0];

		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;



	float cy = fadeDown(easeInCubic(cymb.getValue(t)));

		for(int i = 0; i < 5; i++) {

			float val = fadeDown(easeOutCubic(trig[i].getValue(t)));

			p->cubes[i].inner->drawFade(cy, c3, c1);
			//if(s)
			p->cubes[i].left->drawSweepInOut90(val, c0, c1);
			p->cubes[4-i].right->drawSweepInOut270(val, c1, c2);
			//else p->cubes[i].right->drawFade(val, c0, c1);
		}

		glDisable(GL_DEPTH_TEST);
	}
};
