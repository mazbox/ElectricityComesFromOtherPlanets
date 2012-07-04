//
//  VolcanoProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PlanetProgram.h"

#pragma once

class VolcanoProgram: public PlanetProgram {
public:
	
    Fan centre;
    Fan quarters[4];


    void makeQuarter(int i, int a, int b, int c, int d, int e);

    void constructGeometry();
	void initializeSubprograms();
	
};
