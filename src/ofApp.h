#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
  
  void drawScene();
  void drawLights();
  ofBoxPrimitive cube;
  ofBoxPrimitive light;
  ofPlanePrimitive plane;
  ofSpherePrimitive sphere;
  ofEasyCam cam;
  ofShader shader;

  ofxVec3Slider lightPos;
  ofxColorSlider lightAmbientColor;
  ofxColorSlider lightDiffuseColor;
  ofxFloatSlider  lightSpecular;
  
  ofxColorSlider materialAmbientColor;
  ofxColorSlider materialDiffuseColor;
  ofxIntSlider  materialShininess;
  ofxFloatSlider materialSpecular;

  ofImage textureImage;
  
  ofxPanel gui;
};
