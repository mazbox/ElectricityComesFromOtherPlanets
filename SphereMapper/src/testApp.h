#pragma once

#include "ofMain.h"
#include "ofxFourUpDisplay.h"
#include "Scene.h"
#include "SceneGui.h"
#include "PlanetProgram.h"
#include "ofxOsc.h"
#include "SimpleGui.h"
#include "OBJEditGui.h"
class testApp : public ofBaseApp, public xmlgui::Listener {

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void startEditing();
	void stopEditing();
    void controlChanged(xmlgui::Control *ctrl);

	ofxFourUpDisplay *fourup;
	Scene *scene;
	SceneGui *sceneGui;
	vector<Model*> models;
	map<int,PlanetProgram*> programs;
	ofxOscReceiver osc;
	xmlgui::SimpleGui gui;
	void createNewModelAndProgram(int midiChannel, string objPath, PlanetProgram *program, string settings);
	void createNewModelAndProgram(int midiChannel);
	int drawMode;
	void clearProgramsAndModels();
	OBJEditGui objEditor;
    void setWinState(int winState, int winMode);
	bool editMode;

};
