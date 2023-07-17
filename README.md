# Freecam 3D - Trabalho Final de Computação Gráfica

Feito por Victor Medeiros Martins - 401339, discente da Universidade Federal do Ceará.

Para compilar o programa, recomendo o uso de uma IDE (CLion ou Visual Studio) e do C++ versão 17. A linkagem dos arquivos é feita de forma automática pelo CMakeLists.txt.

Na pasta "includes" contém todos os arquivos de biblioteca própria ou de terceiros.

- cg1: são minhas bibliotecas, como shader, câmera e álgebra linear na mão;
- glad;
- glm: biblioteca comparada ao numpy, porém com muita afinidade com openGL;
- stbimage: carregamento de texturas.

O main.cpp está na pasta "src", e as texturas estão na pasta "resources".

IMPORTANTE: é necessário ter um cmake-build-debug (pasta na raíz) de acordo com seu SO, caso contrário o projeto não compila. A minha pasta foi gerada pela IDE CLion (Jetbrains) em um ubuntu.

# Projeto

O projeto Freecam 3D utiliza uma câmera para visualização em 3D com projeção em perspectiva.

- WASD para direções;
- Mouse para olhar ao redor;
- Scroll do mouse para aumentar ou diminuir o FOV (zoom).

A ideia do projeto é mostrar a iluminação Phong refletindo sobre diferentes objetos, texturas, mostrar transformações lineares de câmera, de objetos e até de luz. O cenário foi feito na mão utilizando apenas transformações de escala, rotação e translação.

