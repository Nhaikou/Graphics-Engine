//Laatija: Ville Koskinen

#version 120

uniform sampler2D tex;
varying vec4 color;
varying vec2 uv;

varying out vec4 c;


void main()
{
	c =  texture2D(tex, vec2(uv.x, -uv.y)) ; 
}