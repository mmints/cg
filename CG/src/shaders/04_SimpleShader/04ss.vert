#version 330 core

in vec4 positionAttribute;
out vec4 pos;


void main(){
	pos = positionAttribute;
	pos.xy *= 2.0;
    gl_Position = pos;
}