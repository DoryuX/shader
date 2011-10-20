#version 330
#extension GL_EXT_gpu_shader4 : enable

in vec4 ambient;
in vec4 diffuse;
in vec4 specular;
in vec4 shininess;
in vec4 color;

in vec3 Normal;
in vec3 LightDir;

uniform samplerBuffer tex_Positions;

//in vec4 TexCoord;

uniform float elapsed_time;

out vec4 vFragColor;

void main()
{
    float diff = max( 0.0, dot(normalize(Normal), LightDir) );

    vec3 vReflect = normalize( reflect(-LightDir, normalize(Normal)) );

    vFragColor = diffuse * diff;
    vFragColor += ambient;

    float spec = max(0.0, dot(normalize(Normal), vReflect));
    if(diffuse != 0) {
        float fSpec = pow(spec, shininess[0]);
        vec3 tSpec = specular.xyz * vec3(fSpec, fSpec, fSpec);
        clamp(tSpec, 0.0, 1.0);

        vFragColor.rgb += tSpec;
    }
}
