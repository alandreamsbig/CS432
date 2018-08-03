#version 150

in vec4 vPosition;	//vertex attribute for vertex position
in vec3 vNormal;

out vec4 color;  //to send to the fragment shader, interpolated along the way

uniform mat4 model_matrix;  //the model matrix to transpose vertices from object coord to world coord

uniform mat4 view_matrix;
uniform mat4 projection_matrix;

uniform vec4 lightPos1;
uniform vec4 lightAmbient1, lightDiffuse1, lightSpecular1;

uniform vec4 lightPos2;
uniform vec4 lightAmbient2, lightDiffuse2, lightSpecular2;

uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matAlpha;

uniform int enabled1, enabled2;

void main() 
{
	vec4 color1 = vec4(0,0,0,0);
	vec4 color2 = vec4(0,0,0,0);

	vec3 L, H, E, N;
	vec4 ambient, diffuse, specular;
	float Kd, Ks;

	vec3 pos = (view_matrix*model_matrix*vPosition).xyz;
	vec3 lightPosInCam = (view_matrix*lightPos1).xyz;
	N = normalize(view_matrix*model_matrix*vec4(vNormal, 0)).xyz;

	if( enabled1 == 1 )
	{
		L = normalize(lightPosInCam.xyz - pos);

		float dist = abs(distance(pos, lightPosInCam));

		E = normalize(vec3(0,0,0) - pos);
		
		H = normalize(L + E);

		ambient = lightAmbient1*matAmbient;
		Kd = max(dot(L,N), 0.0);
		diffuse = Kd*lightDiffuse1*matDiffuse;
		Ks = pow(max(dot(N,H), 0.0), matAlpha);
		specular = Ks*lightSpecular1*matSpecular;
		if(dot(L, N) < 0.0 )
			specular = vec4(0,0,0,0);
		float cspot;
	

		float theta = abs(acos(dot(L, vec3(0,0,1))));
		cspot = pow( max(dot(L,vec3(0,0,1)), 0.0), 5);


		if( theta > radians(10.0) )
			cspot = 0.0;
	

		color1 = color1 + cspot * 1.0/pow(abs(dist),.25) * (ambient+diffuse+specular);
	}
	

	if( enabled2 == 1 )
	{
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
	}

	color = color1 + color2;
	color[3] = 1.0;

	gl_Position = projection_matrix*view_matrix*model_matrix*vPosition;
}