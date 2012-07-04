#include "testApp.h"

#include "TriProgram.h"
#include "HexProgram.h"
#include "FiveCubesProgram.h"
#include "CubeCubeProgram.h"

#include "DiamondProgram.h"
#include "TowersProgram.h"
#include "TriFaceProgram.h"
#include "VolcanoProgram.h"


//#include "ofxWebServer.h"

ofShader plShader;

#include "Colours.h"
#define PROGRAM 0
#define FACES 1
#define SHADED 2
#define TEXTURED 3
#define LINES 4
int modelPos = 0;
ofImage debugTex;

int simulatePos = 0;

ofShader fxaa;
ofFbo fbo;

bool enableFbo = true;

void testApp::createNewModelAndProgram(int midiChannel) {
    switch(midiChannel) {
        case 1:
            createNewModelAndProgram(midiChannel, "models/hexsimple.obj", new HexProgram(), "settings/hex.xml");
            break;


        case 2:
            createNewModelAndProgram(midiChannel, "models/volcanosimple.obj", new VolcanoProgram(), "settings/volcano.xml");
            break;


        case 3:
            createNewModelAndProgram(midiChannel, "models/cubecubesimple.obj", new CubeCubeProgram(), "settings/cubecube.xml");
            break;
		case 4:
            createNewModelAndProgram(midiChannel, "models/trisimple.obj", new TriProgram(), "settings/tri.xml");
            break;


        case 5:
            createNewModelAndProgram(midiChannel, "models/5cubessimple.obj", new FiveCubesProgram(), "settings/5cubes.xml");
            break;

        case 6:
            createNewModelAndProgram(midiChannel, "models/diamondsimple.obj", new DiamondProgram(), "settings/diamond.xml");
            break;

		case 7:
            createNewModelAndProgram(midiChannel, "models/towerssimple.obj", new TowersProgram(), "settings/towers.xml");
            break;


		case 8:
            createNewModelAndProgram(midiChannel, "models/trifacesimple.obj", new TriFaceProgram(), "settings/triface.xml");
            break;

    }
}
float lightAttConst = 1;
float lightAttLin = 0;
float lightAttQuad = 0;
//--------------------------------------------------------------
void testApp::setup(){

	//fbo.allocate(ofGetWidth(), ofGetHeight());
	//fxaa.load("v002.FXAA.vert", "v002.FXAA.frag");

    ofEnableNormalizedTexCoords();
    debugTex.loadImage("debug.jpg");
    ofSetFrameRate(60);
	ofSetVerticalSync(true);
	scene = new Scene();
	Colours::load();
	editMode = false;

    ofxSettings programsSettings;
    programsSettings.load("settings/programs.xml");

    string programStr = programsSettings.get("programs", "1,2");
    vector<string> sss = ofSplitString(programStr, ",");
    for(int i = 0; i < sss.size(); i++) {
        createNewModelAndProgram(ofToInt(sss[i]));
    }

    osc.setup(12345);

	sceneGui = new SceneGui(scene);
	sceneGui->setEnabled(false);
	ofSetFullscreen(true);

	fbo.allocate(ofGetWidth()*2, ofGetHeight()*2, GL_RGB);



	ofBackground(0, 0, 0);

	scene->getLight()->enable();
	ofEnableAlphaBlending();

	drawMode = 0;

	gui.addSegmented("Draw Mode", drawMode, "PROG|FACE|SHADE|TEX|LINE");
	gui.addSegmented("Position", simulatePos, "OFF|1|2|3|4|5|6|7|8");
	gui.addSlider("attconst", lightAttConst, 0, 1);
	gui.addSlider("attlin", lightAttLin, 0, 1);
	gui.addSlider("attquad", lightAttQuad, 0, 1);
	gui.addToggle("edit mode", editMode);
	gui.addPushButton("next model");

    ofHideCursor();
	gui.setEnabled(false);
	objEditor.setup();
	objEditor.setEnabled(editMode);

	gui.addListener(this);
	plShader.load("pointlight.vert", "pointlight.frag");
	ofBuffer b = ofBufferFromFile("pointlight.vert");
	printf("buffer size: %d\n", b.size());
}

void testApp::stopEditing() {
	editMode = false;
	objEditor.setEnabled(false);
	printf("stop editing\n");
}

void testApp::startEditing() {
	drawMode = LINES;
	for(int i = 0; i < models.size(); i++) {
		if(i==0) {
			printf("starting edit on 0\n");
			models[i]->setEditing(true);
			objEditor.setModel(models[i]);
		} else {
			printf("stop edit on %d\n", i);
			models[i]->setEditing(false);
		}
	}
}

