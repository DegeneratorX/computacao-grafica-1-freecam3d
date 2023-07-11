https://vimeo.com/842318468/8fd617e7b2

# Desenvolvimento de Jogos: Desafios e Perspectivas na Criação de Personagens Inteligentes

Essa palestra foi ministrada pelo discente Matheus, aluno de doutourado pela Universidade Federal do Ceará, no dia 4 de julho de 2023, as 18:00. Esses são os principais tópicos de sua palestra.

# Jogo - do que eles são feitos?

### Planejamento básico

Qualquer jogo básico hoje precisa de um roteiro, áudio, design, modelagem 2D/3D e lógica de programação. Sem esses pilares, é difícil atender a demanda do mercado de jogos modernos hoje em dia. Porém existem casos raros de jogos sem roteiro que deram certo. É o caso do Minecraft, que não possui um objetivo concreto, e cabe ao jogador criar seu próprio roteiro, ou o BeamNG Drive, que é um simulador de batidas de carro.

### Planejamento avançado

Para produções em larga escala de jogos, é necessário seguir tópicos mais avançados de planejamento, e por isso irei separar eles aqui:

- Pré-Produção
    - Ideia
        - Trata-se de uma ideia inicial para a elaboração de um jogo.
    - Análise de Requisitos e Pré-Venda
    - Game Concept
        - Seria um esborço inicial do jogo


Atualmente existe um desafio que precisaremos enfrentar: como usar a inteligência artificial crescente a nosso favor, de forma que possamos aumentar a interação e a imersão nos games?



# NPCs

## Anatomia

- TODO

# Agente racional

Age em um ambiente, maximizando sua medida de desempenho para atingir o objetivo.

## 

Técnicas utilizadas:
- Máquinas de estado finito
- Redes neurais artificiais
- Árvores de decisão
- Lógica Fuzzy (lógica incerta, não é binária. Ou seja, 0.7 sim e 0.3 não, por exemplo).

## NPCs com Plano e Mapa

Solução: dotar NPC de mapas e calcular caminhos mínimos ou buscas em grafos. Sim, NPCs podem ter uma representação de um mapa programado para si, e nesse mapa "próprio" possui grafos.

## NPCs com Controlador Neural

Solução coum: dotar NPC de uma rede neural que recebe o estado na entrada e classifica a melhor ação.

Se o NPC fizer um estado certo, a gente recompensa ele. Por exemplo, no Mario, tem um bloco na frente. Se o npc mario (controlado por uma rede neural) pular, então ele ganha uma recompensa.

## Neuroevolução

Diversidade evolutiva: surgimento dos olhos uma nova dinâmica entre predadores e presas

Cortéx Visual Artificial: forte conexão entre a mente e o ambiente ao redor

Visão do agente é uma câmera virtual

Entradas são visuais e de alta dimensão

### XAI

Inteligência Artificial Explicativa.

É quando a decisão tomada não é direta. Por exemplo, se tem a foto de um gato, a IA normalmente diz: é um gato. Mas A IA explicativa diz:
- É um gato
    - Pois na foto tem orelhas únicas pontudas
    - Tem garras

A IA explicativa observa detalhes únicos que dão mais probabilidade de conclusão. Só olhando pro corpo é inconclusivo.