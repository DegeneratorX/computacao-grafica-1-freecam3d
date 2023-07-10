#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "cg1/shader_s.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(){
    GLFWwindow* window;

    // Verifica se a lib GLFW inicializou
    if (!glfwInit())
        return -1;
    glfwInit();
    // Isso aqui significa que eu estou usando o OpenGL 4.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    // Existe dois OpenGL, o core e o compatibility. Estou dizendoq que vou usar o core.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Cria a janela
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Isso significa que "eu vou desenhar nessa janela, será minha área de desenho
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Inicializa o Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Glad não inicializou");
        glfwTerminate();
        return -1;
    }

    Shader shaderFreeCam("../src/shader.vs", "../src/shader.fs");

    // Declaração de objetos
    float vertices[] = {
            0.5f, 0.5f, 0.0f, // top right
            0.5f, -0.5f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f // top left
    };
    unsigned int indices[] = { // note that we start from 0!
            0, 1, 3, // first triangle
            1, 2, 3
    };

    // VBO = Vertex Buffer Objects — É uma variável que guarda uma enorme quantidade de vértices na memória da GPU.
    // VAO = Vertex Array Object — É uma variável que encapsula os vértices por uso de referência (ponteiro).
    // EBO = Element Buffer Objects — Serve para tratar objetos complexos como quadrado para dividir em 2 triângulos
    // Aqui estou inicializando o VBO e o VAO. Precisa bindar o VAO primeiro, e os métodos precisam estar
    // nessa ordem.
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // Leitura dos dados no ponteiro para o vertex buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    // Desbindando, não tem mais necessidade
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Modo Wireframe (para visualizar os triângulos)
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    // Loop do "jogo"
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        // Reseta a tela (fill)
        glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderFreeCam.use(); // Inicializa o shader
        glBindVertexArray(VAO);
        // IMPLEMENTAR AQUI
        // {


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // }

        // Buffer de desenho
        glfwSwapBuffers(window);
        // Gerencia os eventos de tecla e mouse (interação)
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}