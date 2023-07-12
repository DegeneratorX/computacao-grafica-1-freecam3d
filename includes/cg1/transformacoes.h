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
    template<typename T>
    static T transladarObjeto(float translacaoX, float translacaoY, float translacaoZ, const glm::mat4& acumulo = glm::mat4(1.0f)) {
        return glm::mat4(
                1.0f, 1.0f, 0.0f, translacaoX,
                0.0f, 1.0f, 0.0f, translacaoY,
                0.0f, 0.0f, 1.0f, translacaoZ,
                0.0f, 0.0f, 0.0f, 1.0f
        ) * acumulo;
    }

    template<typename T>
    static T redimensionarObjeto(float escalaX, float escalaY, float escalaZ, const glm::mat4& acumulo) {
        return glm::mat4(
                escalaX, 0.0f, 0.0f, 0.0f,
                0.0f, escalaY, 0.0f, 0.0f,
                0.0f, 0.0f, escalaZ, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        ) * acumulo;
    }

    template<typename T>
    static T rotacionarObjetoX(float anguloX, const glm::mat4& acumulo) {
        auto PI = glm::pi<float>();
        return glm::mat4(
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, glm::cos(anguloX*PI/180.0f), -glm::sin(anguloX*PI/180.0f), 0.0f,
                0, glm::sin(anguloX*PI/180.0f), glm::cos(anguloX*PI/180.0f), 0,
                0, 0, 0, 1
        ) * acumulo;
    }

    template<typename T>
    static T rotacionarObjetoY(float anguloY, const glm::mat4& acumulo) {
        auto PI = glm::pi<float>();
        return glm::mat4(
                glm::cos(anguloY*PI/180.0f), 0.0f, -glm::sin(anguloY*PI/180.0f), 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                glm::sin(anguloY*PI/180.0f), 0.0, glm::cos(anguloY*PI/180.0f), 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        ) * acumulo;
    }

    template<typename T>
    static T rotacionarObjetoZ(float anguloZ, const glm::mat4& acumulo) {
        auto PI = glm::pi<float>();
        return glm::mat4(
                glm::cos(anguloZ*PI/180.0f), -glm::sin(anguloZ*PI/180.0f), 0.0f, 0.0f,
                glm::sin(anguloZ*PI/180.0f), glm::cos(anguloZ*PI/180.0f), 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        ) * acumulo;
    }
};




#endif //COMPGRAFICA_FREECAM3D_TRANSFORMACOES_H
