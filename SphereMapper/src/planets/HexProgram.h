//
//  TriProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "PlanetProgram.h"

#pragma once

class HexProgram: public PlanetProgram {
public:

	
	

	QuadFace *outerTopQuad;
	QuadFace *innerTopQuad;
	QuadFace *innerBotQuad;
	QuadFace *outerBotQuad;
	TriFace *topTri;
	TriFace *botTri;


	void constructGeometry();
	void initializeSubprograms();
	
	
};
