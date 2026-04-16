#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
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
    bool first = true;
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

    std::vector<int> listNumber = {6, 2, 4, 9, 7, 5, 8, 1, 3};

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
    // glBindVertexArray(0);

    Shader shaderProgram = Shader("../shader.v", "../shader.f");
    shaderProgram.use();
    GOBJECT mySquare = GOBJECT(mesh,  glm::vec3(8.0f, 9.0f, -1.0f));

    unsigned int projectionLoc = glGetUniformLocation(shaderProgram.program, "projection");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram.program, "view");
    unsigned int highlightLoc = glGetUniformLocation(shaderProgram.program, "highLighted");
    glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(45.0f), 600.0f/400.0f, 0.1f, 100.0f);
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-6.0f, -4.5f, -15.0f));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));

    glClearColor(0.3f, 0.2f, 0.6f, 1.0f);
    glfwSwapInterval(1);
    int count = 0;
    double sortTimer = 0; 
    double sortDelay = 0.3;
    double lastTime = glfwGetTime();
    
    int i = 0;
    int loopingJ = 0;
    while(!glfwWindowShouldClose(window)){
       
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.use();
     
       for(int i = 0; i < listNumber.size(); i++){
                if(i == loopingJ){
                    glUniform1i(highlightLoc, 1);
                }else{

                    glUniform1i(highlightLoc, 0);
                }
                mySquare.translateX(i * 1.1);
                mySquare.scaleY(listNumber[i]);
                mySquare.translateY(listNumber[i] / 2.0f);
                mySquare.update();
                mySquare.draw(shaderProgram.program);
                // std::cout<<count<<std::endl;
                // count ++;
            }
        double currentTime = glfwGetTime();
        double deltaTime = (currentTime - lastTime);

        lastTime = currentTime;
        sortTimer += deltaTime;
        std::cout<<sortTimer<<std::endl;

        if((i < listNumber.size() - 1) && sortTimer>= sortDelay){
            sortTimer = 0;

            if(i<listNumber.size()){
                if(loopingJ < listNumber.size() - i - 1 ){
                    if(listNumber[loopingJ] > listNumber[loopingJ+1]){
                        int temp = listNumber[loopingJ];
                        listNumber[loopingJ] = listNumber[loopingJ+1];
                        listNumber[loopingJ+1] = temp;
                    }

           
                    loopingJ++;
                }else{
                    loopingJ=0;
                    i++;
                }
            }
            else{
                std::cout<<"Sorted"<<std::endl;
            }

           
            
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

