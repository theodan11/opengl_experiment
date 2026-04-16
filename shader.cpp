#include<shader.h>


Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath){
    std::string vertexShaderString = loadShader(vertexShaderPath);
    std::string fragmentShaderString = loadShader(fragmentShaderPath);

    const char* vs = vertexShaderString.c_str();
    const char* fs = fragmentShaderString.c_str();

    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vs, NULL);
    glShaderSource(fShader, 1, &fs, NULL);

    glCompileShader(vShader);
    glCompileShader(fShader);

    program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);

    glDeleteShader(vShader);
    glDeleteShader(fShader);


}

Shader::~Shader(){
    glDeleteProgram(program);
}

std::string Shader::loadShader(const char* path){
    std::string content;

    std::ifstream fileStream(path, std::ios::in);
    if(!fileStream.is_open()){
        std::cerr<<"Failed to parse shader"<<std::endl;
        return "";
    }

    std::stringstream stringStream;
    stringStream << fileStream.rdbuf();
    content =  stringStream.str();
   
    return content;
}


void Shader::use(){
    glUseProgram(program);
}