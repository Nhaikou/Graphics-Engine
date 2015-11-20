//Laatija: Ville Koskinen

#version 120

uniform sampler2D tex;
varying vec4 color;
varying vec2 uv;


void main()
{
	gl_FragColor =  texture2D(tex, vec2(uv.x, -uv.y)) ; 
}