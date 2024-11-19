<p align="center">
  <img
    src="https://img.shields.io/badge/Status-Finalizado!%20-green?style=flat-square"
    alt="Status"
  />
</p>

## 🖥️  Blocky
Bem vindo! Blocky é uma adaptação do clássico jogo Tetris. Trata-se de um jogo de puzzle onde peças de diferentes formatos, chamadas "tetrominós", caem de cima para baixo em um campo de jogo. O objetivo é posicioná-las de maneira a formar linhas horizontais completas, que desaparecem, evitando que as peças se acumulem até o topo. O desafio está em pensar rápido e organizar as peças estrategicamente.

## 🎲 Objetivo do Jogo
O objetivo do jogo é é encaixar peças que caem na tela (tetrominós) para formar linhas horizontais completas no tabuleiro. Quando uma linha é completada, ela é removida, o jogador ganha pontos e as linhas acima da removida descem para ocupar o espaço. O jogo termina quando as peças se acumulam até o topo do tabuleiro. O jogador pode: mover as peças para os lados, girar as peças e acelerar a queda para posicioná-las mais rápido. O objetivo é obter a maior pontuação possível antes que o jogo termine, removendo o máximo de linhas consecutivas e evitando que o tabuleiro fique lotado.

## ♟️ Executando o Jogo
**1. Configuração do Ambiente:**
   - No Windows: 
     - Instale um ambiente compatível com Linux, como:
       - Uma máquina virtual Linux utilizando VirtualBox ou Multipass.
       - WSL (Windows Subsystem for Linux), que permite executar um terminal Linux diretamente no Windows.
   - No Linux ou macOS: Utilize o terminal nativo, pois essas plataformas já são compatíveis!

**2. Instalação do GCC:**
   - Certifique-se de que o GCC (GNU Compiler Collection) está instalado no dispositivo. Caso contrário, instale-o utilizando o gerenciador de pacotes apropriado: Ubuntu/Debian; Fedora; macOS:  Xcode Command 

**3. Clonagem do Repositório:**
   - Baixar o código do jogo diretamente do repositório GitHub. No terminal, executar:
     `git clone https://github.com/lavasilva/Blocky`

**4. Compilação e Execução do Código:***
    - Navegue até a pasta onde o repositório foi clonado:
       `cd Blocky`<br>
    - Compile o jogo utilizando o GCC. Utilize o seguinte comando:
     `gcc ./src/*.c -I./include -o jogo`<br>
    - Após a compilação, execute o jogo com o comando:
       `./jogo`<br>
    - Divirta-se!

## 🕹️ Como Jogar
**Teclas de Controle:**

No modo clássico:
- A: Mover para a esquerda
- D: Mover para a direita
- W: Girar a peça
- S: Acelerar a queda da peça

No modo desafio:
- A: Mover para a direita
- D: Mover para a esquerda
- W: Girar a peça no sentido anti-horário
- S: Acelerar a queda da peça 3x

## 📄 Principais Funções
1. **Definições Básicas:**
   - O tabuleiro do jogo tem largura de 10 e altura de 20.
   - As peças (tetrominós) são representadas em matrizes tridimensionais, incluindo suas rotações possíveis.

2. **Funções do Jogo:**
   - **Exibição:** Funções como `exibirTelaInicial`, `exibirInstrucoes` e `desenhaTabuleiro` são responsáveis por exibir a interface do jogo no terminal, incluindo o tabuleiro e informações como nível e pontuação.
   - **Controle de Peças:** Funções como `gerarPeca`, `rotacionaPeca`, `movePeca` e `desenhaPeca` lidam com a geração, movimentação, rotação e desenho das peças no tabuleiro.
   - **Manipulação do Tabuleiro:** Funções como `checkColisao`, `colocaPeca` e `removeLinhaCompleta` verificam colisões, posicionam peças e removem linhas completas, respectivamente.

3. **Ranking:**
   - Lista encadeada para ordenar pontuações/jogadores e escrevê-las em um arquivo "ranking.txt".

4. **Controle de Fluxo:**
   - O jogo utiliza funções como `processaInput` para interpretar comandos do jogador e ajustar o estado do jogo (movimento, rotação ou queda da peça).

Este código usa bibliotecas externas (`screen.h`, `timer.h`, `keyboard.h`) para lidar com funcionalidades específicas como gráficos no terminal, entrada de teclado e temporização.

## 🎮 Funcionalidades
**Tela Inicial e Personalização:**
Personalize sua experiência iniciando com a inserção do seu nome na tela inicial.

**Instruções do Jogo:**
Uma seção dedicada às instruções para que você nunca fique perdido.

**Funcionalidade Extra: Modo Desafio** <br>
Prepare-se para uma experiência intensa e diferenciada!<br>
- Ao começar o jogo e selecionar o modo desafio, o jogo inicia um modo invertido!
        -       Neste modo, os controles são invertidos!                            
                 A: Mover para a Direita                                            
                 D: Mover para a Esquerda      
                 S: Desce duas vezes mais rápido do que o jogo clássico   


## 😅 Dificuldades Encontradas

**1. Sincronização entre Frames:**
Ajusta o tempo de queda das peças para níveis progressivos que foram solicitados.<br>
**2. Colisões Rotacionais :**
Garantir que as peças não ultrapassem os limites durante rotações realizadas várias verificações.<br>
**3. Centralização de Conteúdo :**
Manter o título e mensagens centralizados, independentemente do tamanho da janela.<br>
**5. Rotação de Peças:**
Implementar a rotação das peças de forma consistente e chacando colisões foi desafiador, especialmente para peças próximas às bordas.<br>
**6. Persistência do Ranking:**
Manipular listas e arquivos para salvar e carregar dados exigiu cuidados com formatação e ordenação para garantir a integridade do ranking.<br>


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


