#version 330
in vec4 vertex;
in vec4 instance;

uniform vec3 angles;
uniform vec4[6] light; // ambient diffuse emission position shininess specular
uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 NM;

smooth out vec4 ambient;
smooth out vec4 diffuse;
smooth out vec4 specular;
smooth out vec3 Normal;
smooth out vec3 LightDir;
smooth out vec3 eyeVec;

void main()
{
    vec4 n;
    n.xyz = vertex.xyz;
    n.w = 0.0;
    n = normalize(NM*n);
    Normal = n.xyz;

    vec4 color=vertex;
    color[0] *= sin(angles[0]);
    //color[1] *= sin(gl_InstanceID*0.11);
    color[1] *= sin(angles[1]);
    color[2] *= sin(gl_VertexID*0.11);
    color += 1.0;
    color *= 0.5;
    vec3 vVertex = vec3 ( MV * vertex );
    LightDir = normalize(light[3].xyz-vVertex);
    eyeVec = -vVertex;
/*
    diffuse = gl_FrontMaterial.diffuse * light[1];
    ambient = gl_FrontMaterial.ambient * light[0];
    ambient += light[0] * gl_FrontMaterial.ambient;
*/
/*
    diffuse = (0.4*gl_FrontMaterial.diffuse+0.6*color) * gl_LightSource[0].diffuse;
    ambient = (0.4*gl_FrontMaterial.ambient+0.6*color) * gl_LightSource[0].ambient;
    ambient += gl_LightModel.ambient * gl_FrontMaterial.ambient;
*/
    diffuse = color * light[1];
    ambient = color * light[0];

    gl_Position.xyz = vertex.xyz * instance.w;
    gl_Position.w = 1;
    gl_Position.xyz += instance.xyz;
    gl_Position = MVP * gl_Position;
}
