//
//  DiamondProgram.cpp
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "DiamondProgram.h"
#include "Diamonds.h"


void DiamondProgram::constructGeometry() {
	fan.m = mesh;
	int fanPoints[] = {0,1,3,6,9,12,15,20,23,27,29,2,1};
	for(int i = 0; i < sizeof(fanPoints)/sizeof(int); i++) {
		fan.point(fanPoints[i]);
	}

	ladder.m = mesh;
	int ladderPoints[] = {1,63,67,69,73,75,31,34,37,40,43,79,21,88,90,91,97,98,52,55,58,59,1, 63};
	for(int i = 0; i < sizeof(ladderPoints)/sizeof(int); i++) {
		ladder.point(ladderPoints[i]);
	}
}



void DiamondProgram::initializeSubprograms() {
	
	
	subprograms[0] = new Diamond0();
	subprograms[1] = new Diamond1();
	subprograms[2] = new Diamond2();
	subprograms[3] = new Diamond3();
	subprograms[4] = new Diamond4();
	subprograms[5] = new Diamond5();
	subprograms[6] = new Diamond6();
	subprograms[7] = new Diamond7();
	subprograms[8] = new Diamond8();
	
	
}



