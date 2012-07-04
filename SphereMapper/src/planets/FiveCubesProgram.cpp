

#include "FiveCubesProgram.h"

#include "FiveCubes.h"

void FiveCubesProgram::constructGeometry() {



	cubes[0].left = createQuadFace(getIntersection(55, 30, 89, 29), mp(30), mp(34), mp(29));
	cubes[0].right = createQuadFace(mp(29), mp(99), mp(101), getIntersection(101,97, 105, 88));
	cubes[0].inner = createQuadFace(mp(79), getIntersection(78, 79, 89, 88), mp(88), getIntersection(88, 105, 85, 79));


	cubes[1].left = createQuadFace(getIntersection(106, 60, 66, 64), mp(60), mp(71), mp(72));
	cubes[1].right = createQuadFace(mp(72), mp(73), mp(128), getIntersection(132,128, 125, 123));
	cubes[1].inner = createQuadFace(mp(110), getIntersection(85, 110, 86, 66), mp(66), getIntersection(110, 108, 116, 123));

	cubes[2].left = createQuadFace(getIntersection(15,16, 189, 186), mp(186), mp(197), mp(15));
	cubes[2].right = createQuadFace(mp(15), mp(153), mp(152), getIntersection(174,152, 167, 15));
	cubes[2].inner = createQuadFace(mp(5), getIntersection(10, 5, 15, 9), mp(15), getIntersection(15, 8, 2, 145));

	cubes[3].left = createQuadFace(getIntersection(143,142, 162, 159), mp(159), mp(170), mp(142));
	cubes[3].right = createQuadFace(mp(181), mp(180), mp(179), getIntersection(178,179, 45, 147));
	cubes[3].inner = createQuadFace(mp(140), getIntersection(137, 140, 144, 142), mp(142), getIntersection(149, 147, 148, 140));

	cubes[4].left = createQuadFace(getIntersection(21,22, 24, 20), mp(21), mp(23), mp(20));
	cubes[4].right = createQuadFace(mp(58), mp(57), mp(53), getIntersection(52,53, 205, 20));
	cubes[4].inner = createQuadFace(mp(41), getIntersection(46, 41, 21, 22), mp(43), getIntersection(43, 50, 41, 49));

	for(int i = 0; i < 5; i++) {
		cubes[i].left->flipNormals();
		cubes[i].right->flipNormals();
		cubes[i].inner->flipNormals();
	}
}



void FiveCubesProgram::initializeSubprograms() {
	
	
	subprograms[0] = new FiveCubes0();
	subprograms[1] = new FiveCubes1();
	subprograms[2] = new FiveCubes2();
	subprograms[3] = new FiveCubes3();
	subprograms[4] = new FiveCubes4();
	subprograms[5] = new FiveCubes5();
	subprograms[6] = new FiveCubes6();
	subprograms[7] = new FiveCubes7();
	subprograms[8] = new FiveCubes8();
	
	
}



