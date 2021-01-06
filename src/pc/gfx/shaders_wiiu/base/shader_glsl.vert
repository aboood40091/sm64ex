
#version 150

in  vec4 aVtxPos;
in  vec2 aTexCoord;
in  vec4 aFog;
in  vec4 aInput1;
in  vec4 aInput2;
in  vec4 aInput3;
in  vec4 aInput4;

out vec2 vTexCoord;
out vec4 vFog;
out vec4 vInput1;
out vec4 vInput2;
out vec4 vInput3;
out vec4 vInput4;

void main() {
    vTexCoord = aTexCoord;
    vFog = aFog;
    vInput1 = aInput1;
    vInput2 = aInput2;
    vInput3 = aInput3;
    vInput4 = aInput4;

    gl_Position = aVtxPos;
}
