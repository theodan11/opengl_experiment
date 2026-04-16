#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<sstream>
#include<string>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<mesh.h>
#include<vector>
#include<game_object.h>


unsigned int shader(const char* vertexShaderPath, const char* fragmentShaderPath);
std::string loadShader(const char* path);
int main() {

    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(600, 400, "Bubble Sort", nullptr, nullptr);



    glfwMakeContextCurrent(window);
    // glewInit();

    glewExperimental = GL_TRUE;
    if(glewInit() == !GLEW_OK){
        std::cerr<<"Failed to initialize GLEW.";
    }

    glEnable(GL_DEPTH_TEST);

    std::vector<float> vertices = {
        -0.5f,      0.5f,    0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f,      -0.5f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f,      -0.5f,   0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         0.5f,      0.5f,    0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
    };

    std::vector<unsigned int> index = {
        0, 1, 3,
        3, 1, 2  
    };
    Mesh mesh = Mesh(vertices, index);
    GOBJECT mySquare = GOBJECT(mesh);
    // glBindVertexArray(0);

    unsigned int shaderProgram = shader("../shader.v", "../shader.f");
    glUseProgram(shaderProgram);

    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");

    glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(45.0f), 600.0f/400.0f, 0.1f, 100.0f);
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));

    glClearColor(0.3f, 0.2f, 0.8f, 1.0f);

    while(!glfwWindowShouldClose(window)){

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        // float time = (float)glfwGetTime();
        // float scaleFactor = 1.0f + 5.0f * sin(time * 2.0f);
        // glm::mat4 modelMatrix = glm::mat4(1.0f);
        // modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 1.0f) );
        // modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f ,0.0f ));
        // modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleFactor, scaleFactor, 1.0f));

        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        mySquare.rotateY((float)glfwGetTime() * 2);
        mySquare.scaleY(3.0f);
        mySquare.update();
        mySquare.draw(shaderProgram);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

unsigned int shader(const char* vertexShaderPath, const char* fragmentShaderPath){
    std::string vertexShaderSource = loadShader(vertexShaderPath); 
    const char* vs = vertexShaderSource.c_str();
    // std::cout<<vs<<std::endl;
    std::string fragmentShaderSource = loadShader(fragmentShaderPath);
    const char* fs = fragmentShaderSource.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vs, NULL);
    glShaderSource(fragmentShader, 1, &fs, NULL);
    
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    unsigned int program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

 
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;

}

std::string loadShader(const char* path){
    std::string content;

    std::ifstream fileStream(path, std::ios::in);

    if(!fileStream.is_open()){
        std::cerr<<"Error loading Shader path";
        return "";
    }

    std::stringstream stringStream;
    stringStream << fileStream.rdbuf();
    content  = stringStream.str();

    return content;
}