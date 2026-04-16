#version 330 core

in vec3 colour;

uniform int highLighted;
out vec4 color;

void main(){
    if(highLighted == 1){

        color = vec4(1.0, 0.3, 0.1, 1.0);
    }else{

        color = vec4(colour, 1.0);
    }
}