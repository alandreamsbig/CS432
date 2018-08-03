#version 150

//vertex attributes (position, normal, texture location)
in vec4 vPosition;	
in vec3 vNormal;
in vec2 vTexture; 

out vec4 color;  //to send to the fragment shader, interpolated along the way
out vec2 textureCoord;  //pass through texture location to fragment shader

uniform mat4 model_matrix;  //the model matrix to transpose vertices from object coord to world coord
uniform mat4 proj_matrix;
uniform mat4 view_matrix;

//lighting stuff...
uniform vec4 lightPos;
uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matAlpha;


void main() 
{ 

	vec3 posInCam = (view_matrix*model_matrix*vPosition).xyz;
	vec3 lightInCam = (view_matrix*lightPos).xyz;
	
	vec3 L = normalize(lightInCam-posInCam);  
	vec3 V = normalize(-posInCam);
	vec3 H = normalize(L+V);
	vec3 N = normalize((view_matrix*model_matrix*vec4(vNormal,0)).xyz);
	
	vec4 ambient = lightAmbient*matAmbient;
	
	float Kd = max(dot(L,N),0.0);
	vec4 diffuse = Kd*lightDiffuse*matDiffuse;
	
	vec4 specular;
	if(dot(L,N)<0.0)
		specular = vec4(1,0,0,1);
	else{
		float Ks = pow(max(dot(N,H),0.0),matAlpha);
		specular = Ks*lightSpecular*matSpecular;
	}
	
	color = ambient + diffuse + specular;
	
	color.a = 1.0;
	
	
  	gl_Position = proj_matrix*view_matrix*model_matrix*vPosition;  //assign the vertex position to the vPosition attribute multiplied by the model matrix
  	
  	textureCoord = vTexture; //pass through texture location to fragment shader

}