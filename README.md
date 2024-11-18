<p align="center">
  <img
    src="https://img.shields.io/badge/Status-Em%20desenvolvimento-green?style=flat-square"
    alt="Status"
  />
</p>

<p align="center">
  <img
    src="https://img.shields.io/github/repo-size/Sofia-Saraiva/Semester3-CESAR-School?style=flat"
    alt="Repository Size"
  />
  <img
    src="https://img.shields.io/github/languages/count/Sofia-Saraiva/Semester3-CESAR-School?style=flat&logo=python"
    alt="Language Count"
  />
  <img
    src="https://img.shields.io/github/commit-activity/t/Sofia-Saraiva/Semester3-CESAR-School?style=flat&logo=github"
    alt="Commit Activity"
  />
  <a href="LICENSE.md"
    ><img
      src="https://img.shields.io/github/license/Sofia-Saraiva/Semester3-CESAR-School"
      alt="License"
  /></a>
</p>

Bem-vindo ao Blocky, uma recriação do clássico jogo de Tetris para ser jogado diretamente no terminal! Este projeto foi desenvolvido em C e utiliza uma biblioteca em C [Acesse Aqui](https://github.com/tgfb/cli-lib/) para criar uma experiência divertida e nostálgica.

## 🖥️  Blocky
Blocky é uma adaptação do clássico jogo Tetris. Trata-se de um jogo de puzzle onde peças de diferentes formatos, chamadas "tetrominós", caem de cima para baixo em um campo de jogo. O objetivo é posicioná-las de maneira a formar linhas horizontais completas, que desaparecem, evitando que as peças se acumulem até o topo. O desafio está em pensar rápido e organizar as peças estrategicamente.

## 🎲 Objetivo do Jogo
O objetivo do jogo é é encaixar peças que caem na tela (Tetrominos) para formar linhas horizontais completas no tabuleiro. Quando uma linha é completada, ela é removida, o jogador ganha pontos e as linhas acima da removida descem para ocupar o espaço. O jogo termina quando as peças se acumulam até o topo do tabuleiro. O jogador pode: mover as peças para os lados, girar as peças e acelerar a queda para posicioná-las mais rápido. O objetivo é obter a maior pontuação possível antes que o jogo termine, removendo o máximo de linhas consecutivas e evitando que o tabuleiro fique lotado.

## 📄 Principais Funções
1. **Definições Básicas:**
   - O tabuleiro do jogo tem largura de 10 e altura de 20.
   - As peças (tetrominos) são representadas em matrizes tridimensionais, incluindo suas rotações possíveis.

2. **Funções do Jogo:**
   - **Exibição:** Funções como `exibirTelaInicial`, `exibirInstrucoes` e `drawBoard` são responsáveis por exibir a interface do jogo no terminal, incluindo o tabuleiro e informações como nível e pontuação.
   - **Controle de Peças:** Funções como `spawnPiece`, `rotatePiece`, `movePiece` e `drawPiece` lidam com a geração, movimentação, rotação e desenho das peças no tabuleiro.
   - **Manipulação do Tabuleiro:** Funções como `checkCollision`, `placePiece` e `removeFullLines` verificam colisões, posicionam peças e removem linhas completas, respectivamente.

3. **Ranking:**
   - Estruturas e funções para salvar e carregar rankings, armazenando o nome e a pontuação dos jogadores.

4. **Controle de Fluxo:**
   - O jogo utiliza funções como `processInput` para interpretar comandos do jogador e ajustar o estado do jogo (movimento, rotação ou queda da peça).

5. **Características Extras:**
   - Exibição de bordas decorativas ao redor do jogo.
   - Título animado e instruções exibidas no início.
   - Sistema de pontuação e níveis.

Este código segue uma estrutura modular, separando funções por responsabilidade, o que facilita o entendimento e a manutenção. Ele usa bibliotecas externas (`screen.h`, `timer.h`, `keyboard.h`) para lidar com funcionalidades específicas como gráficos no terminal, entrada de teclado e temporização.

## 🎮 Funcionalidades
**Tela Inicial e Personalização:**
Personalize sua experiência iniciando com a inserção do seu nome na tela inicial.

**Instruções do Jogo:**
Uma seção dedicada às instruções para que você nunca fique perdido.

**Jogabilidade:**

Mova as peças para a esquerda, direita ou acelere sua queda.
Gire as peças para encaixá-las da melhor maneira possível.
Acelere sua pontuação removendo linhas completas.
Ranking de Jogadores:
Registre suas pontuações e veja como você se compara com outros jogadores.

**Interface com Bordas Dinâmicas:**
Desenho automático das bordas delimitando a área de jogo.


## 🕹️ Como Jogar
**Teclas de Controle:**

- A: Mover para a esquerda
- D: Mover para a direita
- W: Girar a peça
- S: Acelerar a queda da peça
  
**Dicas:**
- Pratique o controle de peças para melhorar sua habilidade em encaixar as peças de forma eficiente.
- Use a rotação de peças para adaptar as formas às linhas disponíveis no tabuleiro.

## 🛠️ Estrutura do Código
Principais Arquivos e Funções
**main.c:**
Contém a lógica principal do jogo, incluindo movimentação, colisão, e renderização.

**Lista e Descrição das Funções:**

1. `screenDrawBorders` 
   - Desenha as bordas do jogo na tela para delimitar o espaço onde as peças cairão.
   - Utiliza `screenGotoxy` para posicionamento no terminal e elementos como `===` e `|||`.
2. `exibirTelaInicial`  
   - Exibe uma tela inicial com o título ASCII do jogo e solicita o nome do jogador.
   - Mostra uma mensagem de boas-vindas e aguarda que o jogador pressione `ENTER`.
3. `exibirInstrucoes`  
   - Exibe as instruções do jogo, incluindo os controles para mover e girar as peças.
   - Utiliza bordas e centralização para melhorar a apresentação.
4. `checkCollision`
   - Verifica colisões entre a peça atual e o tabuleiro ou as bordas.  
   - Retorna 1 se houver colisão e 0 caso contrário.



## ♟️ Executando o Jogo
**1. Configuração do Ambiente:**
   - No Windows: 
     - Instale um ambiente compatível com Linux, como:
       - Uma máquina virtual Linux utilizando VirtualBox ou Multipass.
       - WSL (Windows Subsystem for Linux), que permite executar um terminal Linux diretamente no Windows.
   - No Linux ou macOS: Utilize o terminal nativo, pois essas plataformas já são compatíveis.

**2. Instalação do GCC:**
   - Certifique-se de que o GCC (GNU Compiler Collection) está instalado no dispositivo. Caso contrário, instale-o utilizando o gerenciador de pacotes apropriado: Ubuntu/Debian; Fedora; macOS:  Xcode Command 
     Line Tools

**3. Clonagem do Repositório:**
   - Baixar o código do jogo diretamente do repositório GitHub. No terminal, executar:
     git clone <URL_DO_REPOSITORIO>
     Substitua <URL_DO_REPOSITORIO> pelo link fornecido para o projeto no GitHub.

**4. Compilação do Código:***
    - Navegue até a pasta onde o repositório foi clonado:
       cd <NOME_DO_REPOSITORIO>
    - Compile o jogo utilizando o GCC. Caso os arquivos estejam organizados em uma estrutura típica com   subpastas `src` e `include`, utilize o seguinte comando:
     `gcc ./src/*.c -I./include -o exemplo`
    - `./src/*.c`: Compila todos os arquivos `.c` na pasta `src`.
    - `-I./include`: Inclui cabeçalhos na pasta `include`.
    - `-o exemplo`: Define o nome do executável como `exemplo`.

**5. Execução do Jogo:**
    - Após a compilação, execute o jogo com o comando:
       ./exemplo

Divirta-se!

## 👩‍💻 Membros & Perfis do GitHub

<ul>
  <li>
    <a href="https://github.com/fabianacoelhoo">Fabiana Coelho </a> -
    fcsls@cesar.school 📩
  </li>
  <li>
    <a href="https://github.com/juliamariateixeiraa">Julia Maria Teixeira </a> -
    jmst@cesar.school 📩
  </li>
  <li>
    <a href="https://github.com/lavasilva">Lavínia Maranhão </a> -
    lmfs@cesar.school 📩
  </li>
</ul>

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/fabianacoelhoo">
        <img src="https://github.com/user-attachments/assets/51c785aa-16b1-4489-8498-9760850f64f7" width="100px;" alt="Foto de Fabiana"/><br>
        <sub>
          <b> Fabiana Coelho </b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/juliamariateixeiraa">
        <img src="https://github.com/user-attachments/assets/39749d5b-f523-4822-b0df-79a3915e4667" width="100px;" alt="Foto de Julia"/><br>
        <sub>
          <b>Julia Maria Teixeira</b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/lavasilva">
        <img src="https://github.com/user-attachments/assets/7167573c-3fbf-4b36-b6e5-e3aad1548397" width="100px;" alt="Foto de Lavínia"/><br>
        <sub>
          <b>Lavínia Maranhão</b>
        </sub>
      </a>
    </td>
  </tr>
</table>

## Licença

...

## ⚾👾⚡️🕹️♟️🎲
