#version 330
//Default from OF::programmableRenderer
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 cubeModelMatrix;

//Default from OF::shader
in vec4  position;
in vec3 normal;
in vec2  texcoord;
out vec3 FragPos;
out vec3 Normal;
//Out for frag
out vec4 colorVarying;
out vec2 TexCoords;

//Uniform setup in ofApp
uniform mat4 modView;
uniform mat4 model;

void main() {
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;
  FragPos = vec3(modelMatrix * vec4(position.xyz, 1.0));
  Normal = ( inverse(transpose(modelMatrix)) * vec4(normal, 0.0)).xyz;
  TexCoords = texcoord;
}
