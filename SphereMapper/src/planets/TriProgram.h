//
//  TriProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PlanetProgram.h"

#pragma once


class TriProgram: public PlanetProgram {
public:
    TriFace *t1, *t2, *t3, *t4;
    TriFace *s1, *s2;
	Fan *fan1;
	Fan *fan2;


	// this one is optional, it's a fan made from the left 4 shapes.
	Fan* leftFan;

	void constructGeometry();
	void initializeSubprograms();

};
