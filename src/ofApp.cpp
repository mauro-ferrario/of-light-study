#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  gui.setup();
  
  // Light
  gui.add(lightPos.setup("Light pos", ofVec3f(0), ofVec3f(600),ofVec3f(-600)));
  gui.add(lightAmbientColor.setup("Light Ambient Color", ofFloatColor(0.2), ofFloatColor(0), ofFloatColor(1)));
  gui.add(lightDiffuseColor.setup("Light Diffuse Color", ofFloatColor(0.5), ofFloatColor(0), ofFloatColor(1)));
  gui.add(lightSpecular.setup("Light Specular", 1.0, 0, 1));
  
  // Material props
  gui.add(materialAmbientColor.setup("Material Ambient Color", ofFloatColor(1,0.5,0.31), ofFloatColor(0), ofFloatColor(1)));
  gui.add(materialDiffuseColor.setup("Material Diffuse Color", ofFloatColor(1,0.5,0.31), ofFloatColor(0), ofFloatColor(1)));
  gui.add(materialShininess.setup("Material Shininess", 1, 1, 8));
  gui.add(materialSpecular.setup("Material Specular", 0.5, 0, 1));
  
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
  ofColor tempLightColor;
  shader.setUniform3f("light.position", lightPos);
  tempLightColor = lightAmbientColor;
  shader.setUniform3f("light.ambient", tempLightColor.r/255.0, tempLightColor.g/255.0, tempLightColor.b/255.0);
  tempLightColor = lightDiffuseColor;
  shader.setUniform3f("light.diffuse", tempLightColor.r/255.0, tempLightColor.g/255.0, tempLightColor.b/255.0);
  shader.setUniform3f("light.specular", lightSpecular, lightSpecular, lightSpecular);
  
  tempLightColor = materialAmbientColor;
  shader.setUniform3f("material.ambient", tempLightColor.r/255.0, tempLightColor.g/255.0, tempLightColor.b/255.0);
  tempLightColor = materialDiffuseColor;
  shader.setUniform3f("material.diffuse", tempLightColor.r/255.0, tempLightColor.g/255.0, tempLightColor.b/255.0);
  shader.setUniform3f("material.specular", materialSpecular, materialSpecular, materialSpecular);
  shader.setUniform1f("material.shininess",  pow(2, (int)materialShininess));
  
  
//  shader.setUniform1f("ambientLightStrength", ambientLightStrength);
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
