#ifndef SHADER_H
#define SHADER_H


#include<GL/glew.h>
#include<fstream>
#include<sstream>
#include<iostream>
#include<string>

class Shader{
    public:
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        ~Shader();

        unsigned int program;
        void use();
    private:
        std::string loadShader(const char* path);
};

#endif
