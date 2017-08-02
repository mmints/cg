#version 330 core

in vec4 passPosition;
out vec4 fragmentColor;

void main(){
	fragmentColor = passPosition;
}