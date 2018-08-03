#version 150
in vec4 vPosition;	//vertex attribute for vertex position
in vec4 vColor;
flat out vec4 color;  //to send to the fragment shader, interpolated along the way
uniform mat4 model_matrix;  //the model matrix to transpose vertices from object coord to world coord
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
void main() 
{ 
  gl_Position = projection_matrix*view_matrix*model_matrix*vPosition;  //assign the vertex position to the vPosition attribute multiplied by the model matrix
  color = vColor;  //assign vertex color to the vertex attribute "color".  Will be interpolated during rasterization
}