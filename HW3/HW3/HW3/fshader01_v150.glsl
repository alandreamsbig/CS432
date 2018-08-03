#version 150
in vec4 color;	//get the interpolated color from the vertex shader
out vec4 fColor;

void main() 
{ 
    fColor = color;  //apply the uniform color to the fragment
} 

