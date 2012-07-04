#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxOsc.h"
#include "ofxSettings.h"
#include "ofxKinect.h"
#define USE_KINECT
#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file
#define NUM_CAMERAS		2

#include "EditableRect.h"

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);		

	#ifdef _USE_LIVE_VIDEO
	#	ifdef USE_KINECT
	ofxKinect kinects[NUM_CAMERAS];
	#	else
	  ofVideoGrabber		cams[NUM_CAMERAS];
	#	endif
	#else
	  ofVideoPlayer 		vids[NUM_CAMERAS];
	#endif
		
	ofxCvColorImage			colorToGreyscale;
	ofxCvGrayscaleImage		greyscale;
	ofxCvGrayscaleImage 	greyImgs[NUM_CAMERAS];
	ofxCvGrayscaleImage 	threshImgs[NUM_CAMERAS];
	int threshold;
	int numBlurs;
	bool drawThresh;
	
	int findPosition(ofxCvContourFinder &contours, float height);
	ofxCvContourFinder		contours[NUM_CAMERAS*2];
	
	EditableRect rects[NUM_CAMERAS*2];

	bool flipX[NUM_CAMERAS];
	bool flipY[NUM_CAMERAS];
	float maxY[NUM_CAMERAS];
	bool acquireFrame(int i);
	void getGreyscaleFrame(int i);
	
	float positions[NUM_CAMERAS*2];
	
	void sendOsc();
	
	ofxOscSender osc;
	
	int appId;
	
	ofxSettings settings;
	
	float lastTimeSentOsc;
	
	void setupOsc();
};

