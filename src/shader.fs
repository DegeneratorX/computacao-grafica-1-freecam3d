#version 330 core
out vec4 fragColor;

in vec4 vertexColor; // input variable from vertex shader (same name and type)

void main()
{
    fragColor = vertexColor;
}