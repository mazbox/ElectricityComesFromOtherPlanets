//
//  TriFaceProgram.cpp
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "TriFaceProgram.h"

#include "TriFaces.h"

void TriFaceProgram::constructGeometry() {

	bot.m = left.m = right.m = inner.m = mesh;
	inner.point(0);
	inner.point(5);
	inner.point(1);
	inner.point(7);
	inner.point(5);

	bot.point(17);
	bot.point(31);
	bot.point(30);
	bot.point(15);
	bot.point(20);

	left.point(9);
	left.point(25);
	left.point(24);
	left.point(5);
	left.point(35);

	right.point(12);
	right.point(20);
	right.point(21);
	right.point(8);
	right.point(29);


}

void TriFaceProgram::initializeSubprograms() {
	
	
	subprograms[0] = new TriFace0();
	subprograms[1] = new TriFace1();
	subprograms[2] = new TriFace2();
	subprograms[3] = new TriFace3();
	subprograms[4] = new TriFace4();
	subprograms[5] = new TriFace5();
	subprograms[6] = new TriFace6();
	subprograms[7] = new TriFace7();
	subprograms[8] = new TriFace8();
	
	
}


