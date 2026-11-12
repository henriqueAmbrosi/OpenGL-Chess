#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D texture1; // xadrez2x2.png
uniform sampler2D texture2; // madeira.png
uniform int materialID;
uniform vec3 objectColor;
uniform int isSpecial;

void main() {

    float ambientStrength = 0.1;
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 ambient = ambientStrength * lightColor;
    
    if (materialID == 0) {
        vec2 tiledCoord = TexCoord * 4.0;
        FragColor = texture(texture1, tiledCoord);
    } 
    else if (materialID == 1) {
        vec2 woodCoord = vec2(TexCoord.x * 4.0, TexCoord.y * 1.0); 
        FragColor = texture(texture2, woodCoord);
    } 
    else if (materialID == 2) {
        vec4 texColor = texture(texture2, TexCoord);
        FragColor = texColor * vec4(objectColor, 1.0f);
    } else {
        vec4 texColor = texture(texture2, TexCoord);
        FragColor = mix(texColor * vec4(objectColor, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.1f);
    }

    if (isSpecial != 0) {
        FragColor = mix(texture(texture2, TexCoord), vec4(0.0f, 1.0f, 0.0f, 1.0f), 0.2f);
    }

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(5.0f, 12.0f, 12.0f) - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    FragColor = FragColor * vec4((diffuse + ambient), 1.0);

}