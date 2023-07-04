#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(){
    GLFWwindow* window;

    // Verifica se a lib GLFW inicializou
    if (!glfwInit())
        return -1;

    // Isso aqui significa que eu estou usando o OpenGL 4.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    // Existe dois OpenGL, o core e o compatibility. Estou dizendoq que vou usar o core.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Cria a janela
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Isso significa que "eu vou desenhar nessa janela, será minha área de desenho
    glfwMakeContextCurrent(window);

    // Inicializa o Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Glad não inicializou");
        glfwTerminate();
        return -1;
    }

    glClearColor(0.65f, 0.9f, 1.0f, 1.0f);

    // Loop do "jogo"
    while (!glfwWindowShouldClose(window))
    {
        // IMPLEMENTAR AQUI
        // ...

        // Reseta a tela (fill)
        glClear(GL_COLOR_BUFFER_BIT);
        // Buffer de desenho
        glfwSwapBuffers(window);
        // Gerencia os eventos de tecla e mouse (interação)
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}