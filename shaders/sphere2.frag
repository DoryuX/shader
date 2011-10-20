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

    vFragColor = ambient;

    vec3 N = normalize(Normal);
    vec3 L = normalize(LightDir);

    float lambert = dot(N,L);

    if ( lambert > 0.0 ) {
        vFragColor += 0.3 * diffuse * lambert;
        vec3 E = normalize(eyeVec);
        vec3 R = reflect(-L,N);
        float spec = pow(max(0.0,dot(R,E)),128.0);
        vFragColor.xyz += vec3(0.8,0.8,0.8) * spec;
    }
}
