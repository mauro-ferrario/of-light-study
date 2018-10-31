#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetBackgroundColor(0, 0, 0);
  setupTextures();
  setupDefaultValues();
  setupGUI();
  setup3dElements();
  setupShader();
  setupCubeMaps();
  
  reflectionShader.load("shaders/reflection");
  
  cam.setNearClip(.01);
  cam.setFarClip(100000);
}

void ofApp::setupCubeMaps(){
  ofDisableArbTex();
  skyCubeBox   = ofMesh::box(100000,100000,100000,1,1,1);
  sizeVboSkyMesh= skyCubeBox.getNumIndices();
  //vboSky.setMesh(skyCubeBox, GL_STATIC_DRAW);
  
  cubemapShader.load("shaders/skyCubemaps");
  loadCubeMapsImages();
  setupCubeMapsFaces();
}

void ofApp::setupCubeMapsFaces(){
  glDeleteTextures(1, &CubeMaptexture);
  
  glGenTextures(1, &CubeMaptexture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMaptexture);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  
  ofPixels back, front,up,down,left,right;
  back = cubeMapsImages[0].getPixels();
  front = cubeMapsImages[1].getPixels();
  up = cubeMapsImages[2].getPixels();
  down = cubeMapsImages[3].getPixels();
  left = cubeMapsImages[4].getPixels();
  right = cubeMapsImages[5].getPixels();
  int size = front.getWidth();
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, back.getData());
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, front.getData());
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, up.getData());
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, down.getData());
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, left.getData());
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, right.getData());
}

void ofApp::loadCubeMapsImages(){
  ofImage back;
  ofImage front;
  ofImage up;
  ofImage down;
  ofImage left;
  ofImage right;
  back.load("cubemaps/violentdays_bk.jpg");
  front.load("cubemaps/violentdays_ft.jpg");
  up.load("cubemaps/violentdays_up.jpg");
  down.load("cubemaps/violentdays_dn.jpg");
  left.load("cubemaps/violentdays_lf.jpg");
  right.load("cubemaps/violentdays_rt.jpg");
  cubeMapsImages.push_back(back);
  cubeMapsImages.push_back(front);
  cubeMapsImages.push_back(up);
  cubeMapsImages.push_back(down);
  cubeMapsImages.push_back(left);
  cubeMapsImages.push_back(right);
}

void ofApp::setupShader(){
  shader.load("shaders/light");
  stencilShader.load("shaders/stencil");
}

void ofApp::setup3dElements(){
  light.set(10, 10, 10);
  cube.set(1000, 1000, 1000, 1,1,1);
  cube2.set(1000, 1000, 1000, 1,1,1);
  sphere2.set(1000, 100);
}

void ofApp::setupTextures(){
  // Texture
  ofDisableArbTex();
  textureImage.load("container.png");
  textureSpecularImage.load("container_specular.png");
}

void ofApp::setupDefaultValues(){
  bUseRefraction = false;
  
  useTextureMaterial = true;
  enableCamInteraction = true;
  lightPos = ofVec3f(0.0, 0.0, 100.0);
  lightAmbientColor = ofColor(0);
  
  bDrawSkyCubemaps = true;
  
  bDrawStencil = false;
  stencilBorderPerc = 1.01;
  stencilBordercolor = ofColor(100);
  
  directionalLightDirection = ofVec3f(0.4,0.4,0.3);
  directionalLightAmbientColor = ofColor(0);
  
  lightConstant = 1.0;
  lightLinear = 0.09f;
  lightQuadratic = 0.032f;
  
  spotLightAmbientColor = ofColor(0);
  spotLightPos = ofVec3f(-9.84, 0.0, 88.52);
  spotLightDirection = ofVec3f(0.18,0.0,-1.0);
  spotLightSpecular = 1;
  spotLightCuttOff = 0.86;
  spotLightConstant = 1.0;
  spotLightLinear = 0.09;
  spotLightQuadratic = 0.032;
}

