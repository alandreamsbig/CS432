#version 150

in vec4 vPosition;	//vertex attribute for vertex position
in vec3 vNormal;

out vec3 fN;
out vec3 fE;
out vec3 fL;
  //to send to the fragment shader, interpolated along the way

uniform mat4 model_matrix;  //the model matrix to transpose vertices from object coord to world coord
uniform mat4 proj_matrix;
uniform mat4 view_matrix;

//lighting stuff...
uniform vec4 lightPos;



void main() 
{ 

	vec3 pos = (view_matrix*model_matrix*vPosition).xyz;
	vec3 lightPosInCam = (view_matrix*lightPos).xyz;
	
	fN = normalize((view_matrix*model_matrix*vec4(vNormal,0)).xyz);
	fE = normalize(vec3(0,0,0)-pos);
	fL = normalize(lightPosInCam.xyz - pos);  
	
  	gl_Position = proj_matrix*view_matrix*model_matrix*vPosition;  //assign the vertex position to the vPosition attribute multiplied by the model matrix

}