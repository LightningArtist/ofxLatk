#include "Latk.h"

Latk::Latk() {
	//
}

Latk::Latk(string fileName) {
	read(fileName, true);

	startTime = ofGetElapsedTimeMillis();
	cout << "Latk strokes loaded.";
}

void Latk::run() {
	bool advanceFrame = checkInterval();

	for (int i = 0; i<layers.size(); i++) {
		if (advanceFrame) layers[i].nextFrame();
		layers[i].run();
	}

	lastMillis = ofGetElapsedTimeMillis();
}

bool Latk::checkInterval() {
	bool returns = false;
	timeInterval += ofGetElapsedTimeMillis() - lastMillis;
	if (timeInterval > fpsInterval) {
		returns = true;
		timeInterval = 0;
	}
	return returns;
}

void Latk::read(string fileName, bool clearExisting) {
	if (clearExisting) layers.clear();

	json.open(fileName);

	cout << json["grease_pencil"].size();
	/*
	for (int h = 0; h<json.getJSONArray("grease_pencil").size(); h++) {
		jsonGp = (JSONObject)json.getJSONArray("grease_pencil").get(h);

		for (int i = 0; i<jsonGp.getJSONArray("layers").size(); i++) {
			layers.push_back(LatkLayer());

			jsonLayer = (JSONObject)jsonGp.getJSONArray("layers").get(i);
			for (int j = 0; j<jsonLayer.getJSONArray("frames").size(); j++) {
				layers[layers.size() - 1].frames.push_back(LatkFrame());

				jsonFrame = (JSONObject)jsonLayer.getJSONArray("frames").get(j);
				for (int l = 0; l<jsonFrame.getJSONArray("strokes").size(); l++) {
					jsonStroke = (JSONObject)jsonFrame.getJSONArray("strokes").get(l);

					int r = int(255.0 * jsonStroke.getJSONArray("color").getFloat(0));
					int g = int(255.0 * jsonStroke.getJSONArray("color").getFloat(1));
					int b = int(255.0 * jsonStroke.getJSONArray("color").getFloat(2));
					ofColor col = ofColor(r, g, b);

					vector<ofVec3f> pts;
					for (int m = 0; m<jsonStroke.getJSONArray("points").size(); m++) {
						jsonPoint = (JSONObject)jsonStroke.getJSONArray("points").get(m);
						ofVec3f p = ofVec3f(jsonPoint.getJSONArray("co").getFloat(0), jsonPoint.getJSONArray("co").getFloat(1), jsonPoint.getJSONArray("co").getFloat(2));
						pts.push_back(p * globalScale);
					}

					LatkStroke st = LatkStroke(pts, col);
					layers[layers.size() - 1].frames[layers[layers.size() - 1].frames.size() - 1].strokes.push_back(st);
				}
			}
		}
	}
	*/
}

void Latk::write(string fileName) {
	// TODO
}