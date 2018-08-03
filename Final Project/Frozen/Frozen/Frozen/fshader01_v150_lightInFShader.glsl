#version 150
in vec3 fN;
in vec3 fE;
in vec3 fL;
in vec3 fL2;
uniform vec4 lightAmbient1, lightDiffuse1, lightSpecular1;
uniform vec4 lightAmbient2, lightDiffuse2, lightSpecular2;
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matAlpha;
out vec4 FragColor;
in float dist1, dist2;
uniform int enabled1, enabled2;
in vec2 texCoord;
uniform sampler2D textureID;
void main() 
{ 
	vec4 color1 = vec4(0,0,0,0);
	vec4 color2 = vec4(0,0,0,0);
	vec3 L, H, E, N;
	vec4 ambient, diffuse, spec;
	float Kd, Ks;
	N = normalize(fN);
	if( enabled1 == 1 )
	{
		
		E = normalize(fE);
		L = normalize(fL);
	
		H = normalize(L+E);
		ambient = lightAmbient1*matAmbient;
		Kd = max(dot(L,N), 0.0);
		diffuse = Kd*lightDiffuse1*matDiffuse;
	
		Ks = pow(max(dot(N,H), 0.0), matAlpha);
		spec = Ks * lightSpecular1 * matSpecular;
	
		if(dot(-L,N) < 0.0)
			spec = vec4(0,0,0,1);
		float theta = abs(acos(dot(L, vec3(0,0,1))));
		float cspot = pow(max(dot(L,vec3(0,0,1)), 0.0), 5);
		if( theta > radians(10.0) )
			cspot = 0.0;
	
		color1 = color1 + 1.0/pow(abs(dist1),.25) * cspot *(ambient + diffuse+ spec) ;
	}
	
	
	
	
	if( enabled2 == 1 )
	{
		L = normalize(fL2);
		H = normalize(L+E);
		ambient = lightAmbient2*matAmbient;
		Kd = max(dot(L,N), 0.0);
		diffuse = Kd*lightDiffuse2*matDiffuse;
	
		Ks = pow(max(dot(N,H), 0.0), matAlpha);
		spec = Ks * lightSpecular2 * matSpecular;
	
		if(dot(L,N) < 0.0)
			spec = vec4(0,0,0,1);
	
		color2 =  (ambient + diffuse + spec);
	}
	vec4 fCol = color1 + color2;
	fCol.a = 1.0;
    FragColor = texture(textureID, texCoord) * fCol;
} 
