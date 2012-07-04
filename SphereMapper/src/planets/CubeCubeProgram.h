//
//  CubeCubeProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "PlanetProgram.h"

#pragma once

#include "L.h"

class CubeCubeProgram: public PlanetProgram {
public:


	
	
    QuadFace *in[3];
	QuadFace *mid[3];
    L out[3];


	void constructGeometry();
	void initializeSubprograms();


   
};
