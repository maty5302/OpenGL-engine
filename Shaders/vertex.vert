#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertex_Color;
layout(location = 2) in vec2 texture_coords;	
out vec2 pass_texture_coords;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main() {
gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (position, 1.0);
pass_texture_coords = texture_coords;
}