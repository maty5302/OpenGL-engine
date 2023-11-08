#version 330
out vec4 frag_colour;
in vec2 pass_texture_coords;
uniform sampler2D textureUnitID;
void main () {
    //frag_colour = vec4(pass_texture_coords,1.0,1.0); 
    frag_colour = texture(textureUnitID, pass_texture_coords);
}