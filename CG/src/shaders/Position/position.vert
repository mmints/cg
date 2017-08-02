#version 330 core

in vec4 positionAttribute;

out vec4 passPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectMatrix;


void main(){
    gl_Position = projectMatrix * viewMatrix * modelMatrix * positionAttribute;
	passPosition = modelMatrix * positionAttribute;
}