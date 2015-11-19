#version 330

in vec2 position;
in vec4 in_color;
in vec2 in_uv;

uniform mat4 MVP;

out vec4 color;
out vec2 uv;

void main()
{
    //Process vertex
    gl_Position = MVP * vec4(position, 0, 1);
	color = in_color;
	uv = in_uv;
}