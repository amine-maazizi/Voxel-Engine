#version 330 core
out vec4 FragColor;

in float gradient;

uniform vec4 top_grad;
uniform vec4 bottom_grad;

void main()
{
    FragColor = top_grad * (0.5 + gradient) - bottom_grad * (gradient - 0.5);
} 