void testApp::controlChanged(xmlgui::Control *ctrl) {
    if(ctrl->name=="Position") {
		map<int,PlanetProgram*>::iterator it;
		for(it = programs.begin(); it!=programs.end(); it++) {
            (*it).second->setPosition(simulatePos);
			printf("position changed\n");
        }
    }
    if(ctrl->name=="edit mode") {
		objEditor.setEnabled(editMode);
		if(editMode) {
			startEditing();
		} else {
			stopEditing();
		}
    }
    if(editMode && ctrl->name=="next model") {
		int lastEditedModel = -1;
		for(int i = 0; i < models.size(); i++) {
			if(models[i]->editing) {
				lastEditedModel = i;
			}
			models[i]->editing = false;
		}
		if(lastEditedModel>-1) {
			lastEditedModel++;
			lastEditedModel %= models.size();
			if(models.size()>0) {
				printf("Next model to edit %d\n", lastEditedModel);
				models[lastEditedModel]->setEditing(true);
				objEditor.setModel(models[lastEditedModel]);
			}
		}

    }
}

void testApp::createNewModelAndProgram(int midiChannel, string objPath, PlanetProgram *program, string settings) {
	models.push_back(new Model(objPath));

	// model is in cm, we want metres
	models.back()->loadSettings(settings);
	scene->addModel(models.back());

    program->setModel(models.back());
	program->init(midiChannel);


	program->light = scene->getLight();
    program->setPosition(0);

	programs[midiChannel] = program;

}

//--------------------------------------------------------------
void testApp::update(){
	scene->getLight()->setPointLight();
	scene->getLight()->setAttenuation(lightAttConst, lightAttLin*0.1, lightAttQuad*0.02);
	gui.x = ofGetWidth() - 200;
	ofxOscMessage m;
	while(osc.hasWaitingMessages()) {
		osc.getNextMessage(&m);

		// dispatch
		// this is the midi channel - use it to index the shape
		int channel = m.getArgAsInt32(0);
		//printf("Channel %d %s \n", channel, m.getAddress().c_str());
        if(m.getAddress()=="/winstate") {

            map<int,PlanetProgram*>::iterator it;
            for(it = programs.begin(); it!=programs.end(); it++) {
                (*it).second->setWinState(m.getArgAsInt32(0), m.getArgAsInt32(1));
            }
           // printf("IN win state %d\n", m.getArgAsInt32(0));
        } else if(m.getAddress()=="/mini") {
            if(programs.find(channel)!=programs.end()) {
                programs[channel]->pingMiniWinState();
            }
		} else if(programs.find(channel)!=programs.end()) {//channel<programs.size()) {
			if(m.getAddress()=="/note/on") {
				programs[channel]->noteOn(m.getArgAsInt32(1));
				//printf("%d\n", m.getArgAsInt32(1));
			//} else if(m.getAddress()=="/note/off") {
			//	programs[channel]->noteOff(m.getArgAsInt32(1), m.getArgAsInt32(2));
			//} else if(m.getAddress()=="/cc") {
			//	programs[channel]->cc(m.getArgAsInt32(1), m.getArgAsInt32(2));
			} else if(m.getAddress()=="/sensor/position") {
                //printf("Position : %d\n", m.getArgAsInt32(1));
				programs[channel]->setPosition(m.getArgAsInt32(1));
			} else if(m.getAddress()=="/app/quit") {
				ofExit();

			} else {


				printf("Got a %s\n", m.getAddress().c_str());
			}
		} else {
		//	printf("%s %d %d\n", m.getAddress().c_str(), m.getArgAsInt32(0), m.getArgAsInt32(1));
		}

	}

	map<int,PlanetProgram*>::iterator it;
	for(it = programs.begin(); it!=programs.end(); it++) {
        (*it).second->updateProgram();
    }

	scene->update();

	ofSetWindowTitle(ofToString(ofGetFrameRate(),2));

}

