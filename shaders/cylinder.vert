#version 330
#extension GL_EXT_gpu_shader4 : enable

in vec4 vertex;
in vec4 instance;
in vec4 color;
in vec4 rotations;

in vec3 velocities;

in mat4 rotationMatrix;

uniform samplerBuffer tex_Positions;

uniform float elapsed_time;

uniform vec4[6] light; // ambient diffuse emission position shininess specular
uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 NM;

smooth out vec4 ambient;
smooth out vec4 diffuse;
smooth out vec4 specular;
smooth out vec4 shininess;
smooth out vec3 Normal;
smooth out vec3 LightDir;

//smooth out vec4 TexCoord;

mat4 RotateMatrix( const in float angle, const in vec3 axis ) {
    vec3 n = normalize( axis );

    vec3 r = rotations.xyz;

    //float theta = radians( angle );
    float theta = angle;

    float c = cos( theta );
    float s = sin( theta );

    mat3 R;
    R[0] = n.xyz * n.x * (1.0 - c) + vec3( c, n.z*s, -n.y*s );
    R[1] = n.xyz * n.y * (1.0 - c) + vec3( -n.z*s, c, n.x*s );
    R[2] = n.xyz * n.z * (1.0 - c) + vec3( n.y*s, -n.x*s, c );

    return mat4( R[0],  0.0,
                 R[1],  0.0,
                 R[2],  0.0,
                 0.0, 0.0, 0.0, 1.0 );
}

void main()
{
    mat4 rotMat = rotationMatrix;
    //vec4 pos = texelFetch(tex_Positions, gl_InstanceID);

    vec4 pos = rotMat * vec4(vertex.xyz, 1);
    pos.x += (velocities.x) * (2*cos(4*elapsed_time));
    pos.y += (velocities.y) * (2*sin(4*elapsed_time));
    pos.z -= (velocities.z * ((2*cos(4*elapsed_time) + (2*sin(4*elapsed_time)))));


    //rotMat *= RotateMatrix(mod((rotations.x * elapsed_time), 360), vec3(1.0, 0.0, 0.0));
    //rotMat *= RotateMatrix(mod((rotations.y * elapsed_time), 360), vec3(0.0, 1.0, 0.0));
    //rotMat *= RotateMatrix(mod((rotations.z * elapsed_time), 360), vec3(0.0, 0.0, 1.0));

    //vec4 norm = normalize(vec4(pos.x, pos.y, 0.0, 0.0));
    vec4 norm = normalize(vec4(pos.x, pos.y, pos.z, 0.0));

    // Lighting Calculations
    //vec4 n = normalize( NM * rotMat * norm );
    vec4 n = normalize( NM * norm );

    Normal = n.xyz;

    //vec4 v4 = MV * rotMat * pos;
    vec4 v4 = MV * pos;

    vec3 v3 = v4.xyz / v4.w;

    LightDir = normalize(light[3].xyz - v3);

    diffuse = color * light[1];

    ambient = color * light[0];
    specular = light[5];
    shininess = light[4];

    //gl_Position = rotMat * pos * instance.w;
    gl_Position = pos * instance.w;
    gl_Position.w = 1;
    gl_Position.xyz += instance.xyz;
    gl_Position = MVP * gl_Position;
}
