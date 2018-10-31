#version 330

//layout (location = 0) in vec3 aPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;


uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

in vec4  position;
out vec3 TexCoords;

void main()
{
  TexCoords = normalize(position.xyz);
//  gl_Position = projection * view * vec4(aPos, 1.0);
//  gl_Position = u_viewProjectionMatrix*u_modelMatrix*position;
 //gl_Position = projectionMatrix * viewMatrix * position;
  vec4 newPos = projectionMatrix * viewMatrix * vec4(position.xyz, 1.0);
  gl_Position = newPos.xyww;
} 
