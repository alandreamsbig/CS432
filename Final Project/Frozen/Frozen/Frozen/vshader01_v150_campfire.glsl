#version 150
in vec4 vPosition;	//vertex attribute for vertex position
in vec3 vNormal;
uniform mat4 model_matrix;  //the model matrix to transpose vertices from object coord to world coord
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
in vec2 vTexCoord;
out vec2 texCoord;
uniform vec4 lightPos2;
uniform vec4 lightAmbient2, lightDiffuse2, lightSpecular2;
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matAlpha;
out vec4 color;  
void main() 
{ 
	vec4 color2 = vec4(0,0,0,0);
	vec3 L, H, E, N;
	vec4 ambient, diffuse, specular;
	float Kd, Ks;
	N = normalize(view_matrix*model_matrix*vec4(vNormal, 0)).xyz;
	L = normalize((view_matrix*lightPos2).xyz);
	H = normalize(L+E);
	ambient = lightAmbient2*matAmbient;
	Kd = max(dot(L,N), 0.0);
	diffuse = Kd*lightDiffuse2*matDiffuse;
	Ks = pow(max(dot(N,H), 0.0), matAlpha);
	specular = Ks * lightSpecular2 * matSpecular;
	if(dot(L,N) < 0.0)
		specular = vec4(0,0,0,1);
	color2 = (ambient + diffuse + specular);
	color = color2;
	color[3] = 1.0;
	texCoord = vTexCoord;
	gl_Position = projection_matrix*view_matrix*model_matrix*(vPosition);  //assign th
}
