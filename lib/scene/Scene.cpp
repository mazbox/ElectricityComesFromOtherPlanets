/*
 *  Scene.cpp
 *  emptyExample
 *
 *  Created by Marek Bereza on 06/01/2011.
 *
 */

#include "Scene.h"
#include "ofxSettings.h"

Scene::Scene(int w, int h) {



	bool usingFirstScreenForGuiOnly = settings.getBool("using first screen for gui only", false);
	int numProjectors	= settings.getInt("num projectors", 1);
	int projectorWidth	= settings.getInt("projector width", 1024);
	int projectorHeight = settings.getInt("projector height", 768);

	bool doingProjectorBlend = settings.getBool("using projector blending", false);

	// if we're doing projector blending
	if(doingProjectorBlend) {
		numProjectors = 1;

		projectorWidth = w;
		projectorHeight = h;
		//printf("%d %d\n", projectorWidth, projectorHeight);
	}


	for(int i = 0; i < numProjectors; i++) {
		int offset = 0;
		if(usingFirstScreenForGuiOnly) offset++;

		// add it to our local list
		projectors.push_back(new Projector("proj " + ofToString(i+1), projectorWidth*(i+offset), 0, projectorWidth, projectorHeight));

		// add it to the scene list
		addNode(*projectors.back());
		ofLog(OF_LOG_NOTICE, "projector %d is (%f %f %f %f)\n", i, projectors.back()->x, projectors.back()->y, projectors.back()->width, projectors.back()->height);
		nodes.push_back(projectors.back());
	}



	light = new Light("Light 0");
	light->setSpotlight();
	addNode(*light);
	nodes.push_back(light);

}


void Scene::addModel(Model *model) {
	models.push_back(model);
	addNode(*model);
	nodes.push_back(model);
}

void Scene::removeModel(Model *model) {
//	printf("Incoming %x\n", model);
    for(int i = 0; i < models.size(); i++) {
        if(model==models[i]) {
            models.erase(models.begin()+i);
            for(int j = 0; j < nodes.size(); j++) {
//				printf("Comparison %x\n", nodes[j]);
                if(model==nodes[j]) {
					
                    removeNode(*model);
                    nodes.erase(nodes.begin()+j);
                    return;
                }
            }
            break;
        }
    }
	printf("Couldn't remove models!!\n");
}

Scene::~Scene() {

}

void Scene::update() {

	for(int i = 0; i < nodes.size(); i++) {
		nodes[i]->applyTransformation();
	}
}

Light *Scene::getLight() {
	return light;
}

