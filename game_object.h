#ifndef GOBJECT_H
#define GOBJECT_H


#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<mesh.h>
#include<GLFW/glfw3.h>

class GOBJECT{
    public:
        GOBJECT(Mesh &mesh, glm::vec3 position = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 rotation = glm::vec3(0.0f) , glm::vec3 scale = glm::vec3(1.0f));
        ~GOBJECT();
        Mesh &mesh;
        glm::mat4 transformation;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        float angle = 0.0f;

        void translateX(float x);
        void translateY(float y);
        void translateZ(float z);


        void rotateX(float angle);
        void rotateY(float angle);
        void rotateZ(float angle);

        void scaleX(float scaleA);
        void scaleY(float scaleA);
        void scaleZ(float scaleA);

        void update();
        void draw(unsigned int shaderProgram);
        void rotate(float angle, glm::vec3 rotation);
    private:


};

#endif