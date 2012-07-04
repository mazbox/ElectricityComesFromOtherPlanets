//
//  CubeCubeProgram.cpp
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "CubeCubeProgram.h"
#include "CubeCubes.h"

void CubeCubeProgram::constructGeometry() {
	in[0] = new QuadFace(mesh, 76,59,77,97);
	in[1] = new QuadFace(mesh, 76,104,64,82);
	in[2] = new QuadFace(mesh, 76,44,100,59);

	// the 3 mid-quads share their centrepoint
	ofVec3f mc = getIntersection(47, 64, 58, 57);

	mid[0] = createQuadFace(mc, mp(71), mp(66), mp(65));
	mid[1] = createQuadFace(mc, mp(65), mp(43), mp(48));
	mid[2] = createQuadFace(mc, mp(48), mp(54), mp(86));
	
	mid[0]->flipNormals();
	mid[1]->flipNormals();
	mid[2]->flipNormals();
	
	out[0].set(mesh, 1, 5, 10, 2, 4, 8);
	out[1].set(mesh, 10, 25, 88, 9, 65, 34);
	out[2].set(mesh, 33, 29, 1, 34, 37, 2);
}


void CubeCubeProgram::initializeSubprograms() {
	
	
	subprograms[0] = new CubeCube0();
	subprograms[1] = new CubeCube1();
	subprograms[2] = new CubeCube2();
	subprograms[3] = new CubeCube3();
	subprograms[4] = new CubeCube4();
	subprograms[5] = new CubeCube5();
	subprograms[6] = new CubeCube6();
	subprograms[7] = new CubeCube7();
	subprograms[8] = new CubeCube8();
	
	
}

