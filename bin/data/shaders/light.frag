#version 330

uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
uniform vec3 lightColor;
uniform vec3 cubeColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float specularStrength;
uniform int shininess;
uniform float ambientLightStrength;

in vec3 Normal;
in vec3 FragPos;
out vec4 fragColor;


void main (void) {
  vec3 ambientLight = lightColor * ambientLightStrength;
  vec3 norm = normalize(Normal.xyz);
  vec3 lightDir = normalize(lightPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  vec3 viewDir = normalize(viewPos - FragPos);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
  vec3 specular = specularStrength * spec * lightColor;
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;
  vec3 result = (ambientLight + diffuse + specular) * cubeColor;
  fragColor = vec4(result, 1.0);
}
