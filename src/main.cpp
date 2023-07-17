#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <cg1/shader.h>
#include <cg1/camera.h>

#include "stbimage/stb_image.h"
#include "cg1/transformacoes.h"

#include <iostream>

// MODO WIREFRAME
bool wireframe = false;

// Tela
const unsigned int LARGURA_TELA = 800;
const unsigned int ALTURA_TELA = 600;

// Câmera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float ultimoX = LARGURA_TELA / 2.0f; // Divido por 2 para garantir que a posição inicial seja no centro
float ultimoY = ALTURA_TELA / 2.0f;
bool primeiroEventoMouse = true;

// timing
float deltaFrame = 0.0f;
float ultimoFrame = 0.0f;

// Sempre que o tamanho da janela é redimensionado, essa função executa
// --------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height); // A viewport precisa ser a mesma do tamanho da janela
}

// Sempre que o mouse se mexe, essa função é executada
// ---------------------------------------------------
void mouse_callback(GLFWwindow* window, double posxParametro, double posyParametro){
    // Inicialmente double, converto para float. static_cast é uma forma segura de conversão do C++, comparado com (float) do C.
    float posX = static_cast<float>(posxParametro);
    float posY = static_cast<float>(posyParametro);

    // Se for o primeiro evento do mouse
    if (primeiroEventoMouse){
        ultimoX = posX; // Guardo as últimas posições de X e Y registradas
        ultimoY = posY;
        primeiroEventoMouse = false;
    }

    // Cálculo de subtração padrão para movimentação de mouse
    float movX = posX - ultimoX;
    float movY = ultimoY - posY; // eixo Y invertido (padrão, é assim em jogos)

    // Atualizo as últimas posições dos mouse
    ultimoX = posX;
    ultimoY = posY;

    // Passo as informações para a câmera
    camera.movimentacaoMouse(movX, movY);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double movX, double movY){
    camera.campoDeVisao(static_cast<float>(movY));
}

// Processa os inputs do usuário
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window){
    // Se o usuário apertar Escape, sai do programa
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Se o usuário apertar WASD, movimenta a câmera
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.movimentacaoTeclado(FORWARD, deltaFrame);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.movimentacaoTeclado(BACKWARD, deltaFrame);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.movimentacaoTeclado(LEFT, deltaFrame);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.movimentacaoTeclado(RIGHT, deltaFrame);
    }
}

bool initGLFW(){
    // Verifica se a lib GLFW inicializou
    if (!glfwInit())
        return false;
    glfwInit();
    // Isso aqui significa que eu estou usando o OpenGL 4.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    // Existe dois OpenGL, o core e o compatibility. Estou dizendo que vou usar o core.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    return true;
}

GLFWwindow* getWindow(){
    GLFWwindow* window;
    window = glfwCreateWindow(LARGURA_TELA, ALTURA_TELA, "freecam3D", NULL, NULL);
    if (!window){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    // Isso significa que "eu vou desenhar nessa janela, será minha área de desenho"
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback); // Seta o mouse
    glfwSetScrollCallback(window, scroll_callback); // Seta o scroll

    // Fala pro opengl capturar o movimento do mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return window;
}

bool initGlad(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Glad não inicializou" << std::endl;
        glfwTerminate();
        return false;
    }
    return true;
}

// Proj Perspectiva
// ----------------
glm::mat4 perspectiva(float fov, float aspectRatio, float nearZ, float farZ) {
    glm::mat4 projecao(1.0f);

    float tgMetadeFov = std::tan(fov / 2.0f);
    float alcance = nearZ - farZ;

    projecao[0][0] = 1.0f / (aspectRatio * tgMetadeFov);
    projecao[1][1] = 1.0f / tgMetadeFov;
    projecao[2][2] = (nearZ + farZ) / alcance;
    projecao[2][3] = -1.0f;
    projecao[3][2] = 2.0f * nearZ * farZ / alcance;
    projecao[3][3] = 0.0f;

    return projecao;
}

// Método para não bagunçar a main, carrega texturas
// -----------------------------------------------
void loadTexture(const char* path, bool canalAlfa = true){
    int largura, altura, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &largura, &altura, &nrChannels, 0);
    if (data){
        if (canalAlfa) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else{
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Falha ao carregar a textura " << path << std::endl;
    }
    stbi_image_free(data);
}

