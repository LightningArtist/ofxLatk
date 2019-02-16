#pragma once

#include "ofMain.h"
#include "LatkStroke.h"

class LatkFrame {

public:
	LatkFrame();
	virtual ~LatkFrame() {};

	void run();

	vector<LatkStroke> strokes;

};