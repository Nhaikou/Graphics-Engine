//Laatija: Ville Koskinen

#version 120

varying vec2 position;
varying vec4 in_color;
varying vec2 in_uv;

uniform mat4 MVP;

varying out vec4 color;
varying out vec2 uv;


void main()
{
    gl_Position = MVP * vec4(position, 0, 1);
	color = in_color;
	uv = in_uv;
}