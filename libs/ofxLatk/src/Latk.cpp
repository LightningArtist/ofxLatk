#include "Latk.h"

Latk::Latk() { }

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

	for (int h = 0; h<json["grease_pencil"].size(); h++) {
		jsonGp = json["grease_pencil"][h];

		for (int i = 0; i<jsonGp["layers"].size(); i++) {
			layers.push_back(LatkLayer());

			jsonLayer = jsonGp["layers"][i];
			for (int j = 0; j<jsonLayer["frames"].size(); j++) {
				layers[layers.size() - 1].frames.push_back(LatkFrame());

				jsonFrame = jsonLayer["frames"][j];
				for (int l = 0; l<jsonFrame["strokes"].size(); l++) {
					jsonStroke = jsonFrame["strokes"][l];

					int r = int(255.0 * jsonStroke["color"][0].asFloat());
					int g = int(255.0 * jsonStroke["color"][1].asFloat());
					int b = int(255.0 * jsonStroke["color"][2].asFloat());
					ofColor col = ofColor(r, g, b);

					vector<ofVec3f> pts;
					for (int m = 0; m<jsonStroke["points"].size(); m++) {
						jsonPoint = jsonStroke["points"][m];
						ofVec3f p = ofVec3f(jsonPoint["co"][0].asFloat(), jsonPoint["co"][1].asFloat(), jsonPoint["co"][2].asFloat());
						pts.push_back(p * globalScale);
					}

					LatkStroke st = LatkStroke(pts, col);
					st.globalScale = globalScale;
					st.drawMesh = drawMesh;
					layers[layers.size() - 1].frames[layers[layers.size() - 1].frames.size() - 1].strokes.push_back(st);
				}
			}
		}
	}
}

void Latk::write(string fileName) {
	vector<string> FINAL_LAYER_LIST;

	for (int hh = 0; hh < layers.size(); hh++) {
		currentLayer = hh;

		vector<string> sb;
		vector<string> sbHeader;
		sbHeader.push_back("\t\t\t\t\t\"frames\":[");
		sb.push_back(ofJoinString(sbHeader, "\n")); //String.join("\n", sbHeader.toArray(new String[sbHeader.size()])));

		for (int h = 0; h < layers[currentLayer].frames.size(); h++) {
			layers[currentLayer].currentFrame = h;

			vector<string> sbbHeader;
			sbbHeader.push_back("\t\t\t\t\t\t{");
			sbbHeader.push_back("\t\t\t\t\t\t\t\"strokes\":[");
			sb.push_back(ofJoinString(sbbHeader, "\n"));/// String.join("\n", sbbHeader.toArray(new String[sbbHeader.size()])));
			for (int i = 0; i < layers[currentLayer].frames[layers[currentLayer].currentFrame].strokes.size(); i++) {
				vector<string> sbb;
				sbb.push_back("\t\t\t\t\t\t\t\t{");
				ofColor col = layers[currentLayer].frames[layers[currentLayer].currentFrame].strokes[i].strokeColor;
				string r = ofToString(col.r / 255.0);
				string g = ofToString(col.g / 255.0);
				string b = ofToString(col.b / 255.0);
				sbb.push_back("\t\t\t\t\t\t\t\t\t\"color\":[" + r + ", " + g + ", " + b + "],");

				if (layers[currentLayer].frames[layers[currentLayer].currentFrame].strokes[i].points.size() > 0) {
					sbb.push_back("\t\t\t\t\t\t\t\t\t\"points\":[");
					for (int j = 0; j < layers[currentLayer].frames[layers[currentLayer].currentFrame].strokes[i].points.size(); j++) {
						ofVec3f pt = layers[currentLayer].frames[layers[currentLayer].currentFrame].strokes[i].points[j] * (1.0 / globalScale);

						string x = ofToString(pt.x);
						string y = ofToString(pt.y);
						string z = ofToString(pt.z);

						if (j == layers[currentLayer].frames[layers[currentLayer].currentFrame].strokes[i].points.size() - 1) {
							sbb.push_back("\t\t\t\t\t\t\t\t\t\t{\"co\":[" + x + ", " + y + ", " + z + "], \"pressure\":1, \"strength\":1}");
							sbb.push_back("\t\t\t\t\t\t\t\t\t]");
						}
						else {
							sbb.push_back("\t\t\t\t\t\t\t\t\t\t{\"co\":[" + x + ", " + y + ", " + z + "], \"pressure\":1, \"strength\":1},");
						}
					}
				}
				else {
					sbb.push_back("\t\t\t\t\t\t\t\t\t\"points\":[]");
				}

				if (i == layers[currentLayer].frames[layers[currentLayer].currentFrame].strokes.size() - 1) {
					sbb.push_back("\t\t\t\t\t\t\t\t}");
				}
				else {
					sbb.push_back("\t\t\t\t\t\t\t\t},");
				}

				sb.push_back(ofJoinString(sbb, "\n"));// String.join("\n", sbb.toArray(new String[sbb.size()])));
			}

			vector<string> sbFooter;
			if (h == layers[currentLayer].frames.size() - 1) {
				sbFooter.push_back("\t\t\t\t\t\t\t]");
				sbFooter.push_back("\t\t\t\t\t\t}");
			}
			else {
				sbFooter.push_back("\t\t\t\t\t\t\t]");
				sbFooter.push_back("\t\t\t\t\t\t},");
			}
			sb.push_back(ofJoinString(sbFooter, "\n"));// String.join("\n", sbFooter.toArray(new String[sbFooter.size()])));
		}

		FINAL_LAYER_LIST.push_back(ofJoinString(sb, "\n"));// String.join("\n", sb.toArray(new String[sb.size()])));
	}

	vector<string> s;
	s.push_back("{");
	s.push_back("\t\"creator\": \"processing\",");
	s.push_back("\t\"grease_pencil\":[");
	s.push_back("\t\t{");
	s.push_back("\t\t\t\"layers\":[");

	for (int i = 0; i < layers.size(); i++) {
		currentLayer = i;

		s.push_back("\t\t\t\t{");
		//if (layers[currentLayer].name != none && layers[currentLayer].name != "") {
		if (layers[currentLayer].name != "") {
				s.push_back("\t\t\t\t\t\"name\": \"" + layers[currentLayer].name + "\",");
		}
		else {
			s.push_back("\t\t\t\t\t\"name\": \"UnityLayer " + ofToString(currentLayer + 1) + "\",");
		}

		s.push_back(FINAL_LAYER_LIST[currentLayer]);

		s.push_back("\t\t\t\t\t]");
		if (currentLayer < layers.size() - 1) {
			s.push_back("\t\t\t\t},");
		}
		else {
			s.push_back("\t\t\t\t}");
		}
	}
	s.push_back("            ]"); // end layers
	s.push_back("        }");
	s.push_back("    ]");
	s.push_back("}");

	string url = fileName;

	ofFile file;
	file.open(url, ofFile::WriteOnly);
	file << ofJoinString(s, "\n");
}