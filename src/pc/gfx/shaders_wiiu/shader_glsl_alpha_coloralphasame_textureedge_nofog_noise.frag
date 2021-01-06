
in      vec2      vTexCoord;
in      vec4      vFog;
in      vec4      vInput1;
in      vec4      vInput2;
in      vec4      vInput3;
in      vec4      vInput4;

uniform sampler2D uTex0;
uniform sampler2D uTex1;

layout(std140) uniform Mat {
    int frame_count;
    int window_height;

    int tex_flags;
    bool fog_used;
    bool alpha_used;
    bool noise_used;
    bool texture_edge;
    bool color_alpha_same;

    int c_0_0;
    int c_0_1;
    int c_0_2;
    int c_0_3;
    int c_1_0;
    int c_1_1;
    int c_1_2;
    int c_1_3;

    bool do_single_0;
    bool do_single_1;
    bool do_multiply_0;
    bool do_multiply_1;
    bool do_mix_0;
    bool do_mix_1;
};

vec4 texVal0 = vec4(0.0, 0.0, 0.0, 0.0);
vec4 texVal1 = vec4(0.0, 0.0, 0.0, 0.0);

float random(in vec3 value) {
    float random = dot(sin(value), vec3(12.9898, 78.233, 37.719));
    return fract(sin(random) * 143758.5453);
}

vec4 get_color_alpha(int item) {
    switch (item) {
        case 0: // SHADER_0
            return vec4(0.0, 0.0, 0.0, 0.0);
        case 1: // SHADER_INPUT_1
            return vInput1;
        case 2: // SHADER_INPUT_2
            return vInput2;
        case 3: // SHADER_INPUT_3
            return vInput3;
        case 4: // SHADER_INPUT_4
            return vInput4;
        case 5: // SHADER_TEXEL0
            return texVal0;
        case 6: // SHADER_TEXEL0A
            return vec4(texVal0.a, texVal0.a, texVal0.a, texVal0.a);
        case 7: // SHADER_TEXEL1
            return texVal1;
    }

    return vec4(0.0, 0.0, 0.0, 0.0);
}

vec4 get_texel() {
    if (do_single_0) {
        return get_color_alpha(c_0_3);
    } else if (do_multiply_0) {
        return get_color_alpha(c_0_0) * get_color_alpha(c_0_2);
    } else if (do_mix_0) {
        return mix(get_color_alpha(c_0_1), get_color_alpha(c_0_0), get_color_alpha(c_0_2));
    } else {
        return (get_color_alpha(c_0_0) - get_color_alpha(c_0_1)) * get_color_alpha(c_0_2) + get_color_alpha(c_0_3);
    }
}

void main() {
    texVal0 = texture(uTex0, vTexCoord);
    texVal1 = texture(uTex1, vTexCoord);

    vec4 texel = get_texel();
    if (texel.a > 0.3) texel.a = 1.0; else discard;

    texel.a *= floor(random(vec3(floor(gl_FragCoord.xy * (240.0 / float(window_height))), float(frame_count))) + 0.5);

    gl_FragColor = texel;
}
