/**     ___           ___           ___                         ___           ___
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/
 *
 *  Description: This was in oF, by Memo, just rewrote it in a single file for it to
 *				 work with ofxFourUpDisplay.
 *
 *  ofScene3d.h, created by Marek Bereza on 26/04/2012.
 */
#pragma once

#include "ofNode.h"

class ofScene3d {
public:

	void addNode(ofNode& n) {
		_nodes.push_back(&n);
	}

	void removeNode(ofNode &n) {
        for(int i =0; i < _nodes.size(); i++) {
            if(_nodes[i]==&n) {
                _nodes.erase(_nodes.begin()+i);
                return;
            }
        }
        printf("Warning! Couldn't delete node!\n");
	}

	ofNode& getNode(int i) {
		return *_nodes.at(i);
	}

	int getNumNodes() const {
		return _nodes.size();
	}
	vector<ofNode*>& getNodes() {
		return _nodes;
	}

	void draw() {
		for(int i=0; i<(int)_nodes.size(); i++) {
			_nodes[i]->draw();
		}
	}

protected:
	vector<ofNode*>_nodes;
};


