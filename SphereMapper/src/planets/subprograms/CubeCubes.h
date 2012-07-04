//
//  VolcanoProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PlanetProgram.h"

#pragma once

class CubeCube1: public PlanetSubprogram<CubeCubeProgram> {
public:
	Trigger triga;
    Trigger trigb;
    bool tog;
    void init() {
        triga.setDuration(0.5);
        trigb.setDuration(0.5);
        tog = false;
    }
	void noteOn(int note) {
		if(note==0) {
		    tog ^= true;
		    if(tog) {
                triga.trigger();
		    } else {
                trigb.trigger();
		    }
		}
		//printf("%d\n", note);
	}


	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();


		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];


		c0.a = alpha;
		c1.a = alpha;



        float fa = fadeDown(triga.getValue(t));
        float fb = fadeDown(trigb.getValue(t));
        fa = easeInCubic(fa);
        fb = easeInCubic(fb);

		for(int i = 0; i < 3; i++) {

			p->mid[i]->drawGrow(1.f - fa*0.1, 0, c1, c0);

			p->in[i]->drawGrow(1.f - fb*0.1, 0, c1, c0);

			p->out[i].drawEdge(fa*0.1, c0, c1);



		}



	}


};
class CubeCube0: public PlanetSubprogram<CubeCubeProgram> {
public:

	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();


		ofFloatColor c0 = p->colours[0];
		ofFloatColor c1 = p->colours[1];
		ofFloatColor c2 = p->colours[2];
		ofFloatColor c3 = p->colours[3];



		c0.a = alpha;
		c1.a = alpha;
		c2.a = alpha;
		c3.a = alpha;


		t/= 4.f;
		t -= (int) t;
		for(int i = 0; i < 3; i++) {

			p->mid[i]->drawGrad(t, c0, c1, c2, c3);

			p->in[i]->drawGrad(t, c0, c1, c2, c3);

			p->out[i].drawGrad(t, c0, c1, c2, c3);



		}



	}
};



class CubeCube2: public PlanetSubprogram<CubeCubeProgram> {
public:
	Trigger triga;
    Trigger trigb;
    Trigger trigc;

    int pos;
    void init() {
        triga.setDuration(0.5);
        trigb.setDuration(0.5);
        trigc.setDuration(0.5);
        pos = 0;
    }

	void noteOn(int note) {
		if(note==12) {
		    pos++;
		    pos %= 3;

		    if(pos==0) {
                triga.trigger();
		    } else if(pos==1) {
                trigb.trigger();
		    } else {
                trigc.trigger();
		    }
		}
		//printf("%d\n", note);
	}


	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();


		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];



		c0.a = alpha;
		c1.a = alpha;


        float fa = fadeDown(triga.getValue(t));
        float fb = fadeDown(trigb.getValue(t));
        float fc = fadeDown(trigc.getValue(t));

        fa = easeInCubic(fa);
        fb = easeInCubic(fb);
        fc = easeInCubic(fc);

		for(int i = 0; i < 3; i++) {
            float f = fa;
            if(i==1) {
                f = fb;
            } else if(i==2) {
                f = fc;
            }
            ofFloatColor c0 = p->colours[(2+i+pos)%3];
            ofFloatColor c1 = p->colours[3];
			p->mid[i]->drawGrow(1.f - f*0.25, 0, c1, c0);

			p->in[i]->drawGrow(1.f - f*0.25, 0, c1, c0);

			p->out[i].drawEdge(f*0.25, c0, c1);



		}



	}
};
class CubeCube3: public PlanetSubprogram<CubeCubeProgram> {
public:
	Trigger triga;
    Trigger trigb;
    Trigger trigc;

    int pos;
    int triPos;
    bool toggle;
    int edgePos;
    void init() {
    	edgePos = 0;
    	triPos = 0;
        triga.setDuration(0.25);
        trigb.setDuration(0.25);
        trigc.setDuration(0.2);
        pos = 0;
        toggle = false;
    }

