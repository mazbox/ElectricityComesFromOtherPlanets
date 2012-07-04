/*
 *  SceneGui.h
 *  emptyExample
 *
 *  Created by Marek Bereza on 06/01/2011.
 *
 */
#include "SimpleGui.h"
#include "Scene.h"
#include "Enableable.h"
#include "ofxFourUpDisplay.h"
#include "FineControls.h"

/**
 * \brief The gui for arranging cameras
 */
class SceneGui: public Enableable, public xmlgui::Listener {
public:


	SceneGui(Scene *scene);
	FineControls posX, posY, posZ;
	FineControls rotX, rotY, rotZ;

	void controlChanged(xmlgui::Control *control);
	void setEnabled(bool enabled);
	void draw();
	void save();

private:
	xmlgui::SimpleGui gui;
	Scene *scene;
	ANode dummy;
	int objectIndex;
	void setSelectedObjectIndex(int index);
};
