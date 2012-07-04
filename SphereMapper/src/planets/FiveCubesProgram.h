

#include "PlanetProgram.h"


#pragma once



struct Cube {
    QuadFace *inner;
    QuadFace *left;
    QuadFace *right;
};


class FiveCubesProgram: public PlanetProgram {
public:

    Cube cubes[5];

   


	void constructGeometry();
	void initializeSubprograms();
	
};
