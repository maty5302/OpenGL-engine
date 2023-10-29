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

void main(void){
    vec3 lightVector = lightPosition - ex_worldPosition;
    
    vec4 specularStrengthVec4 = vec4(specularStrength, 1.0f);

    float dot_product = max(dot(normalize(lightVector), normalize(ex_worldNormal)), 0.0);
    vec4 diffuse = dot_product * vec4(lightColor, 1.0);
    
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition);
    vec3 reflectDir = reflect ( - normalize(lightVector ), normalize (ex_worldNormal) );
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec4 specular = specularStrengthVec4*spec*vec4(lightColor,1.0f);

    if(dot(ex_worldNormal, lightVector)< 0.0){
		specular = vec4(0.0, 0.0, 0.0, 0.0);
	}

    vec4 ambient = vec4(ambientStrength, 1.0);

    out_Color = (ambient + diffuse + specular)*objectColor;
}