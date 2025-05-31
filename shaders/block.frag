#version 330 core
out vec4 FragColor;

in float gradient;
in vec2 TexCoord;
in vec3 normal;

uniform sampler2D blockTexture;
uniform vec3 directionalLight; // should be normalized

void main()
{
    // Normalize the input normal
    vec3 norm = normalize(normal);
    
    // Compute the diffuse lighting intensity
    // Note: directionalLight should point FROM the light source TO the surface
    float diff = max(dot(norm, -directionalLight), 0.0);
    
    // Get base texture color
    vec4 texColor = texture(blockTexture, TexCoord);
    
    // Add ambient lighting
    float ambient = 0.8;
    float intensity = ambient + (1.0 - ambient) * diff;
    
    // Apply lighting and gradient
    vec4 finalColor = texColor * intensity * (1.0 - gradient);
    
    FragColor = finalColor;
}