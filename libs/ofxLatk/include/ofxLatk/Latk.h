#pragma once

#include "ofMain.h"
#include "LatkJson.h"
#include "LatkLayer.h"

class Latk {

	public:
		Latk();
		Latk(string fileName);
		virtual ~Latk() {};

		void run();
		bool checkInterval();
		void read(string fileName, bool clearExisting);
		void write(string fileName);

		LatkJson json;
		LatkJson jsonGp;
		LatkJson jsonLayer;
		LatkJson jsonFrame;
		LatkJson jsonStroke;
		LatkJson jsonPoint;

		vector<LatkLayer> layers;
		string fileName = "layer_test";
		float globalScale = 100.0;
		bool drawMesh = false;
		int startTime = 0;
		int lastMillis = 0;
		int timeInterval = 0;
		float fps = 12.0;
		int fpsInterval = int((1.0 / fps) * 1000.0);

		int currentLayer = 0;

};