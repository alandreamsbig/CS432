#version 150

in vec4 vPosition;
in vec4 vColor;
out vec4 randomColor;

void main() 
{ 
  gl_Position = vPosition;
  randomColor = vColor;
  
}