#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec3 FragPos;
out vec2 TexCoord;
out vec3 Normal;
out vec4 FragPosLightSpace[10];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix[10];

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoord = aTexCoord;
    for (int i = 0; i < 10; ++i)
            FragPosLightSpace[i] = lightSpaceMatrix[i] * vec4(FragPos, 1.0);
    gl_Position = projection * view * vec4(FragPos, 1.0f);

}