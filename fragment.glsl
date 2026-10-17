#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1; // xadrez2x2.png
uniform sampler2D texture2; // madeira.png
uniform int materialID;

void main() {
    if (materialID == 0) {
        vec2 tiledCoord = TexCoord * 4.0;
        FragColor = texture(texture1, tiledCoord);
    } 
    else if (materialID == 1) {
        vec2 woodCoord = vec2(TexCoord.x * 4.0, TexCoord.y * 1.0); 
        FragColor = texture(texture2, woodCoord);
    } 
    else {
        FragColor = texture(texture2, TexCoord);
    }
}