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

struct TextureMaterial {
  sampler2D diffuse;
  vec3      specular;
  float     shininess;
};

in vec2 TexCoords;

uniform Light light;
uniform Material material;
uniform TextureMaterial textMaterial;

uniform sampler2D diffuseText;

uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
uniform vec3 lightColor;
uniform vec3 cubeColor;
uniform vec3 viewPos;
//uniform float specularStrength;
//uniform int shininess;
//uniform float ambientLightStrength;

in vec3 Normal;
in vec3 FragPos;
out vec4 fragColor;

bool useTexMaterial = true;


void main (void) {
  vec3 norm = normalize(Normal.xyz);
  vec3 lightDir = normalize(light.position - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  
  if(!useTexMaterial){
    // ambient
    vec3 ambient = light.ambient * material.ambient;
    // diffuse
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    // specular
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (material.specular * spec);
    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
  }
  else{
    vec3 diffuse = light.diffuse * diff * vec3(texture(textMaterial.diffuse, TexCoords));
    vec3 ambient = light.ambient * vec3(texture(textMaterial.diffuse, TexCoords));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), textMaterial.shininess);
    vec3 specular = light.specular * (textMaterial.specular * spec);
    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
  }
}
