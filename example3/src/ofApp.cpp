#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	latk = Latk("layer_test.json");   
   
	post.init(ofGetWidth(), ofGetHeight());
	post.createPass<FxaaPass>()->setEnabled(true);
	post.createPass<GodRaysPass>()->setEnabled(true);
	post.createPass<BloomPass>()->setEnabled(true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	post.begin(cam);
    //cam.begin(); // if not using post
	ofBackground(0);
	latk.run();
	post.end();// 
	//cam.end(); // if not using post
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'i') {
		// TODO
	}

	if (key == 'o') {
		latk.write("test.json");
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) { 

}

