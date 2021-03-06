/**
 * Mask.h
 * emptyExample
 *
 * Created by Marek Bereza on 12/03/2011.
 *
 */
#include "ofMain.h"
#include "ofxXmlSettings.h"

class QuadMask: public ofRectangle {

public:
	QuadMask() ;
	
	void setup(string file = "") ;

	void save(string file = "") ;

	
	
	void draw(ofEventArgs &args);
	
	void toggleEditing();
	void setEnableEditing(bool editingEnabled);
	bool isEditing();
	
	void toggleEnabled();
	void setEnabled(bool enabled);
	bool isEnabled();
	
	void mousePressed(ofMouseEventArgs &m);
	void mouseDragged(ofMouseEventArgs &m);
	void mouseReleased(ofMouseEventArgs &m) ;
	
	
	void keyPressed(ofKeyEventArgs &k);
	void keyReleased(ofKeyEventArgs &k);
	
	void setTransform(float x, float y, float width, float height);
	
private:
	
	int sqrDist(int x1, int y1, int x2, int y2);
	float distToCentre(ofVec3f a, ofVec3f b, ofVec3f p);
	
	// the 3rd point is the mask thickness at a specific point
	vector<ofVec2f> points;
	
	
	// the point that the mouse is
	// currently pressing down on.
	int selectedPoint;
	
	// the last point in this Plane
	// that the mouse pressed down on.
	int lastSelectedPoint;
	
	// if one of the points in this plane is 
	// focused for arrow key control, this
	// will be the index of the point. -1 otherwise.
	int focusedPoint;
	
	bool selected;
	
	string filePath;
	bool editing;
	bool enabled;
	
	ofRectangle transform;

};
