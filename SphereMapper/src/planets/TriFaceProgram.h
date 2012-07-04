//
//  TriFaceProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PlanetProgram.h"

#pragma once


class TriFaceProgram: public PlanetProgram {
public:
    Fan inner;

    Fan bot;
    Fan left;
    Fan right;

	void constructGeometry();
	void initializeSubprograms();
	
};
