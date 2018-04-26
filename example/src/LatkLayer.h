#pragma once

#include "ofMain.h"
#include "LatkFrame.h"

class LatkLayer {

public:
	LatkLayer();
	virtual ~LatkLayer() {};

	void run();
	void nextFrame();

	vector<LatkFrame> frames;
	int currentFrame = 0;
	string name = "ofLayer";

};