#version 330
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;
uniform bool useRefraction;

float refractiveIndexAir = 1.00;
float refractiveIndexWater = 1.33;
float refractiveIndexIce = 1.309;
float refractiveIndexGlass = 1.52;
float refractiveIndexDiamond = 2.42;



void main()
{
  float ratio = refractiveIndexAir/refractiveIndexWater;
  vec3 I = normalize(Position - cameraPos);
  vec3 R = reflect(I, normalize(Normal));
  if(useRefraction){
    R = refract(I, normalize(Normal), ratio);
  }
  FragColor = vec4(texture(skybox, R).rgb, 1.0);
}
