#version 400
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normalposition;
out vec4 ex_worldPosition;
out vec3 ex_worldNormal;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main() {
gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (position, 1.0);
mat4 normal=transpose(inverse(modelMatrix));
ex_worldPosition = modelMatrix * vec4(position,1.0f);
ex_worldNormal = vec3(normal * vec4(normalposition,1.0f));
}