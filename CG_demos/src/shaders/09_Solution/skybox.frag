#version 330

in vec2 passUVCoord;

uniform sampler2D tex;

out vec4 fragmentColor;

void main(){
	
	fragmentColor = vec4(texture(tex, passUVCoord).rgb,1.0);
}