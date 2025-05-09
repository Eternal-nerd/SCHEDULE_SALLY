#version 450

#extension GL_EXT_nonuniform_qualifier : require

layout(binding = 1) uniform sampler2D texSamplers[];

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) flat in int inTexIndex;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = texture(texSamplers[nonuniformEXT(inTexIndex)], fragTexCoord);
    if (outColor.w < 0.8) {
        discard;
    }
}