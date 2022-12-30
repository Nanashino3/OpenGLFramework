#version 460 core

in vec2 fragTexCoord;
out vec4 outColor;

uniform float uAlpha;
uniform sampler2D uTexture;
uniform vec3 uTextColor;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uTexture, fragTexCoord).r);
	outColor = vec4(uTextColor, 1.0) * sampled;
}