	void noteOn(int note) {
		if(note==24) {
		    pos++;
		    pos %= 2;

		    if(pos==0) {
                triga.trigger();
		    } else if(pos==1) {
                trigb.trigger();
                toggle ^= true;
		    }
		} else if(note==26) {
			trigc.trigger();
			triPos++;
			triPos %= 3;
			if(triPos==0) {
				edgePos = (edgePos+1) % 3;
			}
		}
		//printf("%d\n", note);
	}


	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();


		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];

		c0.a = alpha;
		c1.a = alpha;




        float fa = fadeDown(triga.getValue(t));
        float fb = fadeDown(trigb.getValue(t));
        float fc = fadeDown(trigc.getValue(t));

        fa = easeInCubic(fa);
        fb = easeOutCubic((fb));
        fc = easeInCubic(fc);

		for(int i = 0; i < 3; i++) {
            float f = fa;
            if(i==1) {
                f = fb;
            } else if(i==2) {
                f = fc;
            }
            //ofFloatColor c0 = p->colours[(2+pos)%3];
            //ofFloatColor c1 = p->colours[3];
			p->mid[i]->drawGrow(1.f - fa*0.1, edgePos, c1, c0);



			p->out[i].drawEdge(fb*0.1, c0, c1);

           //if(toggle) swapColours(c1,c0);
            //p->in[i]->drawSweep(1.f - fb, c1, c0);

		}
		p->in[triPos]->drawGrow(1.f - fc*0.2,0, c1, c0);


	}
};
class CubeCube4: public PlanetSubprogram<CubeCubeProgram> {
public:
	Trigger triga;
    Trigger trigb;
    Trigger trigc;

    int pos;
    int triPos;
    bool toggle;
    int edgePos;
    void init() {
    	edgePos = 0;
    	triPos = 0;
        triga.setDuration(0.4);
        trigb.setDuration(0.4);
        trigc.setDuration(0.3);
        pos = 0;
        toggle = false;
    }

	void noteOn(int note) {
		if(note==36) {
		    pos++;
		    pos %= 2;

		    //if(pos==0) {
            //
		   // } else if(pos==1) {
           //     trigb.trigger();
           //     toggle ^= true;
		   // }
		} else if(note==38) {
			triga.trigger();
			trigc.trigger();
			triPos++;
			triPos %= 3;
			if(triPos==0) {
				edgePos = (edgePos+1) % 3;
			}
		}
		//printf("%d\n", note);
	}


	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();


		ofFloatColor c0 = p->colours[2];
		ofFloatColor c1 = p->colours[3];


		c0.a = alpha;
		c1.a = alpha;



        float fa = fadeDown(triga.getValue(t));
        float fb = fadeDown(trigb.getValue(t));
        float fc = fadeDown(trigc.getValue(t));

        fa = easeInCubic(fa);
        fb = easeOutCubic((fb));
        fc = easeInCubic(fc);

		for(int i = 0; i < 3; i++) {
            float f = fa;
            if(i==1) {
                f = fb;
            } else if(i==2) {
                f = fc;
            }
            //ofFloatColor c0 = p->colours[(2+pos)%3];
            //ofFloatColor c1 = p->colours[3];
			p->mid[i]->drawGrow(1.f - fa*0.1, 0, c1, c0);



			p->out[i].drawEdge(fb*0.1, c0, c1);

           //if(toggle) swapColours(c1,c0);
            //p->in[i]->drawSweep(1.f - fb, c1, c0);

		}
		p->in[triPos]->drawGrow(1.f - fc*0.2,edgePos, c1, c0);


	}
};


class CubeCube5: public PlanetSubprogram<CubeCubeProgram> {
public:
	Trigger bd;
    Trigger sd;

    void init() {
        bd.setDuration(0.7);
        sd.setDuration(0.4);
    }

	void noteOn(int note) {
		if(note==48) {
		    bd.trigger();
		} else if(note==52) {
            sd.trigger();
		}
	}


	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();



        float fb = fadeDown(bd.getValue(t));
        float fs = fadeDown(sd.getValue(t));

        fb = easeInCubic(fb);
        fs = easeOutCubic((fs));

		for(int i = 0; i < 3; i++) {
ofFloatColor c2 = p->colours[(1)];
            ofFloatColor c0 = p->colours[(2)];
            ofFloatColor c1 = p->colours[3];

			c0.a = alpha;
			c1.a = alpha;

			p->out[i].drawEdge(fb, c2, c1);

            p->mid[i]->drawGrow(fs, 0, c0, c1);
            p->in[i]->drawGrow(fs, 0, c0, c1);

		}
	}
};
class CubeCube6: public PlanetSubprogram<CubeCubeProgram> {
public:
	Trigger bd;
    Trigger sd;

    Trigger hh;
    Trigger cy;

