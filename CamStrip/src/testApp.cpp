#include "testApp.h"

#define VISION_WIDTH 320
#define VISION_HEIGHT 240
#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

#include "ofxSimpleGuiToo.h"

#define BOTH			0
#define CAMERA_0		1
#define CAMERA_1		2
#define NUM_DRAW_MODES	3

int DRAW_MODE = BOTH;

#include "ofxMSAThreadedImageSaver.h"

ofxMSAThreadedImageSaver *imageSaver;
bool record = false;


ofTrueTypeFont font;
float minP = 0;
float maxP = 0;
int stripMap[4];
float minBlobSize;
//--------------------------------------------------------------
void testApp::setup(){
	minBlobSize = 7;
	font.loadFont("Impact.ttf", 60);
	numBlurs = 0;
	
	settings.load("general.xml");

	stripMap[0] = settings.getInt("strip0", 0);
	stripMap[1] = settings.getInt("strip1", 1);
	stripMap[2] = settings.getInt("strip2", 2);
	stripMap[3] = settings.getInt("strip3", 3);
	
	setupOsc();

	drawThresh = false;

	gui.addToggle("record", record);
	gui.addSlider("Min", minP, 0, 8000);
	gui.addSlider("Max", maxP, 0, 8000);
	gui.addSlider("Blur", numBlurs, 0, 5);
	gui.addToggle("Draw Threshold", drawThresh);
	threshold = 0;
	gui.addSlider("Threshold", threshold, 0, 255);
	gui.addSlider("Min Blob Size", minBlobSize, 1, 15);

	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	
	
	for(int i = 0; i < NUM_CAMERAS; i++) {
	#ifdef _USE_LIVE_VIDEO
		#	ifdef USE_KINECT
		kinects[i].init();
		kinects[i].open(i);
		#	else
		cams[i].setVerbose(true);
		cams[i].initGrabber(CAMERA_WIDTH,CAMERA_HEIGHT);
		#	endif
	#else
		if(i==0) {
			vids[i].loadMovie("depth.mov");
			vids[i].play();
		}
	#endif
		maxY[i] = 0;
		
		positions[i*2] = 0;
		positions[i*2+1] = 0;
		
		greyImgs[i].allocate(VISION_WIDTH,VISION_HEIGHT);
		threshImgs[i].allocate(VISION_WIDTH,VISION_HEIGHT);
		flipX[i] = false;
		flipY[i] = false;

		gui.addContent("Cam "+ofToString(i), greyImgs[i]);
		gui.addContent("Thresh "+ofToString(i), threshImgs[i]);
		gui.addToggle("Cam " + ofToString(i) + "flip X", flipX[i]);
		gui.addToggle("Cam " + ofToString(i) + "flip Y", flipY[i]);
		gui.addSlider("maxY " + ofToString(i), maxY[i], 0, 240);
		
	}
	lastTimeSentOsc = -1;
	

	for(int i = 0; i < 4; i++) {
		rects[i].setup(ofToString(i));
	}



	
	gui.setAutoSave(true);
	gui.loadFromXML();
	gui.setAlignRight(true);

	colorToGreyscale.allocate(CAMERA_WIDTH, CAMERA_HEIGHT);
	greyscale.allocate(CAMERA_WIDTH, CAMERA_HEIGHT);



	imageSaver = new ofxMSAThreadedImageSaver();
	imageSaver->allocate(CAMERA_WIDTH, CAMERA_HEIGHT, OF_IMAGE_GRAYSCALE);
	imageSaver->setUseTexture(false);

}



bool testApp::acquireFrame(int i) {
	bool bNewFrame = false;
#ifdef _USE_LIVE_VIDEO
#	ifdef	USE_KINECT
	kinects[i].update();
	bNewFrame = kinects[i].isFrameNew();
#	else
	cams[i].grabFrame();
	bNewFrame = cams[i].isFrameNew();
#endif
#else
	vids[i].idleMovie();
	bNewFrame = vids[i].isFrameNew();
#endif
	return bNewFrame;
}