//--------------------------------------------------------------
void testApp::draw(){

	if(enableFbo) {
		scene->projectors[0]->width = ofGetWidth()*2;
		scene->projectors[0]->height = ofGetHeight()*2;
	} else {
		scene->projectors[0]->width = ofGetWidth();
		scene->projectors[0]->height = ofGetHeight();
	}

	scene->getLight()->enable();
	//scene->getLight()->setSpotlight();

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	//glShadeModel(GL_SMOOTH);

	glEnable(GL_RESCALE_NORMAL);
	if(enableFbo) {
		fbo.begin();
		ofClear(0,0,0,0);
	}
	scene->projectors[0]->begin();

	scene->getLight()->setAmbientColor(ofFloatColor(0, 0, 0));
	scene->getLight()->setDiffuseColor(ofFloatColor(1, 1, 1));
	scene->getLight()->setSpecularColor(ofFloatColor(1, 1, 1));
	scene->getLight()->applyTransformation();

	glEnable(GL_DEPTH_TEST);
	//\printf("%d\n", programs.size());
	map<int,PlanetProgram*>::iterator it;
	for(it = programs.begin(); it!=programs.end(); it++) {
		if(drawMode==FACES) {
			(*it).second->drawDebug();
		} else if(drawMode==PROGRAM) {
			//fbo.begin();
			//ofClear(0,0,0,0);
			(*it).second->draw();
			//fbo.end();
			/*
			ofSetupScreen();
			fbo.getTextureReference(0).bind();
			fxaa.begin();
			fxaa.setUniformTexture("bgl_RenderedTexture", fbo.getTextureReference(0), 0);
			fxaa.setUniform1f("bgl_RenderedTextureWidth", fbo.getWidth());
			fxaa.setUniform1f("bgl_RenderedTextureHeight", fbo.getHeight());

			ofDisableLighting();
			glColor4f(1,1,1,1);
			glBegin(GL_TRIANGLE_STRIP);
			float xx = 1;//ofGetWidth();
			float yy = 1;//ofGetHeight();
			glTexCoord2f(0, 0);
			glVertex2f(0, 0);

			glTexCoord2f(xx, 0);
			glVertex2f(ofGetWidth(), 0);

			glTexCoord2f(0, yy);
			glVertex2f(0, ofGetHeight());

			glTexCoord2f(xx, yy);
			glVertex2f(ofGetWidth(), ofGetHeight());
			glEnd();
			fxaa.end();
			fbo.getTextureReference(0).unbind();
			 */
		} else if(drawMode==SHADED) {
			/*plShader.begin();
			plShader.setUniform1f("constAtt", lightAttConst);
			plShader.setUniform1f("linAtt", lightAttLin);
			plShader.setUniform1f("quadAtt", lightAttQuad);
*/
            (*it).second->drawShaded();
		//	plShader.end();
		} else if(drawMode==TEXTURED) {
		    ofEnableNormalizedTexCoords();
		    debugTex.bind();
            (*it).second->drawShaded();
            debugTex.unbind();
		} else if(drawMode==LINES) {
			glDisable(GL_LIGHTING);
			//glLineWidth(2);
			(*it).second->drawOutline();
			//glLineWidth(1);
		}
	}
	//ofSphere(0, 0, 0, 0.2);
	glDisable(GL_DEPTH_TEST);
	scene->projectors[0]->end();
	if(enableFbo) {
		fbo.end();
	}

	glDisable(GL_LIGHTING);
	if(enableFbo) {
		ofSetHexColor(0xFFFFFF);
		fbo.draw(0, ofGetHeight(), ofGetWidth(), -ofGetHeight());
	}
	sceneGui->draw();
	objEditor.draw();
}

void testApp::clearProgramsAndModels() {

    map<int,PlanetProgram*>::iterator it;
	for(it = programs.begin(); it!=programs.end(); it++) {
        delete (*it).second;
    }
    programs.clear();

    for(int i = 0; i < models.size(); i++) {
        scene->removeModel(models[i]);
        delete models[i];
    }
    models.clear();
}
void testApp::setWinState(int winState,int winMode) {
     map<int,PlanetProgram*>::iterator it;
    for(it = programs.begin(); it!=programs.end(); it++) {
        (*it).second->setWinState(winState, winMode);
    }
    printf("Setting winstate to %d\n", winState);
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(editMode) {
		objEditor.keyPressed(key);
		return;
	}
	if(key>='0' && key <= '8') {
        int num = key - '0';
        setWinState(num, 0);
	}
	switch(key) {

		case 'k':
			enableFbo ^= true;
			break;
        case 'c': {
            map<int,PlanetProgram*>::iterator it;
            for(it = programs.begin(); it!=programs.end(); it++) {
                (*it).second->pingMiniWinState();
            }}
            break;
		case 'f':
			ofToggleFullscreen();
			break;
		case ' ':
			//fourup->toggle();
			sceneGui->toggle();
			gui.toggle();
			if(sceneGui->getEnabled()) {
				ofShowCursor();

			} else {
				ofHideCursor();
				stopEditing();
			}
			break;
        case OF_KEY_RIGHT:
            modelPos++;
            if(modelPos>=8) modelPos = 0;
            clearProgramsAndModels();
            createNewModelAndProgram(modelPos+1);
            break;
        case OF_KEY_LEFT:
            modelPos--;
            if(modelPos<0) modelPos = 7;
            clearProgramsAndModels();
            createNewModelAndProgram(modelPos+1);
            break;
	}

	map<int,PlanetProgram*>::iterator it;
	for(it = programs.begin(); it!=programs.end(); it++) {
		(*it).second->keyPressed(key);
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	scene->projectors[0]->width = w;
	scene->projectors[0]->height = h;

	objEditor.windowResized(w,h);
	fbo.allocate(w*2, h*2);

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
