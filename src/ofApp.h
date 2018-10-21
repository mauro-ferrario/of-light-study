#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

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
  
    void                  drawScene();
    void                  drawLights();
    void                  onButtonEvent(ofxDatGuiButtonEvent e);
    void                  onSliderEvent(ofxDatGuiSliderEvent e);
    void                  onColorEvent(ofxDatGuiColorPickerEvent e);
  
    void                  setupDefaultValues();
    void                  setupGUI();
    void                  setupTextures();
    void                  setupShader();
    void                  setup3dElements();
  
    ofBoxPrimitive        cube;
    ofBoxPrimitive        light;
    ofPlanePrimitive      plane;
    ofSpherePrimitive     sphere;
    ofEasyCam             cam;
    ofShader              shader;
  
    ofxDatGui*            gui;
    bool                  useTextureMaterial;
    bool                  enableCamInteraction;
    bool                  drawPlane;
    bool                  drawCube1;
    bool                  drawCube2;
    bool                  drawSphere;

    ofVec3f               lightPos;
    ofColor               lightAmbientColor;
    ofColor               lightDiffuseColor;
    float                 lightSpecular;
  
    ofColor               materialAmbientColor;
    ofColor               materialDiffuseColor;
    float                 materialShininess;
    float                 materialSpecular;

    ofImage               textureImage;
    ofImage               textureSpecularImage;
};
