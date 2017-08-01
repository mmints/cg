#version 330 core

in vec4 positionAttribute;

uniform mat4 modelMatrix;

void main(){
    gl_Position = modelMatrix * positionAttribute;
    // gl_Position = positionAttribute;
}