void ofApp::setupGUI(){
  gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
  gui->addSlider("Camera near clip", 0.0001, 1.00, 0.01);
  gui->addSlider("Camera far clip", 100.00, 100000, 100000);
  gui->addToggle("Enable cam interaction", enableCamInteraction);
  gui->addToggle("Draw stencil", bDrawStencil);
  gui->addToggle("Draw cubemaps", bDrawSkyCubemaps);
  gui->addSlider("Stencil border perc", 1.00, 2.00, stencilBorderPerc);
  gui->addColorPicker("Stencil border color", stencilBordercolor);
  ofxDatGuiFolder* lightFolder = gui->addFolder("Point Light", ofColor::white);
  ofxDatGuiFolder* directionalLightFolder = gui->addFolder("Directional Light", ofColor::purple);
  ofxDatGuiFolder* spotLightFolder = gui->addFolder("Spot Light", ofColor::purple);
  ofxDatGuiFolder* textureFolder = gui->addFolder("Texture", ofColor::blue);
  ofxDatGuiFolder* meshFolder = gui->addFolder("Mesh", ofColor::red);
  ofxDatGuiFolder* cubeMapsFolder = gui->addFolder("Cubemaps", ofColor::red);
  
  
  // Light
  lightFolder->addSlider("Light pos x", -6000, 6000, 0);
  lightFolder->addSlider("Light pos y", -6000, 6000, 0);
  lightFolder->addSlider("Light pos z", -6000, 6000, 0);
  
  lightFolder->addSlider("Light Linear", 0.0014, 0.7, lightLinear);
  lightFolder->addSlider("Light Quadratic", 0.000007, 1.8, lightQuadratic);
  
  lightFolder->addColorPicker("Light Ambient Color", ofFloatColor(0.2));
  lightFolder->addColorPicker("Light Diffuse Color", ofFloatColor(0.5));
  lightFolder->addSlider("Light Specular", 0.0, 1.0, 1.0);
  
  // Directional Light
  directionalLightFolder->addSlider("Light direction x", -1, 1, 0);
  directionalLightFolder->addSlider("Light direction y", -1, 1, 0);
  directionalLightFolder->addSlider("Light direction z", -1, 1, 0);
  directionalLightFolder->addColorPicker("Directional Ambient Color", ofFloatColor(0.2));
  directionalLightFolder->addColorPicker("Directional Diffuse Color", ofFloatColor(0.5));
  directionalLightFolder->addSlider("Directional Specular", 0.0, 1.0, 1.0);
  
  
  // Spot Light
  spotLightFolder->addSlider("Spot pos x", -6000, 6000, spotLightPos.x);
  spotLightFolder->addSlider("Spot pos y", -6000, 6000, spotLightPos.y);
  spotLightFolder->addSlider("Spot pos z", -6000, 6000, spotLightPos.z);
  spotLightFolder->addSlider("Spot direction x", -1, 1, spotLightDirection.x);
  spotLightFolder->addSlider("Spot direction y", -1, 1, spotLightDirection.y);
  spotLightFolder->addSlider("Spot direction z", -1, 1, spotLightDirection.y);
  spotLightFolder->addColorPicker("Spot Ambient Color", ofFloatColor(0.2));
  spotLightFolder->addColorPicker("Spot Diffuse Color", ofFloatColor(0.5));
  spotLightFolder->addSlider("Spot Specular", 0.0, 1.0, spotLightSpecular);
  spotLightFolder->addSlider("Spot cuttOff", 0.0, 21.0, spotLightCuttOff);
  spotLightFolder->addSlider("Spot outerCuttOff", 0.0, 21.0, spotLightOuterCuttOff);
  spotLightFolder->addSlider("Spot Linear", 0.0014, 0.7, spotLightLinear);
  spotLightFolder->addSlider("Spot Quadratic", 0.000007, 1.8, spotLightQuadratic);

  // Material props
  
  textureFolder->addToggle("Use texture material", useTextureMaterial);
  textureFolder->addSlider("Material Shininess", 1.0, 8.0, 1.0);
  textureFolder->addLabel("Color material parameters");
  textureFolder->addColorPicker("Ambient Color", ofFloatColor(1,0.5,0.31));
  textureFolder->addColorPicker("Diffuse Color", ofFloatColor(1,0.5,0.31));
  textureFolder->addSlider("Specular", 0.0, 1.0, 0.5);
  
  meshFolder->addSlider("Cube pos x", -6000, 6000, 0);
  meshFolder->addSlider("Cube pos y", -6000, 6000, 0);
  meshFolder->addSlider("Cube pos z", -6000, 6000, 0);
  meshFolder->addSlider("Cube rotation", 0, 360, 0);
  
  // Cube maps
  
  cubeMapsFolder->addToggle("Use refraction");
  
  gui->onButtonEvent(this, &ofApp::onButtonEvent);
  gui->onSliderEvent(this, &ofApp::onSliderEvent);
  gui->onColorPickerEvent(this, &ofApp::onColorEvent);
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
  string label =  e.target->getLabel();
  if(label == "Draw stencil"){
    bDrawStencil = !bDrawStencil;
  }
  
  if(label == "Draw cubemaps"){
    bDrawSkyCubemaps = !bDrawSkyCubemaps;
  }
  
  if(label == "Use texture material"){
    useTextureMaterial = !useTextureMaterial;
  }
  if(label == "Enable cam interaction"){
    enableCamInteraction = !enableCamInteraction;
  }
  
  if(label == "Use refraction"){
    bUseRefraction = !bUseRefraction;
  }
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
  string label =  e.target->getLabel();

  
  if(label == "Camera near clip"){
    cam.setNearClip(e.target->getValue());
  }
                    
  if(label == "Camera far clip"){
    cam.setFarClip(e.target->getValue());
  }
  
  if(label == "Stencil border perc"){
    stencilBorderPerc = e.target->getValue();
  }
  
  // Point light
  if(label == "Light pos x"){
    lightPos.x = e.target->getValue();
  }
  if(label == "Light pos y"){
    lightPos.y = e.target->getValue();
  }
  if(label == "Light pos z"){
    lightPos.z = e.target->getValue();
  }
  
  if(label == "Light linear"){
    lightLinear = e.target->getValue();
  }
  if(label == "Light quadratic"){
    lightQuadratic = e.target->getValue();
  }
  
  
  // Directional light
  if(label == "Light direction x"){
    directionalLightDirection.x = e.target->getValue();
  }
  if(label == "Light direction y"){
    directionalLightDirection.y = e.target->getValue();
  }
  if(label == "Light direction z"){
    directionalLightDirection.z = e.target->getValue();
  }
  if(label == "Light Specular"){
    lightSpecular = e.target->getValue();
  }
  
  if(label == "Directional Specular"){
    directionalLightSpecular = e.target->getValue();
  }
  if(label == "Material Shininess"){
    materialShininess = e.target->getValue();
  }
  
  // Spot light
  if(label == "Spot pos x"){
    spotLightPos.x = e.target->getValue();
  }
  if(label == "Spot pos y"){
    spotLightPos.y = e.target->getValue();
  }
  if(label == "Spot pos z"){
    spotLightPos.z = e.target->getValue();
  }
  if(label == "Spot direction x"){
    spotLightDirection.x = e.target->getValue();
  }
  if(label == "Spot direction y"){
    spotLightDirection.y = e.target->getValue();
  }
  if(label == "Spot direction z"){
    spotLightDirection.z = e.target->getValue();
  }
  if(label == "Spot Specular"){
    spotLightSpecular = e.target->getValue();
  }
  if(label == "Spot cuttOff"){
    spotLightCuttOff = e.target->getValue();
  }
  if(label == "Spot outerCuttOff"){
    spotLightOuterCuttOff = e.target->getValue();
  }
  if(label == "Spot linear"){
    spotLightLinear = e.target->getValue();
  }
  if(label == "Spot quadratic"){
    spotLightQuadratic = e.target->getValue();
  }
  
  
  if(label == "Specular"){
    materialSpecular = e.target->getValue();
  }
  if(label == "Cube pos x"){
    cubePos.x = e.target->getValue();
  }
  if(label == "Cube pos y"){
    cubePos.y = e.target->getValue();
  }
  if(label == "Cube pos z"){
    cubePos.z = e.target->getValue();
  }
  if(label == "Cube rotation"){
    cubeRotation = e.target->getValue();
  }
}

