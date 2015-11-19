#version 330

uniform sampler2D tex;
in vec4 color;
in vec2 uv;


out vec4 c;
void main()
{
	c =  texture2D(tex, vec2(uv.x, -uv.y)) ;
    
}