//
//  TriProgram.cpp
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "TriProgram.h"
#include "Tris.h"


void TriProgram::constructGeometry() {

	t1 = new TriFace(mesh, 2, 1, 0);
	t2 = new TriFace(mesh, 2, 7, 6);
	t3 = new TriFace(mesh, 2, 6, 9);
	t4 = new TriFace(mesh, 14, 13, 12);

	s1 = new TriFace(mesh, 5, 4, 3);
	s2 = new TriFace(mesh, 11, 10, 9);

	fan1 = new Fan();
	fan2 = new Fan();
	fan2->m = fan1->m = mesh;

	fan1->point(0);
	fan1->point(2);
	fan1->point(1);
	fan1->point(4);
	fan1->point(2);

	fan2->point(9);
	fan2->point(14);
	fan2->point(11);
	fan2->point(10);
	fan2->point(14);

	leftFan = new Fan();
	leftFan->m = mesh;
	leftFan->point(8);
	leftFan->point(12);
	leftFan->point(17);
	leftFan->point(15);
	leftFan->point(0);
	leftFan->point(1);
	leftFan->flipNormals();


}
void TriProgram::initializeSubprograms() {


	subprograms[0] = new Tri0();
	subprograms[1] = new Tri1();
	subprograms[2] = new Tri2();
	subprograms[3] = new Tri3();
	subprograms[4] = new Tri4();
	subprograms[5] = new Tri5();
	subprograms[6] = new Tri6();
	subprograms[7] = new Tri7();
	subprograms[8] = new Tri8();


}





