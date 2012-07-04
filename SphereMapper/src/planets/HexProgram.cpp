//
//  TriProgram.cpp
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "HexProgram.h"
#include "Hexes.h"


void HexProgram::constructGeometry() {

	outerTopQuad = new QuadFace(mesh, 16, 20, 19, 17);
	outerTopQuad->flipNormals();
	innerTopQuad = new QuadFace(mesh, 23, 25, 26, 22);
	//innerTopQuad->flipNormals();
	innerBotQuad = new QuadFace(mesh, 7, 6, 10, 8);
	innerBotQuad->flipNormals();
	outerBotQuad = new QuadFace(mesh, 1, 5, 4, 2);
	outerBotQuad->flipNormals();
	topTri = new TriFace(mesh, 27, 29, 28);

	topTri->flipNormals();
	botTri = new TriFace(mesh, 12, 14, 13);
	botTri->flipNormals();

}

void HexProgram::initializeSubprograms() {


	subprograms[0] = new Hex0();
	subprograms[1] = new Hex1();
	subprograms[2] = new Hex2();
	subprograms[3] = new Hex3();
	subprograms[4] = new Hex4();
	subprograms[5] = new Hex5();
	subprograms[6] = new Hex6();
	subprograms[7] = new Hex7();
	subprograms[8] = new Hex8();


}

