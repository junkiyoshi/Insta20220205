#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	int hue = 0;
	int deg_span = 6;
	ofColor color;
	for (int deg = 0; deg < 360; deg += deg_span * 2) {

		for (int radius = 50; radius < 720; radius += 15) {

			hue = (radius / 2 - ofGetFrameNum() * 2) % 255;
			color.setHsb(hue, 180, 255);

			this->mesh.addVertex(glm::vec3(radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD), 0));
			this->mesh.addVertex(glm::vec3(radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD), 0));
			this->mesh.addColor(color);
			this->mesh.addColor(color);

			if (radius > 50) {

				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 3); this->mesh.addIndex(this->mesh.getNumVertices() - 4);
				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 4);
			}

		}
	}

	hue = (ofGetFrameNum() * 2) % 255;
	color.setHsb(hue, 255, 255);

	this->mesh.addVertex(glm::vec3());
	this->mesh.addColor(color);
	int center_index = this->mesh.getNumVertices() - 1;
	for (int deg = 0; deg < 360; deg += deg_span) {

		hue = (25 + ofGetFrameNum() * 2) % 255;
		color.setHsb(hue, 180, 255);

		this->mesh.addVertex(glm::vec3(35 * cos((deg + deg_span) * DEG_TO_RAD), 35 * sin((deg + deg_span) * DEG_TO_RAD), 0));
		this->mesh.addVertex(glm::vec3(35 * cos((deg - deg_span) * DEG_TO_RAD), 35 * sin((deg - deg_span) * DEG_TO_RAD), 0));

		this->mesh.addColor(color);
		this->mesh.addColor(color);

		this->mesh.addIndex(center_index);
		this->mesh.addIndex(this->mesh.getNumVertices() - 2);
		this->mesh.addIndex(this->mesh.getNumVertices() - 1);


	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	this->mesh.draw();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}