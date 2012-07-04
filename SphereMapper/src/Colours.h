//
//  Colours.h
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofxXmlSettings.h"
class Colours {
public:
	static vector<vector<ofFloatColor> > colours;
	static void load();
	static ofFloatColor parseHexToColour(string hex);
	static ofFloatColor get(int group, int offset);
	static int size();
};