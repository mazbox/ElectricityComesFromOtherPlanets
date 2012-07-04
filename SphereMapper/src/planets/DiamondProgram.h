//
//  DiamondProgram.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PlanetProgram.h"

#pragma once


class DiamondProgram: public PlanetProgram {
public:

	Fan fan;
    Ladder ladder;


	void constructGeometry();
	void initializeSubprograms();


};
