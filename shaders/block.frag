#version 330 core
out vec4 FragColor;

in float gradient;
in vec2 TexCoord;
in vec3 normal;

uniform sampler2D blockTexture;
uniform vec3 directionalLight; // should be normalized

void main() {
    // Normalize the input normal
    vec3 norm = normalize(normal);
    
    // Normalize the directional light
    vec3 lightDir = normalize(directionalLight);
    
    // Compute the diffuse lighting intensity
    // Note: Using -lightDir because we want light pointing towards surface
    float diff = max(dot(norm, -lightDir), 0.0);
    
    // Get base texture color
    vec4 texColor = texture(blockTexture, TexCoord);
    
    // Add ambient lighting
    float ambient = 0.3;
    float lightIntensity = ambient + (1.0 - ambient) * diff;
    
    // Apply lighting (remove gradient effect for now to test texture)
    vec4 finalColor = texColor * lightIntensity;
    
    FragColor = finalColor;
}