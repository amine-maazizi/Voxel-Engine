#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;  // Changed from vec2 to vec3

out float gradient;
out vec2 TexCoord;
out vec3 normal;  // Changed from vec2 to vec3

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    gradient = aPos.y;
    TexCoord = aTexCoord;
    
    // Transform normal to world space
    normal = mat3(transpose(inverse(model))) * aNormal;
}