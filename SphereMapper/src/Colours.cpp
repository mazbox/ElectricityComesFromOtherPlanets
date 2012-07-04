//
//  Colours.cpp
//  SphereMapper
//
//  Created by Marek Bereza on 14/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Colours.h"
vector<vector<ofFloatColor> > Colours::colours;
void Colours::load() {
	ofxXmlSettings xml;
	bool found = xml.loadFile("settings/colours.html");
	if(!found) {
		printf("Error! couldn't find settings/colours.html!\n");
	}
	
	xml.pushTag("html");
	xml.pushTag("body");
	xml.pushTag("table");
	int numSets = xml.getNumTags("tr");
	//printf("Found %d colour sets\n", numSets);
	for(int i = 0; i < numSets; i++) {
		colours.push_back(vector<ofFloatColor>());
		xml.pushTag("tr", i);
		{
			int numColours = xml.getNumTags("td");
			for(int j = 0; j < numColours; j++) {
				string c = xml.getAttribute("td", "bgcolor", "", j);
				colours.back().push_back(parseHexToColour(c));
				//printf("Colour %s - %f %f %f\n", c.c_str(), colours.back().back().r, colours.back().back().g, colours.back().back().b);

			}
		}
		xml.popTag();
	}
}

int valForHex(char c) {
	if(c>='0' && c<='9') {
		return c - '0';
	} else if(c>='A' && c<='F') {
		return 10 + c - 'A';
	} else if(c>='a' && c<='f') {
		return 10 + c - 'a';
	}
	printf("Couldn't parse hex character '%c'\n", c);
	return -1;
}
int twoCharHexToInt(string s) {
	
	int a = valForHex(s[0]);
	int b = valForHex(s[1]);

	return a * 16 + b;
}

ofFloatColor Colours::parseHexToColour(string hex) {
	string rs = hex.substr(1, 2);
	string gs = hex.substr(3, 2);
	string bs = hex.substr(5, 2);
	float r = twoCharHexToInt(rs);
	float g = twoCharHexToInt(gs);
	float b = twoCharHexToInt(bs);

	return ofFloatColor(r/255.f, g/255.f, b/255.f);
}

ofFloatColor Colours::get(int group, int offset) {
	return colours[group][offset];
}

int Colours::size() {
	return colours.size();
}