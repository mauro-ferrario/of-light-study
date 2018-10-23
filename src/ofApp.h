#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxAutoReloadedShader.h"

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
  
    ofxAutoReloadedShader shader;
//    ofShader              shader;
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
    void                  beginShader(glm::mat4 modelMatrix);
    void                  endShader();
  
    ofBoxPrimitive        cube;
    ofBoxPrimitive        cube2;
    ofSpherePrimitive     sphere;
    ofBoxPrimitive        light;
    ofSpherePrimitive     sphere2;
    ofEasyCam             cam;
  
    ofxDatGui*            gui;
    bool                  useTextureMaterial;
    bool                  enableCamInteraction;

    ofVec3f               lightPos;
    ofVec3f               cubePos;
    ofColor               lightAmbientColor;
    ofColor               lightDiffuseColor;
    float                 lightSpecular;
    float                 cubeRotation;
  
    float                 lightConstant;
    float                 lightLinear;
    float                 lightQuadratic;
  
    ofColor               materialAmbientColor;
    ofColor               materialDiffuseColor;
    float                 materialShininess;
    float                 materialSpecular;

    ofImage               textureImage;
    ofImage               textureSpecularImage;
  
  
    ofVec3f               directionalLightDirection;
    ofColor               directionalLightAmbientColor;
    ofColor               directionalLightDiffuseColor;
    float                 directionalLightSpecular;
  
    ofVec3f               spotLightDirection;
    ofVec3f               spotLightPos;
    ofColor               spotLightAmbientColor;
    ofColor               spotLightDiffuseColor;
    float                 spotLightSpecular;
    float                 spotLightCuttOff;
    float                 spotLightOuterCuttOff;
    float                 spotLightConstant;
    float                 spotLightLinear;
    float                 spotLightQuadratic;
};