void ofApp::onColorEvent(ofxDatGuiColorPickerEvent e)
{
  string label =  e.target->getLabel();
  
  if(label == "Stencil border color"){
    stencilBordercolor = e.target->getColor();
  }
  
  if(label == "Light Ambient Color"){
    lightAmbientColor = e.target->getColor();
  }
  if(label == "Light Diffuse Color"){
    lightDiffuseColor = e.target->getColor();
  }
  
  if(label == "Directional Ambient Color"){
    directionalLightAmbientColor = e.target->getColor();
  }
  if(label == "Directional Diffuse Color"){
    directionalLightDiffuseColor = e.target->getColor();
  }
  
  
  if(label == "Spot Ambient Color"){
    spotLightAmbientColor = e.target->getColor();
  }
  if(label == "Spot Diffuse Color"){
    spotLightDiffuseColor = e.target->getColor();
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

void ofApp::beginShader(glm::mat4 modelMatrix){
  shader.begin();
  shader.setUniform1f("time", ofGetElapsedTimef());
  shader.setUniformMatrix4f("model", modelMatrix);
  shader.setUniform1f("near", cam.getNearClip());
  shader.setUniform1f("far", cam.getFarClip());
  shader.setUniform1i("useTextureMaterial", useTextureMaterial);
  shader.setUniformTexture("diffuseText", textureImage.getTexture() , 1);
  shader.setUniform3f("viewPos", cam.getGlobalPosition());
  
  // Light
  shader.setUniform3f("light.position", lightPos);
  shader.setUniform3f("light.ambient", lightAmbientColor.r/255.0, lightAmbientColor.g/255.0, lightAmbientColor.b/255.0);
  shader.setUniform3f("light.diffuse", lightDiffuseColor.r/255.0, lightDiffuseColor.g/255.0, lightDiffuseColor.b/255.0);
  shader.setUniform3f("light.specular", lightSpecular, lightSpecular, lightSpecular);
  // For the attenuation
  shader.setUniform1f("light.constant", lightConstant);
  shader.setUniform1f("light.linear", lightLinear);
  shader.setUniform1f("light.quadratic", lightQuadratic);
  
  
  // Directional Light
  shader.setUniform3f("directionalLight.direction", directionalLightDirection);
  shader.setUniform3f("directionalLight.ambient", directionalLightAmbientColor.r/255.0, directionalLightAmbientColor.g/255.0, directionalLightAmbientColor.b/255.0);
  shader.setUniform3f("directionalLight.diffuse", directionalLightDiffuseColor.r/255.0, directionalLightDiffuseColor.g/255.0, directionalLightDiffuseColor.b/255.0);
  shader.setUniform3f("directionalLight.specular", directionalLightSpecular, directionalLightSpecular, directionalLightSpecular);
  
  // Spot Light
  shader.setUniform3f("spotLight.position", spotLightPos);
  shader.setUniform3f("spotLight.direction", spotLightDirection);
  shader.setUniform3f("spotLight.ambient", spotLightAmbientColor.r/255.0, spotLightAmbientColor.g/255.0, spotLightAmbientColor.b/255.0);
  shader.setUniform3f("spotLight.diffuse", spotLightDiffuseColor.r/255.0, spotLightDiffuseColor.g/255.0, spotLightDiffuseColor.b/255.0);
  shader.setUniform3f("spotLight.specular", spotLightSpecular, spotLightSpecular, spotLightSpecular);
  shader.setUniform1f("spotLight.cutOff", spotLightCuttOff);
  shader.setUniform1f("spotLight.outerCutOff", spotLightOuterCuttOff);
  shader.setUniform1f("spotLight.linear", spotLightLinear);
  shader.setUniform1f("spotLight.quadratic", spotLightQuadratic);
  
  // Material
  shader.setUniform3f("material.ambient", materialAmbientColor.r/255.0, materialAmbientColor.g/255.0, materialAmbientColor.b/255.0);
  shader.setUniform3f("material.diffuse", materialDiffuseColor.r/255.0, materialDiffuseColor.g/255.0, materialDiffuseColor.b/255.0);
  shader.setUniform3f("material.specular", materialSpecular, materialSpecular, materialSpecular);
  shader.setUniform1f("material.shininess",  pow(2, (int)materialShininess));
  // Texture material
  shader.setUniform1f("textMaterial.shininess",  pow(2, (int)materialShininess));
  shader.setUniformTexture("textMaterial.diffuse", textureImage.getTexture() , 0);
  shader.setUniformTexture("textMaterial.specular", textureSpecularImage.getTexture() , 1);
}


void ofApp::endShader(){
  shader.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
  cam.begin();
  ofEnableDepthTest();
  if(bDrawStencil){
    drawStencil();
  }
  else if(bDrawSkyCubemaps){
    drawSkyCubemaps();
  }
  else{
    drawScene(false);
  }
  drawLights();
  ofDisableDepthTest();
  cam.end();
}

void ofApp::drawSkyCubemaps(){
  
  ofPushMatrix();
  ofTranslate(cubePos);
  ofRotateXDeg(cubeRotation);
  reflectionShader.begin();
  reflectionShader.setUniformMatrix4f("model", cube.getGlobalTransformMatrix());
  reflectionShader.setUniform3f("cameraPos", cam.getPosition());
  reflectionShader.setUniform1i("useRefraction", bUseRefraction);
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMaptexture);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  cube.getMesh().draw();
  reflectionShader.end();
  ofPopMatrix();
  
  ofPushMatrix();
  ofTranslate(5000.0,0,0);
  reflectionShader.begin();
  reflectionShader.setUniformMatrix4f("model", cube2.getGlobalTransformMatrix());
  reflectionShader.setUniform3f("cameraPos", cam.getPosition());
  reflectionShader.setUniform1i("useRefraction", bUseRefraction);
  sphere2.getMesh().drawFaces();
  reflectionShader.end();
  ofPopMatrix();
  
  glEnable(GL_CULL_FACE);
  glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
  cubemapShader.begin();
  cubemapShader.setUniform1i("skybox", 0);
  cubemapShader.setUniformMatrix4f("model", cube.getGlobalTransformMatrix());
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMaptexture);
  skyCubeBox.drawFaces();
  //  vboSky.drawElements(GL_TRIANGLES, sizeVboSkyMesh);
  glDepthFunc(GL_LESS); // set depth function back to default
  glDisable(GL_CULL_FACE);
  cubemapShader.end();
}

