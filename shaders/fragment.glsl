#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;
in vec4 FragPosLightSpace;

uniform sampler2D texture1; // xadrez2x2.png
uniform sampler2D texture2; // madeira.png
uniform sampler2D shadowMap;

uniform int materialID;
uniform vec3 objectColor;
uniform int isSpecial;
uniform vec3 lightPos;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
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
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += (projCoords.z - bias) > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    return shadow;
}

void main()
{
    vec4 baseColor;

    if (materialID == 0) {
        vec2 tiledCoord = TexCoord * 4.0;
        baseColor = texture(texture1, tiledCoord);
    } 
    else if (materialID == 1) {
        vec2 woodCoord = vec2(TexCoord.x * 4.0, TexCoord.y * 1.0); 
        baseColor = texture(texture2, woodCoord);
    } 
    else if (materialID == 2) {
        vec4 texColor = texture(texture2, TexCoord);
        baseColor = texColor * vec4(objectColor, 1.0f);
    } else {
        vec4 texColor = texture(texture2, TexCoord);
        baseColor = mix(texColor * vec4(objectColor, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.1f);
    }

    if (isSpecial != 0) {
        baseColor = mix(texture(texture2, TexCoord), vec4(0.0f, 1.0f, 0.0f, 1.0f), 0.2f);
    }

    // ambient
    float ambientStrength = 0.15;
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 ambient = ambientStrength * lightColor;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // shadow
    float shadow = ShadowCalculation(FragPosLightSpace, norm, lightDir);

    vec3 lighting = ambient + (1.0 - shadow) * diffuse;
    FragColor = baseColor * vec4(lighting, 1.0);
}