#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 tileMatrix;

uniform vec2 transVector;

out vec2 TexCoord;

void main()
{
	gl_Position = projection * view * tileMatrix * vec4(aPos, 1.0);
	TexCoord = aTexCoord + transVector;
}