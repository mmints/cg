#version 330 core

in float height;
in vec4 passPosition;
in vec3 passNormal;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec2 heightInterval;

out vec4 fragmentColor;

void main(){
	
	vec4 white = vec4(1.0,1.0,1.0,1.0);
	vec4 gray = vec4(0.2,0.2,0.2,1.0);
	vec4 green = vec4(0.3,0.8,0.3,1.0);
	
	// normalize height ([minH,maxH] to [0.0,1.0])
	float minH = heightInterval.x;
	float maxH = heightInterval.y;
	float heightNorm = (height-minH)/(maxH-minH);
	vec4 color;
	if(heightNorm > 0.75)
	{	
		// normalize ([0.75,1.0] to [0.0,1.0])
		float heightNorm0 = (heightNorm -0.75)/(1.0-0.75);
		// interpolate between green and white
		color = heightNorm0 * white + (1.0-heightNorm0)* gray;
	}else 
	{	
		// normalize ([0.0,0.75] to [0.0,1.0])
		float heightNorm1 = heightNorm/0.75;
		// interpolate between blue and green
		color = heightNorm1 * gray + (1.0-heightNorm1)* green;
	}
	
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