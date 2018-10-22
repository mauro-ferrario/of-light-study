#version 330

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light {
  vec3 position;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct DirectionalLight {
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct TextureMaterial {
  sampler2D diffuse;
  sampler2D specular;
  float     shininess;
};

uniform Light light;
uniform DirectionalLight directionalLight;
uniform Material material;
uniform TextureMaterial textMaterial;

uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
uniform vec3 lightColor;
uniform vec3 cubeColor;
uniform vec3 viewPos;
uniform bool useTextureMaterial;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
out vec4 fragColor;


void main (void) {
  vec3 norm = normalize(Normal.xyz);
  vec3 lightDir = normalize(light.position - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  float diffDirectional = max(dot(norm, normalize(-directionalLight.direction)), 0.0);
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  vec3 reflectDirDirectional = reflect(normalize(-directionalLight.direction), norm);
  vec3 result;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 directionalAmbient;
  vec3 directionalDiffuse;
  vec3 directionalSpecular;
  float shininess = (useTextureMaterial) ? textMaterial.shininess : material.shininess;
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  float specDirectional = pow(max(dot(viewDir, reflectDirDirectional), 0.0), material.shininess);
  if(!useTextureMaterial){
    ambient = light.ambient * material.ambient;
    diffuse = light.diffuse * (diff * material.diffuse);
    specular = light.specular * (material.specular * spec);
    directionalAmbient = directionalLight.ambient * material.ambient;
    directionalDiffuse = directionalLight.diffuse * (diffDirectional * material.diffuse);
    directionalSpecular = directionalLight.specular * (material.specular * specDirectional);
  }
  else{
    ambient = light.ambient * vec3(texture(textMaterial.diffuse, TexCoords));
    diffuse = light.diffuse * diff * vec3(texture(textMaterial.diffuse, TexCoords));
    specular = light.specular * spec * vec3(texture(textMaterial.specular, TexCoords));
    directionalAmbient = directionalLight.ambient * vec3(texture(textMaterial.diffuse, TexCoords));
    directionalDiffuse = directionalLight.diffuse * diffDirectional * vec3(texture(textMaterial.diffuse, TexCoords));
    directionalSpecular = directionalLight.specular * specDirectional * vec3(texture(textMaterial.specular, TexCoords));
  }
  result = ambient + diffuse + specular + directionalSpecular + directionalDiffuse + directionalAmbient;
  fragColor = vec4(result, 1.0);
}
