#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;
in vec4 FragPosLightSpace[10];

uniform sampler2D opal; // opal.png
uniform sampler2D dark_marble; // dark_marble.png
uniform sampler2DArray shadowMaps;

uniform int materialID;
uniform vec3 objectColor;
uniform int isSpecial;
uniform vec3 lightPos[10];
uniform vec3 lightIntensity[10];
uniform int size;
uniform float specularStrength;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir, float layer)
{
    // Converte de clip-space para coordenadas normalizadas [0, 1]
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    // Evita sombra fora do alcance do far_plane da luz
    if (projCoords.z > 1.0)
        return 0.0;

    // Bias dinâmico para evitar "shadow acne" (listras na superfície)
    float bias = max(0.005 * (1.0 - dot(normal, lightDir)), 0.0005);

    // PCF 3x3 para suavizar as bordas da sombra
    float shadow = 0.0;
    vec2 texelSize = 1.0 / vec2(textureSize(shadowMaps, 0));
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            vec3 uvLayer = vec3(projCoords.xy + vec2(x, y) * texelSize, layer);
            float pcfDepth = texture(shadowMaps, uvLayer).r;
            shadow += (projCoords.z - bias) > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    return shadow;
}

void main()
{
    vec4 baseColor;

    if (materialID == 2) {
        vec4 texColor = texture(opal, TexCoord);
        baseColor = texColor * vec4(objectColor, 1.0f);
    } else if (materialID == 3) {
        vec4 texColor = texture(dark_marble, TexCoord);
        baseColor = texColor * vec4(objectColor, 1.0f);
    } else {
        baseColor = vec4(objectColor, 1.0f);
    }

    if (isSpecial != 0) {
        baseColor = mix(baseColor, vec4(0.0f, 1.0f, 0.0f, 1.0f), 0.4f);
    }

    // ambient
    float ambientStrength = 0.25;
    vec3 lightColor = vec3(1.0, 1.0, 0.0);
    vec3 ambient = ambientStrength * lightColor;

    // diffuse 

    vec3 norm = normalize(Normal);
    vec3 diffuse = vec3(0.0);
    vec3 lighting = ambient;
    for (int i = 0; i < size; ++i) {
        vec3 lightDir = normalize(lightPos[i] - FragPos);
        vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightIntensity[i];
        float shadow = ShadowCalculation(FragPosLightSpace[i], norm, lightDir, float(i));
        lighting += (1.0 - shadow) * diffuse;

        // Specular
        vec3 viewDir = normalize(viewPos-FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lightIntensity[i];
        lighting += specular * objectColor * (1.0 - shadow);
    }

    
    FragColor = baseColor * vec4(lighting, 1.0);
}