    void init() {
        hh.setDuration(0.2);
        bd.setDuration(0.7);
        sd.setDuration(0.4);
        cy.setDuration(1.5);
    }

	void noteOn(int note) {
		if(note==60) {
		    bd.trigger();
		} else if(note==64) {
            sd.trigger();
		} else if(note==67){
            hh.trigger();
		} else if(note==69) {
            cy.trigger();
		}
		printf("%d\n", note);
	}


	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();



        float fb = fadeDown(bd.getValue(t));
        float fs = fadeDown(sd.getValue(t));
        float fh = fadeDown(hh.getValue(t));
        float fc = fadeDown(cy.getValue(t));
        fb = easeInCubic(fb);
        fs = easeOutCubic((fs));
        fc = easeInCubic(fc);
		for(int i = 0; i < 3; i++) {
ofFloatColor c2 = p->colours[(1)];
            ofFloatColor c0 = p->colours[(2)];
            ofFloatColor c1 = p->colours[3];

			c0.a = alpha;
			c1.a = alpha;


			p->out[i].drawEdge(fc*0.5
							   , c2, c1);

            p->mid[i]->drawGrow(fb, 2, c0, c1);
            p->in[i]->drawGrow(fs, 2, c0, c1);

		}
	}
};
class CubeCube7: public PlanetSubprogram<CubeCubeProgram> {
public:
	Trigger bd;
    Trigger sd;

    Trigger hh;
    Trigger cy;

    void init() {
        hh.setDuration(0.2);
        bd.setDuration(1);
        sd.setDuration(0.7);
        cy.setDuration(1.5);
    }

	void noteOn(int note) {
		if(note==72) {
		    bd.trigger();
		} else if(note==76) {
            sd.trigger();
		} else if(note==79){
            hh.trigger();
		} else if(note==81) {
            cy.trigger();
		}
		printf("%d\n", note);
	}


	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();



        float fb = fadeDown(bd.getValue(t));
        float fs = fadeDown(sd.getValue(t));
        float fh = fadeDown(hh.getValue(t));
        float fc = fadeDown(cy.getValue(t));
        fb = easeInCubic(fb);
        fs = easeOutCubic((fs));
        fc = easeInCubic(fc);
		for(int i = 0; i < 3; i++) {
ofFloatColor c2 = p->colours[(1)];
            ofFloatColor c0 = p->colours[(2)];
            ofFloatColor c1 = p->colours[3];
			c0.a = alpha;
			c1.a = alpha;


			p->out[i].drawEdge(fc, c0, c1);

            p->mid[i]->drawGrow(fb, 2, c2, c1);
            p->in[i]->drawSweep(fs, c0, c1);

		}
	}
};
class CubeCube8:public PlanetSubprogram<CubeCubeProgram> {
public:
	Trigger bd;
    Trigger sd;

    Trigger hh;
    Trigger cy;
	bool switcheroo;
    void init() {
    	switcheroo = false;
        hh.setDuration(0.2);
        bd.setDuration(1);
        sd.setDuration(0.7);
        cy.setDuration(1.5);
    }

	void noteOn(int note) {
		if(note==84) {
		    bd.trigger();
		} else if(note==88) {
            sd.trigger();
            switcheroo ^= true;
		} else if(note==91){
            hh.trigger();
		} else if(note==93) {
            cy.trigger();
		}
		printf("%d\n", note);
	}


	void draw(float alpha) {
		float t = ofGetElapsedTimef();
		ofEnableLighting();



        float fb = fadeDown(bd.getValue(t));
        float fs = fadeDown(sd.getValue(t));
        float fh = fadeDown(hh.getValue(t));
        float fc = fadeDown(cy.getValue(t));
        fb = easeInCubic(fb);
        fs = easeOutCubic((fs));
        fc = easeInCubic(fc);
		for(int i = 0; i < 3; i++) {
			ofFloatColor c2 = p->colours[(1)];
            ofFloatColor c0 = p->colours[(2)];
            ofFloatColor c1 = p->colours[3];

			c0.a = alpha;
			c1.a = alpha;
			c2.a = alpha;


			p->out[i].drawEdge(fb, c0, c1);


            p->in[i]->drawSweepInOut(fc, c0, c1);
            //if(switcheroo) swapColours(c2, c1);
            p->mid[i]->drawSweep(fs, c1, c2);

		}
	}
};
