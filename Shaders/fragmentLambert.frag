#version 330
in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 out_Color;

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform vec4 objectColor;
uniform vec3 ambientStrength;

void main(void){
    vec3 lightVector = lightPosition - ex_worldPosition;
    float dot_product = max(dot(normalize(lightVector), normalize(ex_worldNormal)), 0.0);
    vec4 diffuse = dot_product * vec4(lightColor, 1.0);
    vec4 ambient = vec4(ambientStrength, 1.0);
    out_Color = (ambient + diffuse)*objectColor;
}