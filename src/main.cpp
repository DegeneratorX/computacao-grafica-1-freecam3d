#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "cg1/shader_s.h"
#include "stbimage/stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "cg1/transformacoes.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void checkTextureErrors(unsigned char* data, int largura, int altura){
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

bool initGLFW(){
    // Verifica se a lib GLFW inicializou
    if (!glfwInit())
        return false;
    glfwInit();
    // Isso aqui significa que eu estou usando o OpenGL 4.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    // Existe dois OpenGL, o core e o compatibility. Estou dizendoq que vou usar o core.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return true;
}

GLFWwindow* getWindow(){
    GLFWwindow* window;
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    // Isso significa que "eu vou desenhar nessa janela, será minha área de desenho
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return window;
}

bool initGlad(){

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Glad não inicializou" << std::endl;
        glfwTerminate();
        return false;
    }
    return true;
}

int main(){
    // Verifica a inicialização do GLFL (OpenGL)
    if (!initGLFW()){return -1;}

    // Cria a janela com viewport configurada
    GLFWwindow* window = getWindow();

    // Verifica a inicialização do glad (OpenGL)
    if (!initGlad()){return -1;}

    Shader shaderFreeCam("../src/shader.vs", "../src/shader.fs");

    // Declaração de objetos
    float vertices[] = {
            // posições dos vertices (coluna 0 a 2), cores (coluna 3 a 5) e coordenadas de textura (colunas 6 e 7)
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
    };
    unsigned int indices[] = { // Isso aqui serve para não repetirmos vértices ao desenhar 2 triângulos (para formar o quadrado)
            0, 1, 3, // Primeiro triângulo
            1, 2, 3 // Segundo triângulo
    };

    unsigned int textura; // Toda textura é referenciada pelo ID
    glGenTextures(1, &textura); // input de quantas texturas queremos para gerar e guardar em um unsigned int array
    glBindTexture(GL_TEXTURE_2D, textura); // bind de textura

    // Parâmetros para filtros de textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
    // Atributos de posição
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Atributos de cores
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Atributos da coordenada de textura
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Carrega e gera a textura (guarda a textura na variável data)
    int texLargura, texAltura, canaisCores;
    unsigned char* data = stbi_load("../resources/textures/whitesquaredtexture.jpg", &texLargura, &texAltura, &canaisCores, 0);
    checkTextureErrors(data, texLargura, texAltura);

    // Desbindando, não tem mais necessidade
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Modo Wireframe (para visualizar os triângulos)
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    //glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

    // Loop do "jogo"
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        // Reseta a tela (fill)
        glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, textura); // Binda a textura
        glBindVertexArray(VAO);
        shaderFreeCam.use(); // Inicializa o shader

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