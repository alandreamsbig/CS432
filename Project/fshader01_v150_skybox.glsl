#version 150
in vec3 texCoord;
uniform samplerCube cubeMap;
out vec4 FragColor;


void main() 
{ 
    FragColor = texture(cubeMap, texCoord);
	FragColor.a = 1.0;
} 

