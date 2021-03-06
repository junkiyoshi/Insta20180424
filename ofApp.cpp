#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(239);
	ofSetWindowTitle("Insta");

	ofSetColor(39);
	ofSetLineWidth(1.5);
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 50, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<string> words = {
		"あ", "い", "う", "え", "お",
		"か", "き", "く", "け", "こ",
		"さ", "し", "す", "せ", "そ",
		"た", "ち", "つ", "て", "と",
		"な", "に", "ぬ", "ね", "の",
		"は", "ひ", "ふ", "へ", "ほ",
		"ま", "み", "む", "め", "も",
		"や", "　", "ゆ", "　", "よ",
		"ら", "り", "る", "れ", "ろ",
		"わ", "　", "を", "　", "ん"
	};

	for (int words_index = 0; words_index < words.size(); words_index++) {
	
		if (words[words_index] == "　") {

			continue;
		}
		
		ofPoint word_size = ofPoint(this->font.stringWidth(words[words_index]), this->font.stringHeight(words[words_index]));
		vector<ofTTFCharacter> word_paths = this->font.getStringAsPoints(words[words_index]);
		ofPoint word_point = ofPoint(ofGetWidth() - (words_index / 5) * 72 - 38, 216 + (words_index % 5) * 72);

		ofPushMatrix();
		ofTranslate(word_point);

		for (int w_index = 0; w_index < word_paths.size(); w_index++) {

			vector<ofPolyline> outline = word_paths[w_index].getOutline();
			ofVec3f center = outline[0].getCentroid2D();

			ofBeginShape();
			for (int o_index = 0; o_index < outline.size(); o_index++) {

				if (o_index != 0) {

					ofNextContour(true);
				}

				outline[o_index] = outline[o_index].getResampledBySpacing(3);
				vector<ofPoint> vertices = outline[o_index].getVertices();
				for (int v_index = 0; v_index < vertices.size(); v_index++) {

					ofPoint point = ofPoint(vertices[v_index].x - word_size.x / 2, vertices[v_index].y + word_size.y / 2);
					point *= 0.5 + ofNoise((word_point.x + point.x * 0.01), (word_point.y + point.y) * 0.01, ofGetFrameNum() * 0.005);
					ofVertex(point);
				}
			}
			ofEndShape(true);
		}

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}