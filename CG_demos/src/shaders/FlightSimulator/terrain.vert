#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

out vec4 passPosition;
out vec3 passNormal;
out float height;

void main()
{
  gl_Position = projectionMatrix * viewMatrix * modelMatrix* vec4(position, 1);
  height = position.y;
  passPosition = viewMatrix * modelMatrix * vec4(position, 1);
  vec4 n = transpose(inverse(viewMatrix * modelMatrix)) * vec4(normal, 0);
  passNormal = normalize(n.xyz);
}