#version 140

uniform sampler3D dataFieldTex; 
uniform isampler2D edgeTableTex; 
uniform isampler2D triTableTex; 
uniform vec3 lightPos;
uniform float light_ambient, light_diffuse, global_ambient;
in vec4 position_out;
out vec4 out_Color;
const vec4 diffuse_material = vec4(0.7, 0.7, 0.7, 1.0);
const vec3 specularMaterial = vec3(0.99, 0.99, 0.99);
const vec4 ambient_material = vec4(0.1, 0.1, 0.1, 1.0);
uniform vec3 dataStep;

void main()
{	
	 vec3 grad = vec3(
		texture(dataFieldTex, (position_out.xyz+vec3(dataStep.x, 0, 0))).r - texture(dataFieldTex, (position_out.xyz+vec3(-dataStep.x, 0, 0))).r, 
		texture(dataFieldTex, (position_out.xyz+vec3(0, dataStep.y, 0))).r - texture(dataFieldTex, (position_out.xyz+vec3(0, -dataStep.y, 0))).r, 
		texture(dataFieldTex, (position_out.xyz+vec3(0,0,dataStep.z))).r - texture(dataFieldTex, (position_out.xyz+vec3(0,0,-dataStep.z))).r);
	

	
	vec3 lightVec=normalize(lightPos);// - (gl_ModelViewProjectionMatrix * position_out).xyz);
	
	vec3 normalVec = normalize(grad);
	
	float NdotL = max(dot(lightVec, normalVec), 0.0);
	
	vec4 diffuse = light_diffuse * diffuse_material;
	vec4 ambient = light_ambient * ambient_material;
	vec4 global_ambient = global_ambient * ambient_material;
	out_Color = NdotL * diffuse + ambient + global_ambient;
} 
