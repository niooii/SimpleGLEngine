#version 330 core
layout (location=0) in vec3 pos;
layout (location=1) in vec4 col;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
void main(){
    mat4 mvp = projMat * viewMat * modelMat;
    vec4 pos = mvp * vec4(pos, 1.0);
    gl_Position = pos;
}