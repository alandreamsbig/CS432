#version 150
out vec4 fColor;
in vec2 texCoord;
uniform sampler2D textureID;
in vec4  color;
void main() 
{ 
    fColor =  0.75*texture(textureID, texCoord) + 0.25*color;  //apply the uniform color to the fragment
} 
