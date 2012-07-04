
#pragma once

struct Fan {
	int centre, p1, p2;
	Fan() {
		centre = p1 = p2 = -1;
		m = NULL;
	}
	ofMesh *m;

	void flipNormals() {
		for(int i = 0; i < fan.size(); i++) {
			fan[i]->flipNormals();
		}
	}
	vector<TriFace*> fan;
	void point(int i) {
		if(m==NULL) {
			printf("Please set m (the mesh) on your fan!\n");
			return;
		}
		if(centre==-1) {
			centre = i;
			return;
		}

		p2 = p1;
		p1 = i;

		if(p1!=-1 && p2!=-1) {
			fan.push_back(new TriFace(m, centre, p2, p1));
		}
	}
	void draw(const ofFloatColor &c) {
		for(int i = 0; i <fan.size(); i++) {
			fan[i]->draw(c);
		}
	}
	
	void drawGrad(float f, const ofFloatColor &a,const ofFloatColor &b,const ofFloatColor &c) {
		for(int i = 0; i < fan.size(); i++) {
			if(i%2==0) {
				fan[i]->drawGrad(f, a, b, c);
			} else {
				fan[i]->drawGrad(f, a, c, b);
			}
		}
	}
		
	void drawFadeSkip(float f, int start, int step, const ofFloatColor &a, const ofFloatColor &b) {
        for(int i = start; i < fan.size(); i+=step) {
            fan[i]->drawFade(f, a, b);
        }
	}

	void drawFade(float f, const ofFloatColor &a, const ofFloatColor &b) {
        for(int i = 0; i < fan.size(); i++) {
            fan[i]->drawFade(f, a, b);
        }
	}

	void drawOne(float f, int pos, const ofFloatColor &a, const ofFloatColor &b) {
		for(int i = 0; i < fan.size(); i++) {
			if(i==pos) {
				fan[i]->drawFade(f, a, b);
			} else {
				fan[i]->draw(b);
			}
        }

	}

    void drawGrow(float f, const ofFloatColor &a, const ofFloatColor &b) {
        for(int i = 0; i < fan.size(); i++) {
            fan[i]->drawSlide(f, 0, a, b);
        }
    }

	void drawFadeFan(float f, const ofFloatColor &a, const ofFloatColor &b) {
        float ff = f * fan.size();
        float count = floor(ff);
        float fraction = ff - count;

        for(int i = 0; i < fan.size(); i++) {
            if(i<count) {
                fan[i]->draw(a);
            } else if(i==count) {
                fan[i]->drawFade(fraction, a, b);
            } else {
                fan[i]->draw(b);
            }
        }
	}

	void drawSmoothFan(float f, const ofFloatColor &a, const ofFloatColor &b) {
        float ff = f * fan.size();
        float count = floor(ff);
        float fraction = ff - count;

        for(int i = 0; i < fan.size(); i++) {
            if(i<count) {
                fan[i]->draw(a);
            } else if(i==count) {
                fan[i]->drawFan(fraction, 0, 1, a, b);
            } else {
                fan[i]->draw(b);
            }
        }
	}
	void drawFan(float f, const ofFloatColor &a, const ofFloatColor &b) {
        float count = round(f * fan.size());

        for(int i = 0; i < fan.size(); i++) {
            if(i<count) {
                fan[i]->draw(a);
            } else {
                fan[i]->draw(b);
            }
        }
	}

	void drawFans(float f, const ofFloatColor &a, const ofFloatColor &b) {
	    for(int i = 0; i < fan.size(); i++) {
            fan[i]->drawFan(f, 0, 1, a, b);
	    }
	}
	void drawFans2(float f, const ofFloatColor &a, const ofFloatColor &b) {
	    for(int i = 0; i < fan.size(); i++) {
            fan[i]->drawFan(f, 1, 2, a, b);
	    }
	}
	void drawZoom(float f, const ofFloatColor &a, const ofFloatColor &b) {
	    for(int i = 0; i < fan.size(); i++) {
            fan[i]->drawSlide(f, 0, a, b);
	    }
	}
};
