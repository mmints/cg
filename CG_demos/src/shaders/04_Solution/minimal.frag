#version 330 core

in vec4 pos;
out vec4 fragmentColor;

uniform vec2 mousePosition;

void main(){
	vec2 mouse = vec2(mousePosition.x, 600 - mousePosition.y);
	if (distance(gl_FragCoord.xy,mouse) < 100){
	    fragmentColor = vec4(0,0,1,0);
	} else{
		fragmentColor = pos;
	}
}