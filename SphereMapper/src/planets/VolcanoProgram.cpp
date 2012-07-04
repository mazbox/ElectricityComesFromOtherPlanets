//
//  VolcanoProgram.cpp
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "VolcanoProgram.h"
#include "Volcanoes.h"


void VolcanoProgram::constructGeometry() {
	
	centre.m = mesh;
	
	int centrePoints[] = {32, 30, 33, 24, 27, 30};
	for(int i = 0; i < sizeof(centrePoints)/sizeof(int); i++) {
		centre.point(centrePoints[i]);
	}
	
	makeQuarter(0,   38,37,36,41,14);
	makeQuarter(1,   14, 15,17,20,1);
	makeQuarter(2,   1,9,11,7,23);
	makeQuarter(3,   23,22,21,42,46);	
}


void VolcanoProgram::initializeSubprograms() {
	subprograms[0] = new Volcano0();
	subprograms[1] = new Volcano1();
	subprograms[2] = new Volcano2();
	subprograms[3] = new Volcano3();
	subprograms[4] = new Volcano4();
	subprograms[5] = new Volcano5();
	subprograms[6] = new Volcano6();
	subprograms[7] = new Volcano7();
	subprograms[8] = new Volcano8();
}


void VolcanoProgram::makeQuarter(int i, int a, int b, int c, int d, int e) {
	quarters[i].m = mesh;
	quarters[i].point(a);
	quarters[i].point(b);
	quarters[i].point(c);
	quarters[i].point(d);
	quarters[i].point(e);
}

