#version 450 core
out vec4 frag_color;

uniform vec4 base_color;

void main() 
{
    //frag_color = vec4(1.f, 0.f, 0.f, 1.f);
    frag_color = base_color;
    
}