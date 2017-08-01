#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uvCoord;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

out vec4 passPosition;
out vec3 passNormal;
out vec2 passUVCoord;


void main()
{
  gl_Position = projectionMatrix * viewMatrix * modelMatrix* vec4(position, 1);
  passPosition = viewMatrix * modelMatrix * vec4(position, 1);
  vec4 n = transpose(inverse(viewMatrix * modelMatrix)) * vec4(normal, 0);
  passNormal = normalize(n.xyz);
  passUVCoord = uvCoord;
}