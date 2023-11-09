#version 450
out vec4 frag_colour;
in vec3 fragPosition;
uniform samplerCube textureUnitID;
void main () {
    //frag_colour = vec4(fragPosition,1.0); 
    frag_colour = texture(textureUnitID, normalize(fragPosition));
}