int main(){
    // Verifica a inicialização do GLFL (OpenGL)
    // -----------------------------------------
    if (!initGLFW()){return -1;}

    // Cria a janela com viewport configurada
    //---------------------------------------
    GLFWwindow* window = getWindow();

    // Verifica a inicialização do glad (OpenGL)
    //-----------------------------------------
    if (!initGlad()){return -1;}

    // Ativa o z-buffer
    // ----------------
    glEnable(GL_DEPTH_TEST);

    // Inicializa os shaders (um para objetos que recebem uma fonte de luz e outro pro cubo que emite luz (não recebe luz)
    // -------------------------------------------------------------------------------------------------------------------
    Shader shaderComum("../src/shader_padrao.vs", "../src/shader_padrao.fs");
    Shader shaderCuboBranco("../src/shader_emissorluz.vs", "../src/shader_emissorluz.fs");

    // Vértices (coluna 0 a 2), Normais (coluna 3 a 5) e Textura (coluna 6 e 7) para qualquer cubo
    // Lembrar que qualquer cubo reaproveita esse array aqui, e ocorre transformação linear em cimaCamera
    // dele para diferenciar de outros.
    // Cada bloco desses são uma face, formados por 2 triângulos. Você pode ver os triângulos ativando
    // a opção de wireframe no começo do arquivo.
    // -------------------------------------------------------------------------------------------
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // Triângulo 1
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,// Triângulo 2
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
    };


    // VBO = Vertex Buffer Objects — É uma variável que guarda uma enorme quantidade de vértices na memória da GPU.
    // VAO = Vertex Array Object — É uma variável que encapsula os vértices por uso de referência (ponteiro).
    // EBO = Element Buffer Objects — Serve para tratar objetos complexos como quadrado para dividir em 2 triângulos
    // Aqui estou inicializando o VBO, o VAO e o EBO. Precisa bindar o VAO primeiro, e os métodos precisam estar
    // nessa ordem. (Depreciei o EBO)
    //-------------------------------------------------------------------------------------------------------------
    unsigned int VBO, VAOcuboNormal, EBO;
    glGenVertexArrays(1, &VAOcuboNormal);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAOcuboNormal); // Vincula o VAO ao OpenGL

    // Ponteiro que vai capturar as informações no array "vertices" da coluna 0 até 2 (posição dos vértices)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // atribuo como índice 0, são 3 floats (x,y,z), tamanho total da linha (8 floats), começa a ler na coluna 0
    glEnableVertexAttribArray(0); // Manda pro .vs (glsl) a informação para o "location 0"
    // Ponteiro que vai capturar as informações no array "vertices" da coluna 3 até 5 (posição das normais)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // atribuo como índice 1, são 3 floats (x,y,z), tamanho total da linha (8 floats), começa a ler na coluna 3
    glEnableVertexAttribArray(1); // Manda pro .vs (glsl) a informação para o "location 1"
    // Ponteiro que vai capturar as informações no array "vertices" da coluna 6 e 7 (coordenadas de textura)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // atribuo como índice 2, são 2 floats (x,y), tamanho total da linha (8 floats), começa a ler na coluna 6
    glEnableVertexAttribArray(2);

    // O cubo de luz usa o mesmo array de vertices (pois também é um cubo), e para qualquer cubo, irá utilizar aquele array
    unsigned int VAOCuboEmissorLuz; // Porém, o VAO é diferente, pois a forma que o objeto recebe iluminação é diferente

    // Faço a mesma coisa que o cubo normal, só não faço ponteiro pra normal, pois ele usa outro shader (não receberá iluminação, e será uma cor sólida).
    glGenVertexArrays(1, &VAOCuboEmissorLuz);
    glBindVertexArray(VAOCuboEmissorLuz);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texturas
    // --------
    unsigned int texAsfalto, texCalcada, texWindow,  texPorta, texFolhas, texTronco;

    // Textura do asfalto
    // ------------------
    glGenTextures(1, &texAsfalto);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texAsfalto);

    // Propriedades das texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Filtro das texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    loadTexture("../resources/textures/asfalto.jpg", false);

    // Textura da calçada
    // ------------------
    glGenTextures(1, &texCalcada);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texCalcada);

    // Propriedades das texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Filtro das texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    loadTexture("../resources/textures/concreto.png", true);

    // Textura da janela do prédio
    // ---------------------------
    glGenTextures(1, &texWindow);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texWindow);

    // Propriedades das texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Filtro das texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    loadTexture("../resources/textures/window.jpg", false);

    // Textura da porta do prédio
    // --------------------------
    glGenTextures(1, &texPorta);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, texPorta);

    // Propriedades das texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Filtro das texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    loadTexture("../resources/textures/porta.jpg", false);

    // Textura da folha da árvore
    // --------------------------
    glGenTextures(1, &texFolhas);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, texFolhas);

    // Propriedades das texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Filtro das texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    loadTexture("../resources/textures/leaves.jpg", false);

    // Textura do tronco da árvore
    // ---------------------------
    glGenTextures(1, &texTronco);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, texTronco);

    // Propriedades das texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Filtro das texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    loadTexture("../resources/textures/log.jpg", false);


    // Modo Wireframe (para visualizar os triângulos)
    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }

    shaderComum.use();

    float rotacao = 0.0f;
    float movimento = 0.0f; float velocidadeMovimento = 0.05f;
    // Loop do "jogo"
    // --------------
    while (!glfwWindowShouldClose(window))
    {
        // Irei trabalhar com frames (principalmente para controle de seta)
        // Precisarei de algumas variáveis do OpenGL
        // ----------------------------------------------------------------
        float frameAtual = static_cast<float>(glfwGetTime());
        deltaFrame = frameAtual - ultimoFrame; // Variação de tempo
        ultimoFrame = frameAtual;

        // Processa os inputs do usuário
        // -----------------------------
        processInput(window);

        // Reseta a tela (fill)
        // --------------------
        glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Memória temporária (buffer) de cor e zbuffer são resetados a cada frame

        // Ativa as texturas correspondes
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texAsfalto);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texCalcada);
        glBindVertexArray(VAOcuboNormal);

        // Ativo o shader para objetos normais e mando propriedades para o fragment shader de objetos normais
        shaderComum.use();
        shaderComum.setVec3("objectColor", 1.0f, 0.5f, 0.31f); // Cor do objeto
        shaderComum.setVec3("lightColor", 1.0f, 1.0f, 1.0f); // Cor da luz
        shaderComum.setVec3("lightPos", -3.0f, 3.0f, movimento); // Posição da luz
        shaderComum.setVec3("viewPos", camera.posicaoCamera); // Coordenadas de câmera

        // mando as propriedades de câmera e perspectiva para o vertex shader de objetos normais
        glm::mat4 projection = perspectiva(glm::radians(camera.fovCamera), (float)LARGURA_TELA / (float)ALTURA_TELA, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        shaderComum.setMat4("projection", projection);
        shaderComum.setMat4("view", view);

        // Transformação do asfalto
        shaderComum.setInt("textura", 0);
        glm::mat4 model = glm::mat4(1.0f);
        model = Transformacoes::translacao(model, glm::vec3(0.0f, -1.0f, 2.0f));
        model = Transformacoes::escala(model, glm::vec3(3.0f, 0.1f, 20.0f));
        shaderComum.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Transformação da calçada 1
        shaderComum.setInt("textura", 1);
        model = glm::mat4(1.0f);
        model = Transformacoes::translacao(model, glm::vec3(5.0f, -1.0f, 2.0f));
        model = Transformacoes::escala(model, glm::vec3(7.0f, 0.2f, 20.0f));
        shaderComum.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Transformação da calçada 2
        shaderComum.setInt("textura", 1);
        model = glm::mat4(1.0f);
        model = Transformacoes::translacao(model, glm::vec3(-5.0f, -1.0f, 2.0f));
        model = Transformacoes::escala(model, glm::vec3(7.0f, 0.2f, 20.0f));
        shaderComum.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Transformação do prédio
        shaderComum.setInt("textura", 2);
        model = glm::mat4(1.0f);
        model = Transformacoes::translacao(model, glm::vec3(5.0f, 1.0f, 2.0f));
        model = Transformacoes::escala(model, glm::vec3(3.0f, 7.0f, 3.0f));
        shaderComum.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Transformação da porta
        shaderComum.setInt("textura", 3);
        model = glm::mat4(1.0f);
        model = Transformacoes::translacao(model, glm::vec3(3.5f, 0.0f, 2.0f));
        model = Transformacoes::escala(model, glm::vec3(0.1f, 2.0f, 1.0f));
        model = Transformacoes::rotacaoY(model, 90.0);
        shaderComum.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Transformação das folhas 1
        shaderComum.setInt("textura", 4);
        model = glm::mat4(1.0f);
        model = Transformacoes::translacao(model, glm::vec3(3.5f, 2.0f, -2.0f));
        model = Transformacoes::escala(model, glm::vec3(1.0f, 1.0f, 1.0f));
        shaderComum.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Transformação das folhas 2
        shaderComum.setInt("textura", 4);
        model = glm::mat4(1.0f);
        model = Transformacoes::translacao(model, glm::vec3(3.5f, 2.0f, 6.0f));
        model = Transformacoes::escala(model, glm::vec3(1.0f, 1.0f, 1.0f));
        model = Transformacoes::rotacaoY(model, 45);
        shaderComum.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Transformação do tronco 1
        shaderComum.setInt("textura", 5);
        model = glm::mat4(1.0f);
        model = Transformacoes::translacao(model, glm::vec3(3.5f, -1.0f, -2.0f));
        model = Transformacoes::escala(model, glm::vec3(0.1f, 6.0f, 0.1f));
        model = Transformacoes::rotacaoY(model, 45);
        shaderComum.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Transformação do tronco 2
        shaderComum.setInt("textura", 5);
        model = glm::mat4(1.0f);
        model = Transformacoes::translacao(model, glm::vec3(3.5f, -1.0f, 6.0f));
        model = Transformacoes::escala(model, glm::vec3(0.1f, 6.0f, 0.1f));
        model = Transformacoes::rotacaoY(model, 45);
        shaderComum.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Transformação do poste
        shaderComum.setInt("textura", 0);
        model = glm::mat4(1.0f);
        model = Transformacoes::translacao(model, glm::vec3(-3.0f, 1.0f, movimento));
        model = Transformacoes::escala(model, glm::vec3(0.1f, 4.0f, 0.1f));
        shaderComum.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // Ativo o shader para objetos luminosos e mando propriedades para o fragment shader de objetos que não recebe luz (cubo branco)
        shaderCuboBranco.use();

        // Faço a mesma coisa e uso as mesmas propriedades de vertex shader de objetos normais
        glBindVertexArray(VAOCuboEmissorLuz);
        shaderCuboBranco.setMat4("projection", projection);
        shaderCuboBranco.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = Transformacoes::translacao(model, glm::vec3(-3.0f, 3.0f, movimento));
        model = Transformacoes::escala(model, glm::vec3(0.5f, 0.8f, 0.5f));
        model = Transformacoes::rotacaoX(model, rotacao);
        model = Transformacoes::rotacaoY(model, rotacao);
        model = Transformacoes::rotacaoZ(model, rotacao);
        shaderCuboBranco.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // Gerencia os eventos de tecla e mouse (interação) usando o OpenGL
        // ----------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        rotacao += 1.0f;
        if (rotacao == 360.0f){
            rotacao = 0.0f;
        }

        movimento += velocidadeMovimento; // Atualiza o movimento do poste
        // Se ele chega no limite, volta
        if (movimento > 10.0f || movimento < -7.0f) {
            velocidadeMovimento *= -1;
        }
    }

    // Dá um "free" nos VAOs e no VBO no término do programa
    // -----------------------------------------------------
    glDeleteVertexArrays(1, &VAOcuboNormal);
    glDeleteVertexArrays(1, &VAOCuboEmissorLuz);
    glDeleteBuffers(1, &VBO);
    glfwTerminate(); // Encerra o OpenGL

    return 0;
}