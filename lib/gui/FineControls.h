#pragma once
#include "SimpleGui.h"

struct FineControls {
	PushButton *m01;
	PushButton *m001;
	PushButton *p01;
	PushButton *p001;
	float *value;
	bool isAngle;
	void addToGui(xmlgui::SimpleGui *g, float &value, bool isAngle = false) {
		float w = 30;
		this->isAngle = isAngle;
		m001 = g->addPushButton("-0.01");
		float initialX = m001->x;
		m001->x = m001->x+w+10;
		m001->width = w;
		m001->y -= 10;
		p001 = g->addPushButton("+0.01");
		p001->y = m001->y;
		p001->width = w;
		p001->x = m001->x+w+10;
		p01 = g->addPushButton("+0.1");
		p01->y = m001->y;
		p01->width = w;
		p01->x = p001->x+w+10;

		m01 = g->addPushButton("-0.1");
		m01->width = w;
		m01->x = initialX;
		m01->y = p001->y;
		this->value = &value;
	}

	void pointToValue(float *f) {
		this->value = f;
	}

	bool update(xmlgui::Control *c) {
		if(isAngle) {
			if(c==m01) {
				*value -= 1;
				return true;
			} else if(c==m001) {
				*value -= 0.1;
				return true;
			} else if(c==p01) {
				*value += 1;
				return true;
			} else if(c==p001) {
				*value += 0.1;
				return true;
			}
			return false;
		} else {
			if(c==m01) {
				*value -= 0.01;
				return true;
			} else if(c==m001) {
				*value -= 0.001;
				return true;
			} else if(c==p01) {
				*value += 0.01;
				return true;
			} else if(c==p001) {
				*value += 0.001;
				return true;
			}
			return false;
		}
	}
};
