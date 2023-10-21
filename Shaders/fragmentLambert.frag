#version 330
in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 out_Color;

uniform vec3 lightPosition;
uniform vec3 lightColor;

void main(void){
    vec3 lightVector = lightPosition - ex_worldPosition;
    float dot_product = max(dot(normalize(lightVector), normalize(ex_worldNormal)), 0.0);
    vec4 diffuse = dot_product * vec4(lightColor, 1.0);
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
    vec4 objectColor=vec4(0.385,0.647,0.812,1.0);
    out_Color = (ambient + diffuse)*objectColor;
}