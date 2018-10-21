#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetBackgroundColor(0, 0, 0);
  setupTextures();
  setupDefaultValues();
  setupGUI();
  setup3dElements();
  setupShader();
}

void ofApp::setupShader(){
  shader.load("shaders/light");
}

void ofApp::setup3dElements(){
  light.set(10, 10, 10);
  sphere.set(100, 100);
  plane.set(1000, 1000, 10, 10);
}

void ofApp::setupTextures(){
  // Texture
  ofDisableArbTex();
  textureImage.load("container.png");
  textureSpecularImage.load("container_specular.png");
}

void ofApp::setupDefaultValues(){
  useTextureMaterial = true;
  enableCamInteraction = false;
  drawSphere = true;
  drawCube1 = true;
  drawCube2 = true;
  drawPlane = false;
  lightPos = ofVec3f(0.0);
}

void ofApp::setupGUI(){
  gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
  gui->addToggle("Enable cam interaction", enableCamInteraction);
  ofxDatGuiFolder* lightFolder = gui->addFolder("Light", ofColor::white);
  ofxDatGuiFolder* textureFolder = gui->addFolder("Texture", ofColor::blue);
  ofxDatGuiFolder* meshFolder = gui->addFolder("Mesh", ofColor::red);
  
  // Light
  lightFolder->addSlider("Light pos x", -600, 600, 0);
  lightFolder->addSlider("Light pos y", -600, 600, 0);
  lightFolder->addSlider("Light pos z", -600, 600, 0);
  lightFolder->addColorPicker("Light Ambient Color", ofFloatColor(0.2));
  lightFolder->addColorPicker("Light Diffuse Color", ofFloatColor(0.5));
  lightFolder->addSlider("Light Specular", 0.0, 1.0, 1.0);
  
  // Material props
  
  textureFolder->addToggle("Use texture material", useTextureMaterial);
  textureFolder->addSlider("Material Shininess", 1.0, 8.0, 1.0);
  textureFolder->addLabel("Color material parameters");
  textureFolder->addColorPicker("Ambient Color", ofFloatColor(1,0.5,0.31));
  textureFolder->addColorPicker("Diffuse Color", ofFloatColor(1,0.5,0.31));
  textureFolder->addSlider("Specular", 0.0, 1.0, 0.5);
  
  meshFolder->addToggle("Draw sphere", drawSphere);
  meshFolder->addToggle("Draw cube 1", drawCube1);
  meshFolder->addToggle("Draw cube 2", drawCube2);
  meshFolder->addToggle("Draw plane", drawPlane);
  
  gui->onButtonEvent(this, &ofApp::onButtonEvent);
  gui->onSliderEvent(this, &ofApp::onSliderEvent);
  gui->onColorPickerEvent(this, &ofApp::onColorEvent);
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
  string label =  e.target->getLabel();
  if(label == "Use texture material"){
    useTextureMaterial = !useTextureMaterial;
  }
  if(label == "Enable cam interaction"){
    enableCamInteraction = !enableCamInteraction;
  }
  if(label == "Draw cube 1"){
    drawCube1 = !drawCube1;
  }
  if(label == "Draw cube 2"){
    drawCube1 = !drawCube2;
  }
  if(label == "Draw sphere"){
    drawSphere = !drawSphere;
  }
  if(label == "Draw plane"){
    drawPlane = !drawPlane;
  }
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
  string label =  e.target->getLabel();
  if(label == "Light pos x"){
    lightPos.x = e.target->getValue();
  }
  if(label == "Light pos y"){
    lightPos.y = e.target->getValue();
  }
  if(label == "Light pos z"){
    lightPos.z = e.target->getValue();
  }
  if(label == "Light Specular"){
    lightSpecular = e.target->getValue();
  }
  if(label == "Material Shininess"){
    materialShininess = e.target->getValue();
  }
  if(label == "Specular"){
    materialSpecular = e.target->getValue();
  }
}

void ofApp::onColorEvent(ofxDatGuiColorPickerEvent e)
{
  string label =  e.target->getLabel();
  if(label == "Light Ambient Color"){
    lightAmbientColor = e.target->getColor();
  }
  if(label == "Light Diffuse Color"){
    lightDiffuseColor = e.target->getColor();
  }
  
  if(label == "Ambient Color"){
    materialAmbientColor = e.target->getColor();
  }
  if(label == "Diffuse Color"){
    materialDiffuseColor = e.target->getColor();
  }
}

//--------------------------------------------------------------
void ofApp::update(){
  if(enableCamInteraction){
    cam.enableMouseInput();
  }
  else{
    cam.disableMouseInput();
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  cam.begin();
  ofSetColor(ofColor::yellow);//FRONT
  ofEnableDepthTest();
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  shader.begin();
  shader.setUniform1i("useTextureMaterial", useTextureMaterial);
  shader.setUniformTexture("diffuseText", textureImage.getTexture() , 1);
  shader.setUniform3f("viewPos", cam.getGlobalPosition());
  
  // Light
  shader.setUniform3f("light.position", lightPos);
  shader.setUniform3f("light.ambient", lightAmbientColor.r/255.0, lightAmbientColor.g/255.0, lightAmbientColor.b/255.0);
  shader.setUniform3f("light.diffuse", lightDiffuseColor.r/255.0, lightDiffuseColor.g/255.0, lightDiffuseColor.b/255.0);
  shader.setUniform3f("light.specular", lightSpecular, lightSpecular, lightSpecular);
  // Material
  shader.setUniform3f("material.ambient", materialAmbientColor.r/255.0, materialAmbientColor.g/255.0, materialAmbientColor.b/255.0);
  shader.setUniform3f("material.diffuse", materialDiffuseColor.r/255.0, materialDiffuseColor.g/255.0, materialDiffuseColor.b/255.0);
  shader.setUniform3f("material.specular", materialSpecular, materialSpecular, materialSpecular);
  shader.setUniform1f("material.shininess",  pow(2, (int)materialShininess));
  // Texture material
  shader.setUniform1f("textMaterial.shininess",  pow(2, (int)materialShininess));
  shader.setUniformTexture("textMaterial.diffuse", textureImage.getTexture() , 0);
  shader.setUniformTexture("textMaterial.specular", textureSpecularImage.getTexture() , 1);
  
  drawScene();
  shader.end();
  drawLights();
  ofDisableDepthTest();
  cam.end();
}

void ofApp::drawLights(){
  ofPushMatrix();
  ofTranslate(lightPos);
  ofSetColor(255);
  light.getMesh().draw();
  ofPopMatrix();
}

void ofApp::drawScene(){
  if(drawCube1){
    ofPushMatrix();
    ofTranslate(200,0);
    cube.draw();
    ofPopMatrix();
  }
  if(drawCube2){
    ofPushMatrix();
    ofTranslate(200,0,200);
    cube.getMesh().draw();
    ofPopMatrix();
  }
  if(drawSphere){
    ofPushMatrix();
    ofTranslate(-200,0);
    sphere.getMesh().draw();
    ofPopMatrix();
  }
  if(drawPlane){
    ofPushMatrix();
    ofRotateXDeg(-90);
    plane.getMesh().draw();
    ofPopMatrix();
  }
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
