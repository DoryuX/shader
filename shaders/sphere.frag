#version 330

out vec4 vFragColor;

in vec3 eyeVec;
in vec4 ambient;
in vec4 diffuse;
in vec4 specular;

in vec3 Normal;
in vec3 LightDir;

void main()
{

    float diff = max ( 0.0, dot(normalize(Normal),normalize(LightDir)));
    vFragColor = diff * diffuse;

    vFragColor += ambient;
    
    vec3 vReflect = normalize(reflect(-normalize(LightDir),
                    normalize(Normal)));

    float spec = max(0.0,dot(normalize(Normal),vReflect));

    if ( diff > 0.0 ) {
        spec = pow(spec,128.0);
        vFragColor.rgb += vec3(0.8,0.8,0.8) * spec;
    }


}
