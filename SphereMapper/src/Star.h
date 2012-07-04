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
 *  Description:
 *
 *  Star.h, created by Marek Bereza on 06/06/2012.
 */



class Star {
public:

	ofVec3f pos;

	float radius;
	float angle;
	float angVel;
	float radVel;

	float size;
	float maxRadius;
	
	bool dead;
	Star() {
		maxRadius = 1.4;
		dead = false;
		setup();

	}

	void update(const float &delta) {
		if(dead) return;
		angle += angVel*delta;
		radius += radVel*delta;
		
		if(radius>maxRadius) {
		//	setup();
			dead = true;
		}
		
		pos.x = radius*cos(angle);
		pos.y = radius*sin(angle);

	}

	void setup() {
		radius = 0.3;
		size = ofRandom(0.3, 1);
		angle = ofRandom(0, PI*2);
		angVel = ofRandom(0.4, 0.7);
		radVel = ofRandom(0.15, 0.8);
		dead = false;
	}
	
	void setupFast() {
		radius = 0.3;
		size = ofRandom(0.3, 1);
		angle = ofRandom(0, PI*2);
		angVel = ofRandom(1, 2.2);
		radVel = ofRandom(0.4, 0.8);
		dead = false;
	}
};
