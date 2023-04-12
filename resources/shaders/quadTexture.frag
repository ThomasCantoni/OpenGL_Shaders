#version 450 core
out vec4 frag_color;

uniform vec4 base_color;

//uniform sampler2D smile_tex; //default binding = 0
layout (binding = 0) uniform sampler2D tex0; //1
layout (binding = 1) uniform sampler2D tex1; //1

in vec2 vert_uv_out;

void main() 
{
    //frag_color = vec4(1.f, 0.f, 0.f, 1.f);
    //frag_color = base_color;
    vec4 texel_zero = texture(tex0, vert_uv_out);
    vec4 texel_one  = texture(tex1, vert_uv_out);

    //Like mask effect
    //frag_color = smile_texel * wood_texel;
    frag_color = mix(texel_zero, texel_one, 0.5f);
}