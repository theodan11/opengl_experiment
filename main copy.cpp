#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<sstream>
#include<string>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>



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

    float vertices[32] = {
        -0.5f,      0.5f,    0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f,      -0.5f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f,      -0.5f,   0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         0.5f,      0.5f,    0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
    };

    unsigned int index[6] = {
        0, 1, 3,
        3, 1, 2  
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 32, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, index, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void*) 0 );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void*)( 3 * sizeof(float) ));

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
        float time = (float)glfwGetTime();
        float scaleFactor = 1.0f + 5.0f * sin(time * 2.0f);
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 1.0f) );
        modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f ,0.0f ));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleFactor, scaleFactor, 1.0f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

unsigned int shader(const char* vertexShaderPath, const char* fragmentShaderPath){
    std::string vertexShaderSource = loadShader(vertexShaderPath); 
    const char* vs = vertexShaderSource.c_str();
    std::cout<<vs<<std::endl;
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