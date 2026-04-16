#include<game_object.h>

GOBJECT::GOBJECT(Mesh &mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
    mesh(mesh), position(position), rotation(rotation), scale(scale)
{
  
}

void GOBJECT::translateX(float x){
    position = glm::vec3(x, position.y, position.z);
}
void GOBJECT::translateY(float y){
    position = glm::vec3(position.x, position.y, position.z);
}
void GOBJECT::translateZ(float z){
    position = glm::vec3(position.x, position.y, z);
}


void GOBJECT::rotateX(float angle){
    rotation = glm::vec3(1.0f, 0.0f, 0.0f);
    this->angle = angle;
}
void GOBJECT::rotateY(float angle){
    rotation = glm::vec3(0.0f, 1.0f, 0.0f);
    this->angle = angle;
}
void GOBJECT::rotateZ(float angle){
    rotation = glm::vec3(0.0f, 0.0f, 1.0f);
    this->angle = angle;
}

void GOBJECT::scaleX(float scaleA){
    scale = glm::vec3(scaleA, 1.0f, 1.0f );
}
void GOBJECT::scaleY(float scaleA){
    scale = glm::vec3(1.0f, scaleA, 1.0f );
}
void GOBJECT::scaleZ(float scaleA){
    scale = glm::vec3(1.0f, 1.0f, scaleA );
}

void GOBJECT::update(){
    transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, position);
    if(rotation != glm::vec3(0.0f)){
        transformation = glm::rotate(transformation,  angle, rotation);
    }
    transformation = glm::scale(transformation, scale);


}

void GOBJECT::draw(unsigned int shaderProgram){
    unsigned int  modelLoc = glGetUniformLocation(shaderProgram, "model");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transformation));

    mesh.draw();
}


GOBJECT::~GOBJECT(){
    // mesh.destroy();
}
