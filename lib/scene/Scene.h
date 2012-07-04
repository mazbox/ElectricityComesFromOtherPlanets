#pragma once

#include "Projector.h"
#include "Model.h"
#include "ofScene3d.h"
#include "Light.h"

/**
 * \brief Represents the real world setup of physical surfaces,
 * and the projectors in the scene
 */
class Scene: public ofScene3d {
public:

	/**
	 * Loads the scene from XML. If using
	 * projector edge blending, pass in
	 * the total projection area here,
	 * otherwise it's ignored.
	 */
	Scene(int w = 0, int h = 0);

	~Scene();

	vector<Model*> models;
	void update();

	void addModel(Model *model);
	void removeModel(Model *model);

	vector<Projector*> projectors;
	Light *getLight();


	// this is for the gui
	vector<Node*> nodes;

private:
	Light *light;

};
