#version 330
#define MAX_POINT_LIGHTS 4
in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 ex_texcoord;
out vec4 out_Color;

uniform vec3 cameraPosition;
uniform vec4 objectColor;
uniform float shininess;
uniform sampler2D textureUnitID;

struct Material{
    vec4 objectColor;
    float shininess;
};

struct SpotLight{
    int isDefined;
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct DirLight{
    int isDefined;
    vec3 direction;
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
	int isDefined;
	vec3 position;
	vec3 color;
	float constant;
	float linear;
	float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

float getAttenuation(float c, float l, float q, vec3 lightPos, vec3 worldPos)
{
    float d = length(lightPos - worldPos);
    float att = 1.0 / (c + l * d + q * d * d);
	return max(att, 0.0);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 cameraPos, Material material)
{
    float attenuation = getAttenuation(light.constant, light.linear, light.quadratic, light.position, fragPos);
    
	vec3 lightVector = normalize(light.position - fragPos);
    float dot_product = max(dot(normalize(lightVector), normalize(normal)), 0.0);
    vec3 diffuse = dot_product * light.diffuse * light.color;
    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect ( - normalize(lightVector ), normalize (normal) );
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * light.color;
	    if(dot(normal, lightVector)< 0.0){
            specular = vec3(0.0, 0.0, 0.0);
        }

    vec3 ambient = light.ambient * light.color;

    return (ambient + diffuse + specular)*attenuation;
}

vec3 CalcDirLight(DirLight light, vec3 normal, Material material, vec3 cameraPos, vec3 fragPos)
{
    vec3 lightVector = normalize(-light.direction);
    float dot_product = max(dot(normalize(normal), normalize(lightVector)), 0.0);
    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect ( - normalize(lightVector ), normalize (normal) );
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * light.color;
    vec3 diffuse = dot_product * light.diffuse * light.color;
    vec3 ambient = light.ambient * light.color;
    return (ambient + diffuse+specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, Material material, vec3 cameraPos, vec3 fragPos)
{
	vec3 lightVector = normalize(light.position - fragPos);
    float dot_product = max(dot(normalize(normal), normalize(lightVector)), 0.0);
    vec3 reflectDir = reflect ( - normalize(lightVector ), normalize (normal) );
    vec3 viewDir = normalize(cameraPos - fragPos);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    float attenuation = getAttenuation(light.constant, light.linear, light.quadratic, light.position, fragPos);

    float theta = dot(lightVector, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 diffuse = dot_product * light.diffuse * light.color * intensity;
    vec3 specular = light.specular * spec * light.color * intensity;
	vec3 ambient = light.ambient * light.color * intensity;

    return (ambient+diffuse+specular);
};


uniform PointLight pointLight[MAX_POINT_LIGHTS];
uniform DirLight dirLight;
uniform SpotLight spotLight;

void main(void){
    
    vec3 norm = normalize(ex_worldNormal);
    vec3 result;
    if(dirLight.isDefined == 1){
		result = CalcDirLight(dirLight, norm, Material(objectColor, shininess), cameraPosition, ex_worldPosition);
	}
    for(int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
		if(pointLight[i].isDefined == 1)
            result += CalcPointLight(pointLight[i], norm, ex_worldPosition, cameraPosition, Material(objectColor, shininess));
    }
    if(spotLight.isDefined == 1){
        result+= CalcSpotLight(spotLight, norm, Material(objectColor, shininess), cameraPosition, ex_worldPosition);
    }
    out_Color = texture(textureUnitID, ex_texcoord)* vec4(result, 1.0f) ;
}