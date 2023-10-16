#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertex_Color;
out vec3 colorInput;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main() {
gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (position, 1.0);
colorInput = vertex_Color;
}