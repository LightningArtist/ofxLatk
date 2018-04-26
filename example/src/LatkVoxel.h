#pragma once

#include "ofMain.h"

class LatkVoxel {

	public:
		LatkVoxel();
		LatkVoxel(ofVec3f _p, float _s, ofColor _c);
		virtual ~LatkVoxel() {};
		
		void update();
		void draw();
		void run();

		ofVec3f p;
		float s;
		ofColor c;
		bool drawMe = false;
		bool selectMe = false;
		bool sameZ = false;

};

