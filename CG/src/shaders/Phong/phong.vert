#version 330 core

layout (location = 0) in vec4 positionAttribute;
layout (location = 1) in vec3 normalAttribute;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

out vec4 passPosition;
out vec3 passNormal;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix* positionAttribute;
	passPosition =viewMatrix * modelMatrix * positionAttribute;
	
	passNormal = mat3(transpose(inverse(viewMatrix * modelMatrix))) * normalAttribute;
}