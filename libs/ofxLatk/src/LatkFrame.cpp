#include "LatkFrame.h"

LatkFrame::LatkFrame() { }

void LatkFrame::run() {
	for (int i = 0; i < strokes.size(); i++) {
		strokes[i].run();
	}
}