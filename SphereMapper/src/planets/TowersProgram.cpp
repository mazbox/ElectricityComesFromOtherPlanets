//
//  TowersProgram.cpp
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "TowersProgram.h"
#include "Towersez.h"



void TowersProgram::constructGeometry() {

	top = new QuadFace(mesh, 4, 5, 1, 3);
	top->flipNormals();
	bot = new QuadFace(mesh, 156, 158,142,143);
	bot->flipNormals();
	left = new QuadFace(mesh, 160, 159, 57,158);
	right = new QuadFace(mesh, 175,1,177,91);
	right->flipNormals();

	lMid.up = new QuadFace(mesh, 38, 44, 68, 45);
	lMid.up->flipNormals();
	rMid.up = new QuadFace(mesh, 105, 107, 190, 189);

	lMid.down = new QuadFace(mesh, 55, 54, 152, 151);
	rMid.down = new QuadFace(mesh, 185, 183, 94, 95);
    rMid.down->flipNormals();

	lMid.in = new QuadFace(mesh, 45,68,69,151);
	lMid.in->flipNormals();

	rMid.in = new QuadFace(mesh,45,190,76, 151);

	lMid.out = new QuadFace(mesh, 31,68,69,149);
	rMid.out = new QuadFace(mesh, 197,190,94,100);
	rMid.out->flipNormals();

	lOut.in = new TriFace(mesh, 20,12,18);
	rOut.in = new TriFace(mesh, 124,80,123);
	rOut.in->flipNormals();

	lOut.out = new TriFace(mesh, 6, 7, 8);
	lOut.out->flipNormals();
	rOut.out = new TriFace(mesh, 124, 132, 111);

	lOut.up = new QuadFace(mesh, 11, 9, 6, 12);
	lOut.up->flipNormals();
	rOut.up = new QuadFace(mesh, 127, 126, 134, 80);

	lOut.down = new QuadFace(mesh, 28, 27, 22, 49);
	rOut.down = new QuadFace(mesh, 122, 111, 112, 114);
	rOut.down->flipNormals();
}



void TowersProgram::initializeSubprograms() {


	subprograms[0] = new Towers0();
	subprograms[1] = new Towers1();
	subprograms[2] = new Towers2();
	subprograms[3] = new Towers3();
	subprograms[4] = new Towers4();
	subprograms[5] = new Towers5();
	subprograms[6] = new Towers6();
	subprograms[7] = new Towers7();
	subprograms[8] = new Towers8();


}




