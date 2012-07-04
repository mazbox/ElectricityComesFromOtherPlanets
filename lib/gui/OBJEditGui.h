
#pragma once
#include "SimpleGui.h"
#include "Model.h"
#include "FineControls.h"
#include "EditPoints.h"
#ifdef _WIN32
#include "glut.h"
#else
#include "../../../libs/glut/lib/osx/GLUT.framework/Versions/A/Headers/glut.h"
#endif

class OBJEditGui: public Enableable, public xmlgui::Listener {
public:
	xmlgui::SimpleGui gui;
	FineControls x, y, z;
	ofVec3f pos;
	Model *model;

	EditPoints editPoints;

	int selectedPoint;

	void setup() {
		model = NULL;
		gui.addPushButton("prev");
		gui.addPushButton("next");
		x.addToGui(&gui, pos.x);
		y.addToGui(&gui, pos.y);
		z.addToGui(&gui, pos.z);
	selectedPoint = -1;
		gui.addListener(this);
		windowResized(ofGetWidth(), ofGetHeight());
	}


	void setEditPoint(int index) {
		if(index>=0 && index<editPoints.size()) {
			model->editPoint = editPoints.getPoint(index);
			selectedPoint = index;
		}

	}
	void controlChanged(xmlgui::Control *ctrl) {
		if(ctrl->name=="next") {
			int index = (selectedPoint+1) % editPoints.size();
			setEditPoint(index);

		} else if(ctrl->name=="prev") {
			int index = selectedPoint-1;
			if(index<0) index = editPoints.size()-1;
			setEditPoint(index);
		} else if(x.update(ctrl) || y.update(ctrl) || z.update(ctrl)) {
			editPoints.delta(selectedPoint, pos);
			model->save();
			setEditPoint(selectedPoint);
			pos.set(0,0,0);
		}
	}

	void setModel(Model *model) {
		this->model = model;

		// find all points, duplicated coords
		editPoints.setFromModel(model);
		setEditPoint(0);
	}
	void draw() { if(getEnabled()) { gui.draw();}  }


	void setEnabled(bool enabled) {
		this->enabled = enabled;
		gui.setEnabled(enabled);
	}

	void keyPressed(int key) {

		float delta = 0.001f;
		if(glutGetModifiers() & GLUT_ACTIVE_SHIFT) delta *= 10.f;
		switch(key) {
			case OF_KEY_UP:
				editPoints.delta(selectedPoint, ofVec3f(0,delta,0));
				setEditPoint(selectedPoint);
				model->save();
				break;
			case OF_KEY_DOWN:
				editPoints.delta(selectedPoint, ofVec3f(0,-delta,0));
				setEditPoint(selectedPoint);
				model->save();
				break;
			case OF_KEY_LEFT:
				editPoints.delta(selectedPoint, ofVec3f(-delta, 0 ,0));
				setEditPoint(selectedPoint);
				model->save();
				break;
			case OF_KEY_RIGHT:
				editPoints.delta(selectedPoint, ofVec3f(delta,0,0));
				setEditPoint(selectedPoint);
				model->save();
				break;
		}
	}
	void windowResized(float x, float y) {
		gui.x = x - 200;
		gui.y = y - 300;
	}
};
