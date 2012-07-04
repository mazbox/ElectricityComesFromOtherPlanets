//
//  Tempo.cpp
//  SphereMapper
//
//  Created by Marek Bereza on 16/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Tempo.h"
float Tempo::bpm = 120;
void Tempo::set(float _bpm) {
	bpm = _bpm;
}