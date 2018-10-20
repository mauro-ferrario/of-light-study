#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  gui.setup();
  gui.add(lightPos.setup("Light pos", ofVec3f(0), ofVec3f(600),ofVec3f(-600)));
  gui.add(specularStrength.setup("Specular Strength", 0.5, 0, 1));
  gui.add(shininess.setup("Shininess", 1, 1, 8));
  gui.add(ambientLightStrength.setup("ambientLightStrength", 0.1, 0.0, 1.0));
  gui.add(lightColor.setup("Light Color", ofColor(255), ofColor(0), ofColor(255)));
  gui.add(cubeColor.setup("Material Color", ofColor(255,0,0), ofColor(0), ofColor(255)));
  ofSetBackgroundColor(0, 0, 0);
  
  light.set(10, 10, 10);
  sphere.set(100, 100);
  cube.enableNormals();
  
  shader.load("shaders/light");
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
  cam.begin();
  ofSetColor(ofColor::yellow);//FRONT
  ofEnableDepthTest();
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  shader.begin();
  shader.setUniform3f("viewPos", cam.getGlobalPosition());
  ofColor tempLightColor = lightColor;
  shader.setUniform3f("lightColor", tempLightColor.r/255.0, tempLightColor.g/255.0, tempLightColor.b/255.0);
  tempLightColor = cubeColor;
  shader.setUniform3f("cubeColor", tempLightColor.r/255.0, tempLightColor.g/255.0, tempLightColor.b/255.0);
  shader.setUniform3f("lightPos", lightPos);
  shader.setUniform1f("specularStrength", specularStrength);
  shader.setUniform1i("shininess", (int) pow(2, (int)shininess));
  shader.setUniform1f("ambientLightStrength", ambientLightStrength);
  drawScene();
  shader.end();
  drawLights();
  ofDisableDepthTest();
  cam.end();
  gui.draw();
}

void ofApp::drawLights(){
  ofPushMatrix();
  ofTranslate(lightPos);
  ofSetColor(255);
  light.getMesh().draw();
  ofPopMatrix();
}

void ofApp::drawScene(){
  ofPushMatrix();
  ofTranslate(200,0);
  sphere.getMesh().draw();
  ofPopMatrix();
  ofPushMatrix();
  ofTranslate(-200,0);
  sphere.getMesh().draw();
  ofPopMatrix();
  ofPushMatrix();
  ofTranslate(200,0,200);
  cube.getMesh().draw();
  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