void testApp::getGreyscaleFrame(int i) {
#ifdef _USE_LIVE_VIDEO
#	ifdef USE_KINECT
	greyscale.setFromPixels(kinects[i].getDepthPixels(), CAMERA_WIDTH, CAMERA_HEIGHT);				
#	else
	colorToGreyscale.setFromPixels(cams[i].getPixels(), CAMERA_WIDTH, CAMERA_HEIGHT);
	greyscale = colorToGreyscale;
#	endif
#else
	colorToGreyscale.setFromPixels(vids[i].getPixels(), CAMERA_WIDTH, CAMERA_HEIGHT);
	greyscale = colorToGreyscale;			
#endif
}


//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(0,0,0);
	
	for(int i = 0; i < NUM_CAMERAS; i++) {
		#ifdef _USE_LIVE_VIDEO
		#	ifdef USE_KINECT
		if(kinects[i].getNearClipping()!=minP || kinects[i].getFarClipping()!=maxP) {
			kinects[i].setDepthClipping(minP, maxP);
		}
		#	endif
		#endif
		bool bNewFrame = acquireFrame(i);

		
		
		if (bNewFrame){

			getGreyscaleFrame(i);
			
			if(record && i==0) {
				imageSaver->setFromPixels(greyscale.getPixels(), CAMERA_WIDTH, CAMERA_HEIGHT, OF_IMAGE_GRAYSCALE);
				imageSaver->saveThreaded(ofGetTimestampString() + ".jpg");
			}
			
			
			greyImgs[i].scaleIntoMe(greyscale);
			greyImgs[i].mirror(flipY[i], flipX[i]);
			
			for(int k = 0; k < numBlurs; k++) {
				greyImgs[i].blur(3);
			}
			threshImgs[i] = greyImgs[i];
			
			threshImgs[i].threshold(threshold);
			
		/*	cvRectangle( threshImgs[i].getCvImage(), cvPoint(100,100), cvPoint(200, 200),
						cvScalar(255) , CV_FILLED);
			*/
			cvRectangle( threshImgs[i].getCvImage(), cvPoint(0,0), cvPoint(320, maxY[i]),
					   cvScalar(0) , CV_FILLED);
			
// 			threshImgs.
			int minArea = minBlobSize*minBlobSize;
			int maxArea = 500*500;
			int nConsidered = 5;
			bool bFindHoles = false;
			
			for(int k = 0; k < 2; k++) {
				// do the contours for both strips
				threshImgs[i].setROI(rects[i*2+k]);
				contours[i*2+k].findContours(threshImgs[i], minArea, maxArea, nConsidered, bFindHoles);
				positions[i*2+k] = findPosition(contours[i*2+k], rects[i*2+k].height);
			}
		
			threshImgs[i].resetROI();
			
			
		}
	}
	sendOsc();
}

