
#include "Model.h"
class EditPoints {
public:

	// this is a map of all unique points
	vector<vector<ofVec3f*> > points;
	void setFromModel(Model *model) {
		clear();
		int originalNumPoints = 0;
		ofxOBJModel *m = &model->model;
		for(int i = 0; i < m->groups.size(); i++) {
			for(int j = 0; j < m->groups[i].faces.size(); j++) {
				for(int k = 0; k < m->groups[i].faces[j].vertices.size(); k++) {
					addPoint(m->groups[i].faces[j].vertices[k]);
					originalNumPoints++;
				}
			}
		}
		printf("EditPoints turned %d points into %d\n", originalNumPoints, size());
	}

	void addPoint(ofVec3f &p) {
		bool pointAdded = false;
		for(int i = 0; i < points.size(); i++) {
			if(p==*points[i][0]) {
				points[i].push_back(&p);
				pointAdded = true;
			}
		}
		if(!pointAdded) {
			points.push_back(vector<ofVec3f*>());
			points.back().push_back(&p);
		}
	}

	void clear() {
		points.clear();
	}

	ofVec3f getPoint(int index) {
		if(index<points.size() &&index>=0) {
			return *points[index][0];
		}
		return ofVec3f();
	}

	void delta(int index, ofVec3f inc) {
		for(int i = 0; i < points[index].size(); i++) {
			*points[index][i] += inc;
		}
	}


	int size() {
		return points.size();
	}
};
