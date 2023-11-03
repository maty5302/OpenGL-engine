#version 330
in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 out_Color;

uniform vec3 cameraPosition;
uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform vec4 objectColor;
uniform float shininess;
uniform vec3 specularStrength;
uniform vec3 ambientStrength;
uniform float attenuation;

void main(void){
    vec3 lightVector = lightPosition - ex_worldPosition;
   
    vec4 specularStrength = vec4(specularStrength, 1.0); 

    float dot_product = max(dot(normalize(ex_worldNormal), normalize(lightVector)), 0.0);
    vec4 diffuse = dot_product * vec4(lightColor, 1.0f);
    
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition);
    vec3 halfwayDir = normalize(lightVector + viewDir);    
    
    float spec = pow(max(dot(normalize(ex_worldNormal), halfwayDir), 0.0), shininess);
    vec4 specular = specularStrength*spec*vec4(lightColor,1.0f);

    vec4 ambient = vec4(ambientStrength, 1.0);
    out_Color = (ambient + diffuse + specular)*objectColor*attenuation;
}