#version 150
out vec4 fColor;
in vec2 texCoord;
uniform sampler2D textureID;
void main() 
{ 
    fColor =  texture(textureID, texCoord); 
} 
