#version 330 core

out vec4 fragmentColor;

uniform vec3 lightPosition;

in vec4 passPosition;
in vec3 passNormal;

void main(){
	
	vec3 lightVector = normalize(lightPosition - passPosition.xyz);
	vec3 eye = normalize(-passPosition.xyz);
	vec3 reflection = normalize(reflect(-lightVector, passNormal));
	
	float cos_phi = max(dot(lightVector, normalize(passNormal)), 0.0);
	float cos_psi = max(dot(eye, reflection), 0.0);
	
	vec3 ambientColor = vec3(0.3, 0.3, 0.2);
	vec3 diffColor = vec3(1.0, 0.0, 0.0);
	vec3 specColor = vec3(1.0, 1.0, 1.0);
	fragmentColor.rgb = diffColor * ambientColor;
	fragmentColor.rgb += diffColor * cos_phi;
	fragmentColor.rgb += specColor * pow(cos_psi, 15);
	
}