#include "LatkLayer.h"

LatkLayer::LatkLayer() {
	//
}

void LatkLayer::run() {
	frames[currentFrame].run();
}

void LatkLayer::nextFrame() {
	currentFrame++;
	if (currentFrame > frames.size() - 1) currentFrame = 0;
}