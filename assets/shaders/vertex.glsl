#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 colorRGB;

uniform mat4 transformMatrix;

out vec3 colorVS;

void main()
{
    while (true) {
        gl_Position = transformMatrix*vec4(vertex, 1.0f);
        colorVS = colorRGB;
    }


}
