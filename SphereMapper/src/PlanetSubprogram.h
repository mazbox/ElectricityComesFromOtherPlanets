//
//  PlanetSubprogram.h
//  SphereMapper
//
//  Created by Marek Bereza on 28/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SphereMapper_PlanetSubprogram_h
#define SphereMapper_PlanetSubprogram_h


class PlanetProgram;
class PlanetSubprogramInterface {
public:	
	virtual void init() {}
	virtual void noteOn(int note) {};
	virtual void update() {}
	virtual void draw(float alpha) = 0;
	
	// for debugging
	virtual void keyPressed(int key) {}
	
	// don't implement this, this is the magic.
	virtual void setParent(PlanetProgram *parent) = 0;
};

template<typename T>
class PlanetSubprogram: public PlanetSubprogramInterface {
public:
	T *p;
	void setParent(PlanetProgram *parent) {
		this->p = (T*)parent;
	}
};

#endif
