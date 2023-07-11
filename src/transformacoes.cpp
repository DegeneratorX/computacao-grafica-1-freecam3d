//
// Created by arida01 on 10/07/23.
//

#include "cg1/transformacoes.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

template<typename T>
T Transformacoes::transladarObjeto(float translacaoX, float translacaoY, float translacaoZ, const glm::mat4& acumulo) {
    return glm::mat4(
            1.0f, 1.0f, 0.0f, translacaoX,
            0.0f, 1.0f, 0.0f, translacaoY,
            0.0f, 0.0f, 1.0f, translacaoZ,
            0.0f, 0.0f, 0.0f, 1.0f
            ) * acumulo;
}

template<typename T>
T Transformacoes::redimensionarObjeto(float escalaX, float escalaY, float escalaZ, const glm::mat4& acumulo) {
    return glm::mat4(
            escalaX, 0.0f, 0.0f, 0.0f,
            0.0f, escalaY, 0.0f, 0.0f,
            0.0f, 0.0f, escalaZ, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    ) * acumulo;
}

template<typename T>
T Transformacoes::rotacionarObjetoX(float anguloX, const glm::mat4& acumulo) {
    auto PI = glm::pi<float>();
    return glm::mat4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, glm::cos(anguloX*PI/180.0f), -glm::sin(anguloX*PI/180.0f), 0.0f,
            0, glm::sin(anguloX*PI/180.0f), glm::cos(anguloX*PI/180.0f), 0,
            0, 0, 0, 1
    ) * acumulo;
}

template<typename T>
T Transformacoes::rotacionarObjetoY(float anguloY, const glm::mat4& acumulo) {
    auto PI = glm::pi<float>();
    return glm::mat4(
            glm::cos(anguloY*PI/180.0f), 0.0f, -glm::sin(anguloY*PI/180.0f), 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            glm::sin(anguloY*PI/180.0f), 0.0, glm::cos(anguloY*PI/180.0f), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    ) * acumulo;
}

template<typename T>
T Transformacoes::rotacionarObjetoZ(float anguloZ, const glm::mat4& acumulo) {
    auto PI = glm::pi<float>();
    return glm::mat4(
            glm::cos(anguloZ*PI/180.0f), -glm::sin(anguloZ*PI/180.0f), 0.0f, 0.0f,
            glm::sin(anguloZ*PI/180.0f), glm::cos(anguloZ*PI/180.0f), 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    ) * acumulo;
}