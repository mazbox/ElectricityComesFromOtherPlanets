/**
 * This file starts up the app with settings in data/settings.xml
 */

#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "testApp.h"
#include "ofxSettings.h"

float WIDTH = 1024;
float HEIGHT = 768;
bool  useMSAA = false;

//========================================================================
int main( ){
	//ofSetDataPathRoot("../../../data/");
	settings.load("settings/general.xml");

	// the width of the app is set by how many projectors we have and if we are using one screen
	// soley for the gui. The gui screen is as wide as the projectors.

	WIDTH =  settings.getInt("projector width", WIDTH);

	// height of the app is determined by the projector height
	HEIGHT = settings.getInt("projector height", HEIGHT);

	useMSAA = settings.getBool("using MSAA", false);
	ofAppGlutWindow window;

	if(useMSAA) {
		//glutInitDisplayString("rgb double depth>=16 alpha samples<=16");

		window.setGlutDisplayString("rgb double depth>=16 alpha samples<=4"); // ati?
		//window.setGlutDisplayString(settings.get("glutDisplayString", "rgb double depth>=16 alpha samples<=4"));
	}

	ofSetupOpenGL(&window, WIDTH, HEIGHT, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
