#version 330 core

// Input vertex data, different for all executions of this shader
layout(location = 0) in vec3 VertexPos;
layout(location = 1) in vec3 VertexNormal;
layout(location = 2) in vec2 VertexUV;
layout(location = 3) in uint VertexClr;

// Size of texture used for rendering
uniform mat4 MVP;
uniform mat4 ModelMatrix;

// Output data - will be interpolated by Fragment Shader
out vec3 FragmentPos;
out vec2 FragmentUV;
out vec4 FragmentColor;

void main()
{
	vec4 v = vec4(VertexPos, 1);
	gl_Position = MVP * v;
	FragmentPos = (ModelMatrix * v).xyz;
	FragmentUV = VertexUV;
	FragmentColor.r = ((VertexClr >> 16u) & 0xFFu) / 255.0f;
	FragmentColor.g = ((VertexClr >> 8u) & 0xFFu) / 255.0f;
	FragmentColor.b = ((VertexClr >> 0u) & 0xFFu) / 255.0f;
	FragmentColor.a = ((VertexClr >> 24u) & 0xFFu) / 255.0f;
}
