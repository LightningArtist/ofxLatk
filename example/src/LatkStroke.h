#pragma once
#include "ofMain.h"

class LatkStroke {
    
    public:
		LatkStroke();
		LatkStroke(ofColor c);
		LatkStroke(float s);
		LatkStroke(ofColor c, float s);
		LatkStroke(vector<ofVec3f> pts, ofColor c);
		virtual ~LatkStroke(){};

        void update();
        void draw();
        void run();
        void splitStroke();
        void smoothStroke();
        void refine();
    
        vector<ofVec3f> points;
        float strokeSize = 4.0;
        ofColor strokeColor = ofColor(0);
        int splitReps = 2;
        int smoothReps = 10;
        bool drawMesh = false;
		float globalScale = 1.0;

};
