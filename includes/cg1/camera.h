#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

// Movimentações de câmera
#define FORWARD 0
#define BACKWARD 1
#define LEFT 2
#define RIGHT 3

// Propriedades da câmera. yawCamera e pitchCamera são propriedades dos ângulos de Euler (rotação horizontal e vertical)
const float TILT             = -90.0f;
const float PITCH            =  0.0f;
const float VELOCIDADE       =  2.5f;
const float SENSIBILIDADE    =  0.1f;
const float FOV              =  65.0f;



class Camera{
public:
    glm::vec3 frenteCamera;
    glm::vec3 cimaCamera;
    glm::vec3 direitaCamera;
    glm::vec3 cimaMundo;

    glm::vec3 posicaoCamera;

    float yawCamera;
    float pitchCamera;
    float velocidadeCamera;
    float sensibilidadeMouse;
    float fovCamera;

    // Construtor da câmera
    // --------------------
    Camera(glm::vec3 posicaoCamera = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 cimaMundo = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = TILT, float pitch = PITCH) : frenteCamera(glm::vec3(0.0f, 0.0f, -1.0f)), velocidadeCamera(VELOCIDADE), sensibilidadeMouse(SENSIBILIDADE), fovCamera(FOV){
        this->posicaoCamera = posicaoCamera;
        this->cimaMundo = cimaMundo;
        atualizarCamera();
    }

    // Transformação linear de câmera usando teclado (translação apenas)
    // -----------------------------------------------------------------
    void movimentacaoTeclado(int direcao, float deltaFrame){
        float velocidade = velocidadeCamera * deltaFrame;
        if (direcao == FORWARD)
            posicaoCamera += frenteCamera * velocidade;
        if (direcao == BACKWARD)
            posicaoCamera -= frenteCamera * velocidade;
        if (direcao == LEFT)
            posicaoCamera -= direitaCamera * velocidade;
        if (direcao == RIGHT)
            posicaoCamera += direitaCamera * velocidade;
    }

    // Transformação linear de câmera usando mouse (rotação, campo de visão)
    // ---------------------------------------------------------------------
    void movimentacaoMouse(float deslocamentoX, float deslocamentoY, GLboolean limiteDoPitch = true){
        deslocamentoX *= sensibilidadeMouse;
        deslocamentoY *= sensibilidadeMouse;

        yawCamera   += deslocamentoX;
        pitchCamera += deslocamentoY;
        // Evita que a câmera fique de cabeça pra baixo
        if (limiteDoPitch){
            if (pitchCamera > 89.0f){
                pitchCamera = 89.0f;
            }
            if (pitchCamera < -89.0f){
                pitchCamera = -89.0f;
            }
        }
        // Atualiza os vetores frenteCamera, direitaCamera e cimaCamera.
        atualizarCamera();
    }

    // Aumenta ou diminui o campo de visão (FOV)
    // -----------------------------------------
    void campoDeVisao(float yoffset){
        fovCamera -= (float)yoffset;
        if (fovCamera < 1.0f)
            fovCamera = 1.0f; // Limite para o fov
        if (fovCamera > 65.0f)
            fovCamera = 65.0f;
    }

    // Retorna o lootAt da câmera
    // --------------------------
    glm::mat4 GetViewMatrix(){
        return lookAt(posicaoCamera, posicaoCamera + frenteCamera, cimaCamera);
    }

private:
    void atualizarCamera(){
        // Calcula o novo vetor z da câmera
        glm::vec3 frente;
        frente.x = cos(glm::radians(yawCamera)) * cos(glm::radians(pitchCamera));
        frente.y = sin(glm::radians(pitchCamera));
        frente.z = sin(glm::radians(yawCamera)) * cos(glm::radians(pitchCamera));

        frenteCamera = glm::normalize(frente);

        // Calcula os vetores do lado direito e cima da câmera
        direitaCamera = glm::normalize(glm::cross(frenteCamera, cimaMundo));
        cimaCamera    = glm::normalize(glm::cross(direitaCamera, frenteCamera));
    }

    glm::mat4 lookAt(const glm::vec3& posicaoCamera, const glm::vec3& target, const glm::vec3& cimaCamera) {
        glm::vec3 direcaoDaCamera = glm::normalize(posicaoCamera - target);
        glm::vec3 direitaCameraAux = glm::normalize(glm::cross(cimaCamera, direcaoDaCamera)); // Produto vetorial, regra da mão direita
        glm::vec3 cimaCameraAux = glm::cross(direcaoDaCamera, direitaCameraAux);

        glm::mat4 view(1.0f);
        view[0][0] = direitaCameraAux.x;
        view[1][0] = direitaCameraAux.y;
        view[2][0] = direitaCameraAux.z;
        view[0][1] = cimaCameraAux.x;
        view[1][1] = cimaCameraAux.y;
        view[2][1] = cimaCameraAux.z;
        view[0][2] = direcaoDaCamera.x;
        view[1][2] = direcaoDaCamera.y;
        view[2][2] = direcaoDaCamera.z;
        view[3][0] = -glm::dot(direitaCameraAux, posicaoCamera);
        view[3][1] = -glm::dot(cimaCameraAux, posicaoCamera);
        view[3][2] = -glm::dot(direcaoDaCamera, posicaoCamera);

        return view;
    }
};

#endif
