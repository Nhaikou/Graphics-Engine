//Laatija: Ville Koskinen

#version 120

attribute vec2 position;
attribute vec4 in_color;
attribute vec2 in_uv;

uniform mat4 MVP;

varying vec4 color;
varying vec2 uv;


void main()
{
    gl_Position = MVP * vec4(position, 0, 1);
	color = in_color;
	uv = in_uv;
}