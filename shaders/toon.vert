// simple toon vertex shader
// www.lighthouse3d.com
#version 330


uniform vec4[6] light; // ambient diffuse emission position shininess specular
uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 NM;
uniform float elapsed_time;

in vec4 vertex;
in vec4 instance;
in vec4 color;
in vec4 rotations;
in vec3 velocities;
in mat4 rotationMatrix;

smooth out vec3 normal, lightDir; 
smooth out vec4 vColor;

void main()
{	
    mat4 rotMat = rotationMatrix;

    //vec4 pos = vec4(vertex.xyz, 1);
    vec4 pos = rotMat * vec4(vertex.xyz, 1);
    pos.x += (velocities.x) * (2*cos(4*elapsed_time));
    pos.y += (velocities.y) * (2*sin(4*elapsed_time));
    pos.z -= (velocities.z * ((2*cos(4*elapsed_time) + (2*sin(4*elapsed_time)))));

    vec4 norm = normalize(vec4(pos.x, pos.y, 0.0, 0.0));

    // Lighting Calculations
    //vec4 n = normalize( NM * rotMat * norm );
    vec4 n = normalize( NM * norm );

    normal = n.xyz;

    //vec4 v4 = MV * rotMat * pos;
    vec4 v4 = MV * pos;

    vec3 v3 = v4.xyz / v4.w;

	lightDir = normalize(vec3(light[3].xyz - v3));
	//lightDir = normalize(vec3(light[3].xyz));

    vColor = color;

    //gl_Position = rotMat * pos * instance.w;
    gl_Position = pos * instance.w;
    gl_Position.w = 1;
    gl_Position.xyz += instance.xyz;
    gl_Position = MVP * gl_Position;
}
