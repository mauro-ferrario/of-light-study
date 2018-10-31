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


//Out for frag
out vec3 Position;
out vec3 Normal;

//Uniform setup in ofApp
uniform mat4 modView;
uniform mat4 model;

void main() {
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;
  Normal = ( inverse(transpose(modelMatrix)) * vec4(normal, 0.0)).xyz;
  Position = vec3(modelMatrix * vec4(position.xyz, 1.0));
}

