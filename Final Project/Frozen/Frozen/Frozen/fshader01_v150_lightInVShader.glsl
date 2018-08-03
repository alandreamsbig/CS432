#version 150
in vec4  color;
out vec4 FragColor;
in vec2 texCoord;
uniform sampler2D textureID;
void main() 
{ 
    FragColor = texture(textureID, texCoord) ;// + 0.5 *color;
} 