#ifndef COMPGRAFICA_FREECAM3D_TRANSFORMACOES_H
#define COMPGRAFICA_FREECAM3D_TRANSFORMACOES_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/**
 * Classe para transformações lineares diversas
 */
class Transformacoes {
public:
    // Transformação linear de translação
    // ----------------------------------
    static glm::mat4 translacao(const glm::mat4& model, const glm::vec3& vetorTranslacao)
    {
        glm::mat4 matrizTranslacao(1.0f); // Identidade
        matrizTranslacao[3] = glm::vec4(vetorTranslacao, 1.0f); // Quarta coluna

        glm::mat4 resultado = model * matrizTranslacao;
        return resultado;
    }

    // Transformação linear de escala
    // ------------------------------
    static glm::mat4 escala(const glm::mat4& model, const glm::vec3& vetorEscala){
        glm::mat4 matrizEscala(1.0f);
        matrizEscala[0][0] = vetorEscala.x;
        matrizEscala[1][1] = vetorEscala.y;
        matrizEscala[2][2] = vetorEscala.z;

        glm::mat4 resultado = model * matrizEscala;
        return resultado;
    }

    // Transformação linear de rotação em torno do eixo X
    // --------------------------------------------------
    static glm::mat4 rotacaoX(const glm::mat4& model, float anguloX){
        auto PI = glm::pi<float>();
        glm::mat4 matrizRotacaoX = glm::mat4(
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, glm::cos(anguloX*PI/180.0f), -glm::sin(anguloX*PI/180.0f), 0.0f,
                0, glm::sin(anguloX*PI/180.0f), glm::cos(anguloX*PI/180.0f), 0,
                0, 0, 0, 1
        );

        glm::mat4 resultado = model * matrizRotacaoX;
        return resultado;
    }

    // Transformação linear de rotação em torno do eixo Y
    // --------------------------------------------------
    static glm::mat4 rotacaoY(const glm::mat4& model, float anguloY){
        auto PI = glm::pi<float>();
        glm::mat4 matrizRotacaoY = glm::mat4(
                glm::cos(anguloY*PI/180.0f), 0.0f, -glm::sin(anguloY*PI/180.0f), 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                glm::sin(anguloY*PI/180.0f), 0.0, glm::cos(anguloY*PI/180.0f), 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        );

        glm::mat4 resultado = model * matrizRotacaoY;
        return resultado;
    }

    // Transformação linear de rotação em torno do eixo Z
    // --------------------------------------------------
    static glm::mat4 rotacaoZ(const glm::mat4& model, float anguloZ){
        auto PI = glm::pi<float>();
        glm::mat4 matrizRotacaoZ = glm::mat4(
                glm::cos(anguloZ*PI/180.0f), -glm::sin(anguloZ*PI/180.0f), 0.0f, 0.0f,
                glm::sin(anguloZ*PI/180.0f), glm::cos(anguloZ*PI/180.0f), 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        );

        glm::mat4 resultado = model * matrizRotacaoZ;
        return resultado;
    }
};

#endif //COMPGRAFICA_FREECAM3D_TRANSFORMACOES_H
