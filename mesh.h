#ifndef MESH_H
#define MESH_H

#include<GL/glew.h>
#include<iostream>
#include<vector>


class Mesh{
    public:
        Mesh(std::vector<float> &vertices, std::vector<unsigned int> &indices);
        ~Mesh();
        void draw();
    private:
        unsigned int VAO, VBO, EBO;
        int indicesArraySize, verticesArraySize;

};

#endif