#ifndef COMPGRAFICA_FREECAM3D_TRANSFORMACOES_H
#define COMPGRAFICA_FREECAM3D_TRANSFORMACOES_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Transformacoes {
public:
    template<typename T>
    static T transladarObjeto(float translacaoX, float translacaoY, float translacaoZ, const glm::mat4& acumulo = glm::mat4(1.0f));
    template<typename T>
    static T redimensionarObjeto(float escalaX, float escalaY, float escalaZ, const glm::mat4& acumulo = glm::mat4(1.0f));
    template<typename T>
    static T rotacionarObjetoX(float anguloX, const glm::mat4& acumulo = glm::mat4(1.0f));
    template<typename T>
    static T rotacionarObjetoY(float anguloY, const glm::mat4& acumulo = glm::mat4(1.0f));
    template<typename T>
    static T rotacionarObjetoZ(float anguloZ, const glm::mat4& acumulo = glm::mat4(1.0f));
};




#endif //COMPGRAFICA_FREECAM3D_TRANSFORMACOES_H
