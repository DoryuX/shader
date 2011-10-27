// simple toon fragment shader
// www.lighthouse3d.com
#version 330

uniform vec4[6] light; // ambient diffuse emission position shininess specular
uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 NM;
uniform float elapsed_time;

in vec3 normal, lightDir;
in vec4 vColor;

out vec4 vFragColor;

void main()
{
	float intensity;
	vec3 n;
	vec4 tColor;

	n = normalize(normal);
	intensity = max(dot(lightDir,n),0.0); 

	if (intensity > 0.98)
		tColor = vColor * vec4(0.8, 0.8, 0.8, 1.0);
	else if (intensity > 0.5)
		tColor = vColor * vec4(0.4, 0.4, 0.4, 1.0);	
	else if (intensity > 0.25)
		tColor = vColor * vec4(0.2, 0.2, 0.2, 1.0);
	else
		tColor = vColor;			

    vFragColor = tColor;
}
