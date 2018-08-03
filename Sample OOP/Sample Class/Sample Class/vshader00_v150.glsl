#version 150

in vec3 vPosition;
uniform mat3 model_matrix;



void main() 
{ 
  gl_Position = vec4((model_matrix*vPosition).xy,0,1);
}