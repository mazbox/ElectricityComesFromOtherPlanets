
#pragma once

struct Ladder {
    int p1, p2, p3;
    bool flip;
    Ladder() {
        flip = false;
        p1 = p2 = p3 = -1;
        m = NULL;
    }

    ofMesh *m;

    vector<TriFace*> ladder;


    void point(int i) {
        if(m==NULL) {
            printf("Please set m (the mesh) on your ladder!\n");
            return;
        }
        p3 = p2;
        p2 = p1;
        p1 = i;


        if(p1!=-1 && p2!=-1 && p3!=-1) {
            if(flip) {
                ladder.push_back(new TriFace(m, p1, p2, p3));
            } else {
                ladder.push_back(new TriFace(m, p2, p1, p3));
            }
            flip ^= true;
        }

    }
    void drawFadeSkip(float f, int start, int step, const ofFloatColor &a, const ofFloatColor &b) {
        for(int i = start; i < ladder.size(); i+=step) {
            ladder[i]->drawFade(f, a, b);
        }
	}
	void drawFadeAlternate(float f1, float f2, const ofFloatColor &a, const ofFloatColor &b) {
        for(int i = 0; i < ladder.size(); i++) {
        	if(i%2==0) {
				ladder[i]->drawFade(f1, a, b);
        	} else {
				ladder[i]->drawFade(f2, a, b);
        	}
        }
	}
	void drawGrowAlternate(float f1, float f2, const ofFloatColor &a, const ofFloatColor &b) {
        for(int i = 0; i < ladder.size(); i++) {
        	if(i%2==0) {
				ladder[i]->drawSlide(f1,0, a, b);
        	} else {
				ladder[i]->drawSlide(f2, 0,a, b);
        	}
        }
	}
	void drawGrowSkip(float f, int start, const ofFloatColor &a, const ofFloatColor &b) {
        for(int i = start; i < ladder.size(); i+=2) {
			ladder[i]->drawSlide(f,0, a, b);
        }
	}
	void drawFanAlternate(float f1, float f2, const ofFloatColor &a, const ofFloatColor &b) {
        for(int i = 0; i < ladder.size(); i++) {
        	if(i%2==0) {
				ladder[i]->drawFan(f1,0,1, a, b);
        	} else {
				ladder[i]->drawFan(f2, 0,1,a, b);
        	}
        }
	}

	void drawSweepAlternate(float f1, float f2, const ofFloatColor &a, const ofFloatColor &b) {
        for(int i = 0; i < ladder.size(); i++) {
        	if(i%2==0) {
				ladder[i]->drawSweep(f1, a, b);
        	} else {
				ladder[i]->drawSweep(f2,a, b);
        	}
        }
	}

	void drawGrad(float rotation, const ofFloatColor &a, const ofFloatColor &b, const ofFloatColor &c) {
		for(int i = 0; i < ladder.size(); i++) {
			ladder[i]->drawGrad(rotation, a, b, c);
		}
	}

    void draw(const ofFloatColor &c) {
        for(int i = 0; i <ladder.size(); i++) {
            ladder[i]->draw(c);
        }
    }

    void drawStep(float f, const ofFloatColor &a, const ofFloatColor &b) {
       float count = round(f * ladder.size());

        for(int i = 0; i < ladder.size(); i++) {
            if(i<count) {
                ladder[i]->draw(a);
            } else {
                ladder[i]->draw(b);
            }
        }
    }
};
