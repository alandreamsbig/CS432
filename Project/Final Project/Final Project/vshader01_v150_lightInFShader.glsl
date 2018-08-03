#version 150

in vec4 vPosition;	//vertex attribute for vertex position
in vec3 vNormal;
in vec2 vTexCoord;

out vec2 texCoord;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

uniform vec4 lightPos1;
uniform vec4 lightPos2;

out vec3 fN;
out vec3 fE;
out vec3 fL;
out vec3 fL2;

out float dist1;
out float dist2;



void main() 
{
	texCoord = vTexCoord;
	vec3 pos = (view_matrix*model_matrix*vPosition).xyz;
	vec3 lightPosInCam = (view_matrix*lightPos1).xyz;
	vec3 lightPosInCam2 = (view_matrix*lightPos2).xyz;
	
	fN = normalize(view_matrix*model_matrix*vec4(vNormal, 0)).xyz;
	fE = normalize(vec3(0,0,0) - pos);
	fL = normalize(lightPosInCam - pos);
	fL2 = normalize(lightPosInCam2);

	dist1 = abs(distance(pos, lightPosInCam));
	dist2 = abs(distance(pos, lightPosInCam2));

	gl_Position = projection_matrix*view_matrix*model_matrix*vPosition;
}