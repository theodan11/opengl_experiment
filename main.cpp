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
#include<shader.h>

void bubbleSort(std::vector<int> arr);
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

    std::vector<int> listNumber = {6, 2, 4, 1, 3};

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
    GOBJECT mySquare = GOBJECT(mesh, glm::vec3(6.0f, -6.0f, -1.0f));
    // glBindVertexArray(0);

    Shader shaderProgram = Shader("../shader.v", "../shader.f");
    shaderProgram.use();

    unsigned int projectionLoc = glGetUniformLocation(shaderProgram.program, "projection");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram.program, "view");
    unsigned int modelLoc = glGetUniformLocation(shaderProgram.program, "model");

    glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(45.0f), 600.0f/400.0f, 0.1f, 100.0f);
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));

    glClearColor(0.3f, 0.2f, 0.8f, 1.0f);
    glfwSwapInterval(1);
    while(!glfwWindowShouldClose(window)){

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.use();

        for(int i = 0; i < listNumber.size(); i++){

            mySquare.translateX(i * 1.1);
            mySquare.scaleY(listNumber[i]);
            mySquare.translateY(listNumber[i] / 2.0f);
            mySquare.update();
            mySquare.draw(shaderProgram.program);
            std::cout<<listNumber[i]<<std::endl;
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}


void bubbleSort(std::vector<int> arr){

}