#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec2 TexCoordShift;

void main()
{
vec4 texColor = texture(ourTexture, TexCoord);
//vec4 newColor = vec4(1.0, 0.0, 1.0, texColor.z);
FragColor = texColor;
}
