#pragma once

#include "ofMain.h"

class Voxel {

	public:
		ofVec3f p;
		float s;
		ofColor c;
		bool drawMe = false;
		bool selectMe = false;
		bool sameZ = false;

		Voxel(ofVec3f _p, float _s, ofColor _c);
		void update();
		void draw();
		void run();

};