int testApp::findPosition(ofxCvContourFinder &contours, float height) {

	//printf("h: %f\n", height);
	float lowestY = 0;
	bool found = false;
	// find the lowest contour, then map its value?
	for(int i = 0; i < contours.blobs.size(); i++) {
		if(contours.blobs[i].centroid.y>lowestY) {
			lowestY = contours.blobs[i].centroid.y;
			found = true;
		}
	}

	if(!found) return 0;
	return ofMap(lowestY, 0, height, 1, 9); // is this even?
}
void testApp::sendOsc() {
	if(ofGetElapsedTimef()-lastTimeSentOsc>0.2) {
		lastTimeSentOsc = ofGetElapsedTimef();
		
		ofxOscMessage m;
		m.setAddress("/sensor/"+ofToString(appId));
		for(int i = 0; i < NUM_CAMERAS*2; i++) {
			m.addIntArg(positions[stripMap[i]]);
		}
		osc.sendMessage(m);
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){

	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);



	ofxCvGrayscaleImage *imgs;
	if(drawThresh) {
		imgs = threshImgs;
	} else {
		imgs = greyImgs;
	}
	
	if(DRAW_MODE==BOTH) {
		imgs[0].draw(0, 0, VISION_WIDTH, VISION_HEIGHT);

		contours[0].draw(rects[0].x, rects[0].y);
		contours[1].draw(rects[1].x, rects[1].y);		
				
		glPushMatrix();
		glTranslatef(VISION_WIDTH, 0, 0);
		imgs[1].draw(0, 0, VISION_WIDTH, VISION_HEIGHT);
		contours[2].draw(rects[2].x, rects[2].y);
		contours[3].draw(rects[3].x, rects[3].y);
		glPopMatrix();
		for(int i = 0; i < 4; i++) {
			if(i>=2) {
				rects[i].setTransform(VISION_WIDTH, 0, 1);
			}
			rects[i].draw();
		}
		
	} else if(DRAW_MODE==CAMERA_0) {

		imgs[0].draw(0, 0, ofGetWidth(), ofGetHeight());
		
		float scaleX = (float)ofGetWidth()/(float)greyImgs[0].getWidth();
		float scaleY = (float)ofGetHeight()/(float)greyImgs[0].getHeight();
		
		glPushMatrix();
		{
			glScalef(scaleX, scaleY, 1);
			contours[0].draw(rects[0].x, rects[0].y);
			contours[1].draw(rects[1].x, rects[1].y);
		}
		glPopMatrix();
		
		// rects take care of their own transformations
		rects[0].setTransform(0, 0, scaleX, scaleY);
		rects[1].setTransform(0, 0, scaleX, scaleY);
		rects[0].draw();
		rects[1].draw();
		
	} else if(DRAW_MODE==CAMERA_1) {
		
		imgs[1].draw(0, 0, ofGetWidth(), ofGetHeight());
		float scaleX = (float)ofGetWidth()/(float)greyImgs[1].getWidth();
		float scaleY = (float)ofGetHeight()/(float)greyImgs[1].getHeight();
		
		glPushMatrix();
		{
			glScalef(scaleX, scaleY, 1);
			contours[2].draw(rects[2].x, rects[2].y);





			contours[3].draw(rects[3].x, rects[3].y);

		}
		glPopMatrix();
		
		// rects take care of their own transformations

		rects[2].setTransform(0, 0, scaleX, scaleY);
		rects[3].setTransform(0, 0, scaleX, scaleY);
		rects[2].draw();
		rects[3].draw();
	}
	
	
	gui.draw();
	ofSetHexColor(0x0000FF);
	string report = "";
	for(int i = 0; i < NUM_CAMERAS*2; i++) {
		report += ofToString((int)positions[i]) + " " ;
	}
	font.drawString(report, 20, ofGetHeight()-20);
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	switch (key){
		case ' ':
			gui.toggleDraw();
			break;
#ifndef _USE_LIVE_VIDEO
		case 'p':
			vids[0].setPaused(!vids[0].isPaused());
			break;
#endif

		case OF_KEY_DOWN:
		case OF_KEY_UP:
			drawThresh ^= true;
			break;
			
		case OF_KEY_LEFT:
			DRAW_MODE--;
			if(DRAW_MODE<0) DRAW_MODE = NUM_DRAW_MODES - 1;
			break;

		case OF_KEY_RIGHT:
			DRAW_MODE++;
			if(DRAW_MODE>=NUM_DRAW_MODES) DRAW_MODE = 0;
			break;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	for(int i = 0; i < 4; i++) {
		rects[i].mouseMoved(x, y);
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	for(int i = 0; i < 4; i++) {
		if(rects[i].mouseDragged(x, y)) {
			break;
		}
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	for(int i = 0; i < 4; i++) {
		if(rects[i].mousePressed(x, y)) {
			break;
		}
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	for(int i = 0; i < 4; i++) {
		rects[i].mouseReleased(x, y);
	}
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}




void testApp::setupOsc() {
	appId = settings.getInt("appId", 1);
	int oscPort = settings.getInt("oscPort", 24680);
	string oscHost = settings.get("oscHost", "localhost");
	osc.setup(oscHost, oscPort);
}

