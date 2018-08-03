#version 150

in vec4 vPosition;	//vertex attribute for vertex position
uniform mat4 modelview_matrix;
uniform mat4 projection_matrix;
out vec3 texCoord;

void main() 
{
	
	texCoord = normalize(vPosition.xyz);
	gl_Position = projection_matrix*modelview_matrix*vPosition;
}