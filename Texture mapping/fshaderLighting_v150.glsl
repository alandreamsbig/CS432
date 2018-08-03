#version 150
in vec4 color;	//get the interpolated color from the vertex shader
in vec2 textureCoord;  //get the interpolated texture location from the vertex shader

uniform sampler2D textureID;  //the texture unit to sample from

out vec4 fColor;


void main() 
{
    vec4 texColor = texture(textureID,textureCoord);  //get the texture color at location textureCoord
    fColor = color*texColor;  //apply the uniform color to the fragment
} 