void ofApp::drawStencil(){
  glEnable(GL_STENCIL_TEST);
  glEnable(GL_DEPTH_TEST);
  glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glStencilFunc(GL_ALWAYS, 1, 0xFF);
  glStencilMask(0xff);
  drawScene(false);
  glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
  glStencilMask(0x00);
  glDisable(GL_DEPTH_TEST);
  stencilShader.begin();
  stencilShader.setUniform3f("color", stencilBordercolor.r/255.0, stencilBordercolor.g/255.0, stencilBordercolor.b/255.0);
  drawScene(true);
  stencilShader.end();
  glStencilMask(0xFF);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_STENCIL_TEST);
}

void ofApp::drawLights(){
  ofPushMatrix();
  ofTranslate(lightPos);
  ofSetColor(255);
  light.getMesh().draw();
  ofPopMatrix();
  ofPushMatrix();
  ofTranslate(spotLightPos);
  ofSetColor(255, 255,0);
  light.getMesh().draw();
  ofPopMatrix();
}

void ofApp::drawScene(bool drawStencil){
  ofPushMatrix();
  ofTranslate(cubePos);
  ofRotateXDeg(cubeRotation);
  if(drawStencil){
    ofPushMatrix();
    ofScale(ofVec3f(stencilBorderPerc));
  }
  if(!drawStencil)
    beginShader(cube.getGlobalTransformMatrix());
  cube.getMesh().draw();
  if(drawStencil){
    ofPopMatrix();
  }
  if(!drawStencil)
    endShader();
  ofPopMatrix();
  
  ofPushMatrix();
  ofTranslate(5000.0,0,0);
  if(!drawStencil)
    beginShader(cube2.getGlobalTransformMatrix());
  if(drawStencil){
    ofPushMatrix();
    ofScale(ofVec3f(stencilBorderPerc));
  }
  cube2.getMesh().draw();
  if(drawStencil){
    ofPopMatrix();
  }
  if(!drawStencil)
    endShader();
  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  if(key == 'f'){
    ofToggleFullscreen();
  }

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
