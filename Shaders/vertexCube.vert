#version 450
layout(location = 0) in vec3 position;	
out vec3 fragPosition;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main() {
vec4 pos = projectionMatrix * mat4(mat3(viewMatrix))  * vec4 (position, 1.0);
gl_Position = pos;
fragPosition = position;
}