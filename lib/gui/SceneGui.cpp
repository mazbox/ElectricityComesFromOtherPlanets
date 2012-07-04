/*
 *  SceneGui.cpp
 *  emptyExample
 *
 *  Created by Marek Bereza on 06/01/2011.
 *
 */

#include "SceneGui.h"
#include "ofxSettings.h"
#include "constants.h"



SceneGui::SceneGui(Scene *scene): Enableable() {

	objectIndex = -1;
	vector<string> items;
	for(int i = 0; i < scene->nodes.size(); i++) {

		items.push_back(scene->nodes[i]->getName());
	}



	List *list = (List*)gui.addList("object", objectIndex, items);
	list->height = 200;

	this->scene = scene;

	gui.setup();

	gui.addSlider("fov", dummy.fov.fovY, 0, 180);
	gui.addPanner("x position", dummy.pos.x, -10, 10);
	posX.addToGui(&gui, dummy.pos.x);

	gui.addPanner("y position", dummy.pos.y, -2, 2);
	posY.addToGui(&gui, dummy.pos.y);

	gui.addPanner("z position", dummy.pos.z, -5, 25);
	posZ.addToGui(&gui, dummy.pos.z);

	gui.addPanner("x rotation", dummy.rot.x, -180, 180);
	rotX.addToGui(&gui, dummy.rot.x, true);

	gui.addPanner("y rotation", dummy.rot.y, -180, 180);
	rotY.addToGui(&gui, dummy.rot.y, true);

	gui.addPanner("z rotation", dummy.rot.z, -180, 180);
	rotZ.addToGui(&gui, dummy.rot.z, true);

	gui.addPushButton("Reset z-rot");
	gui.addPushButton("Reset rot");


	setSelectedObjectIndex(0);



	//gui.enableAutoSave("settings/cameras.xml");
	gui.setEnabled(false);


	if(enabled) {
		gui.setEnabled(true);
	} else {
		gui.setEnabled(false);
	}


	gui.addListener(this);
}

void SceneGui::setSelectedObjectIndex(int index) {
	objectIndex = index;
	gui.pointToValue("fov", &scene->nodes[index]->fov.fovY);

	gui.pointToValue("x position", &scene->nodes[index]->pos.x);
	posX.pointToValue(&scene->nodes[index]->pos.x);

	gui.pointToValue("y position", &scene->nodes[index]->pos.y);
	posY.pointToValue(&scene->nodes[index]->pos.y);

	gui.pointToValue("z position", &scene->nodes[index]->pos.z);
	posZ.pointToValue(&scene->nodes[index]->pos.z);

	gui.pointToValue("x rotation", &scene->nodes[index]->rot.x);
	rotX.pointToValue(&scene->nodes[index]->rot.x);

	gui.pointToValue("y rotation", &scene->nodes[index]->rot.y);
	rotY.pointToValue(&scene->nodes[index]->rot.y);

	gui.pointToValue("z rotation", &scene->nodes[index]->rot.z);
	rotZ.pointToValue(&scene->nodes[index]->rot.z);

}

void SceneGui::save() {
	//gui.saveValues("settings/cameras.xml");
}

void SceneGui::controlChanged(xmlgui::Control *control) {
	if(posX.update(control)) {
	} else if(posY.update(control)) {
	} else if(posZ.update(control)) {
	} else if(rotX.update(control)) {
	} else if(rotY.update(control)) {
	} else if(rotZ.update(control)) {


	} else if(control->id=="Reset z-rot") {
		scene->nodes[objectIndex]->rot.z = 0;
	} else if(control->id=="Reset rot") {
		scene->nodes[objectIndex]->rot = ofVec3f(0,0,0);
	} else if(control->id=="object") {
		setSelectedObjectIndex(objectIndex);
	}
	if(control->id!="object") {
		scene->nodes[objectIndex]->saveSettings();
	}
}
void SceneGui::draw() { if(getEnabled()) { gui.draw();}  }

void SceneGui::setEnabled(bool enabled) {
	this->enabled = enabled;

	gui.setEnabled(enabled);
	//printf("setting scenegui enabled to %d\n", enabled);


	/*if(enabled && gui.getControlById("Show 4-up")->boolValue()) {
		viewports->setEnabled(true);
	} else {
		viewports->setEnabled(false);
	}*/
}
