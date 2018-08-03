#version 150
in vec4 vPosition;	//vertex attribute for vertex position
in vec4 snowPos;
uniform mat4 model_matrix;  //the model matrix to transpose vertices from object coord to world coord
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
in vec2 vTexCoord;
out vec2 texCoord;
void main() 
{ 
	texCoord = vTexCoord;
	gl_Position = projection_matrix*view_matrix*model_matrix*(vPosition + snowPos);  //assign th
}