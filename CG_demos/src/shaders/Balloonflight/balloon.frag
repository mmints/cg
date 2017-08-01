#version 330 core

in vec4 passPosition;
in vec3 passNormal;
in vec2 passUVCoord;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform sampler2D tex;

out vec4 fragmentColor;

void main(){
	
	// texture color
	vec4 color = vec4(texture(tex, passUVCoord).rgb, 1.0);
	
	//compute the light vector as the normalized vector between 
    //the vertex position and the light position:
    vec3 lightVector = normalize((viewMatrix * vec4(-1.0,1,0,0)).xyz);

    //compute the eye vector as the normalized negative vertex 
    //position in camera coordinates:
    vec3 eye = normalize(-passPosition.xyz);
    
    // //compute the normalized reflection vector using 
    // //GLSL's built-in reflect() function
    vec3 reflection = normalize(reflect(-lightVector, normalize(passNormal)));

    //comment in to use the phong lighting model
    float diffuse = max(dot(passNormal, lightVector), 0.0);
    float specular = pow(max(dot(reflection, eye), 0.0), 15);
    float ambient = 0.6;

    fragmentColor = vec4(
    //comment in to use the phong lighting model:
        diffuse  * color.rgb +  
        specular * vec3(0.1) + 
        ambient * color.rgb,
        1);

}