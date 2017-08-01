#version 330 core

uniform vec2 uniformHeightInterval;

out vec4 fragmentColor;

void main(){
	
	vec4 white = vec4(1.0,1.0,1.0,1.0);
	vec4 gray = vec4(0.2,0.2,0.2,1.0);
	vec4 green = vec4(0.3,0.8,0.3,1.0);
	
	fragmentColor = vec4(0.0,0.0,0.0,1.0);
	
}