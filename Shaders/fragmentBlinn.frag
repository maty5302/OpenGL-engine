#version 330
in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 out_Color;

uniform vec3 cameraPosition;

void main(void){
    vec3 lightPosition= vec3(0.0,0.0,0.0);
    vec3 lightColor = vec3(1.0,1.0,1.0);
    vec3 lightVector = lightPosition - ex_worldPosition;
    
    vec4 specularStrength = vec4(0.2, 0.2, 0.2, 1.0);

    float dot_product = max(dot(normalize(lightVector), normalize(ex_worldNormal)), 0.0);
    vec4 diffuse = dot_product * vec4(lightColor, 1.0);
    
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition);
    vec3 halfwayDir = normalize(lightVector + viewDir);
    vec3 reflectDir = reflect ( - normalize(lightVector ), normalize (ex_worldNormal) );
    
    float spec = pow(max(dot(ex_worldNormal, halfwayDir), 0.0), 32.0);
    vec4 specular = specularStrength*  spec*vec4(lightColor,1.0f);

    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
    vec4 objectColor=vec4(0.385,0.647,0.812,1.0);
    out_Color = (ambient + diffuse + specular)*objectColor;
}