#version 330

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

// Point light
struct Light {
  vec3 position;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  
  float constant;
  float linear;
  float quadratic;
};

// Spot light
struct SpotLight {
  vec3 position;
  vec3 direction;
  float cutOff;
  float outerCutOff;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  
  float constant;
  float linear;
  float quadratic;
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
uniform SpotLight spotLight;
uniform Material material;
uniform TextureMaterial textMaterial;

uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
uniform vec3 lightColor;
uniform vec3 cubeColor;
uniform vec3 viewPos;
uniform bool useTextureMaterial;

uniform float near;
uniform float far;
uniform float time;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
out vec4 fragColor;

float pointLightMultiplier = 0.001;

#define M_PI 3.1415926535897932384626433832795

float LinearizeDepth(float depth)
{
  float z = depth * 2.0 - 1.0; // back to NDC
  return (2.0 * near * far) / (far + near - z * (far - near));
}

void main (void) {
  vec3 norm = normalize(Normal.xyz);
  vec3 spotLightDir = normalize(spotLight.position - FragPos);
  float diffSpot = max(dot(norm, spotLightDir), 0.0);
  float pointLightQuadratic = light.quadratic; // * pointLightMultiplier*0.01;
  float pointLightLinear = light.linear; // * pointLightMultiplier*0.001;
  vec3 reflectDirSpot = reflect(-spotLightDir, norm);
  float lightDistance = length(light.position - FragPos);
  float attenuation = 1.0 / (light.constant + pointLightLinear * lightDistance + pointLightQuadratic * (lightDistance * lightDistance));
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
  vec3 spotAmbient;
  vec3 spotDiffuse;
  vec3 spotSpecular;
  float shininess = (useTextureMaterial) ? textMaterial.shininess : material.shininess;
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
  float specSpot = pow(max(dot(viewDir, reflectDirSpot), 0.0), shininess);
  float specDirectional = pow(max(dot(viewDir, reflectDirDirectional), 0.0), shininess);
  
  float spotCutOff = 0.91; //M_PI/10.4; //0.604; //* 0.010;
  float outerCutOff = 0.82; //M_PI/12.0; // * 0.010;
  float constant = 1.0;
  float linear = 0.17;
  float quadratic = 0.192;
  
  // spotlight (soft edges)
  float theta = dot(spotLightDir, normalize(-spotLight.direction));
  float epsilon = (spotCutOff - outerCutOff);
  float intensity = clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);
  // attenuation
  float distanceSpot    = length(spotLight.position - FragPos);
  float attenuationSpot = 1.0 / (constant + linear * distanceSpot + quadratic * (distanceSpot));
  
  if(!useTextureMaterial){
    ambient = light.ambient * material.ambient;
    diffuse = light.diffuse * (diff * material.diffuse);
    specular = light.specular * (material.specular * spec);
    directionalAmbient = directionalLight.ambient * material.ambient;
    directionalDiffuse = directionalLight.diffuse * (diffDirectional * material.diffuse);
    directionalSpecular = directionalLight.specular * (material.specular * specDirectional);
    spotAmbient = spotLight.ambient * material.ambient;
    spotDiffuse = spotLight.diffuse * diffSpot * material.diffuse;
    spotSpecular = spotLight.specular * specSpot * material.specular;
  }
  else{
    ambient = light.ambient * vec3(texture(textMaterial.diffuse, TexCoords));
    diffuse = light.diffuse * diff * vec3(texture(textMaterial.diffuse, TexCoords));
    specular = light.specular * spec * vec3(texture(textMaterial.specular, TexCoords));
    directionalAmbient = directionalLight.ambient * vec3(texture(textMaterial.diffuse, TexCoords));
    directionalDiffuse = directionalLight.diffuse * diffDirectional * vec3(texture(textMaterial.diffuse, TexCoords));
    directionalSpecular = directionalLight.specular * specDirectional * vec3(texture(textMaterial.specular, TexCoords));
    spotAmbient = spotLight.ambient * texture(textMaterial.diffuse, TexCoords).rgb;
    spotDiffuse = spotLight.diffuse * diffSpot * texture(textMaterial.diffuse, TexCoords).rgb;
    spotSpecular = spotLight.specular * specSpot * texture(textMaterial.specular, TexCoords).rgb;
  }
  attenuation *= 1000000.0;
//  attenuation *= sin(time*4.0)*1000000.0;
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;
  
  spotDiffuse   *= intensity;
  spotSpecular *= intensity;
  
  attenuationSpot *= 1000.0;
  spotAmbient  *= attenuationSpot;
  spotDiffuse   *= attenuationSpot;
  spotSpecular *= attenuationSpot;
  
  result = ambient + diffuse + specular + directionalSpecular + directionalDiffuse + directionalAmbient;
  result += spotAmbient + spotDiffuse + spotSpecular;
  fragColor = vec4(result, 1.0);
//  fragColor = vec4(vec3(gl_FragCoord.z), 1.0); // Default depth with non linear equation
  float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
  fragColor = vec4(vec3(depth), 1.0);
  fragColor = vec4(vec3((1.0-depth)*result), 1.0); // Reverse depth color
}
