
#include "screen.h"
#include "timer.h"
#include "keyboard.h"
#include <stdlib.h>
#include <time.h>

#define WIDTH 10
#define HEIGHT 20
#define BLOCK_SIZE 2

// Definição das formas das peças com rotações possíveis
char tetrominos[7][4][4][4] = {
    { // I
        { {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0} },
        { {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0} }
    },
    { // O
        { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }
    },
    { // T
        { {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} }
    },
    { // S
        { {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} }
    },
    { // Z
        { {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0} }
    },
    { // L
        { {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} },
        { {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0} }
    },
    { // J
        { {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0} },
        { {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0} }
    }
};

int level = 1;  // Nível do jogo
int score = 0;  // Pontuação

// Estado do tabuleiro
int board[WIDTH][HEIGHT];

// Estrutura para representar uma peça
typedef struct {
    int x, y;
    int type;
    int rotation;
} Piece;

Piece currentPiece;

void exibirTelaInicial() {
    system("clear"); // Limpa o terminal (ajuste para "cls" se estiver no Windows)
    
    // Exibe o título
    printf("########################### #################################\n");
    printf("████████╗███████╗████████╗██████╗░██╗░███████╗\n ");
    printf("╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝\n ");
    printf("░░░██║░░░█████╗░░░░░██║░░░██████╔╝██║╚█████╗░\n ");
    printf("░░░██║░░░██╔══╝░░░░░██║░░░██╔══██╗██║░╚═══██╗\n ");
    printf("░░░██║░░░███████╗░░░██║░░░██║░░██║░░██║██║██║\n ");
    printf("░░░╚═╝░░░╚══════╝░░░╚═╝░░░╚═╝░░╚═╝╚═ ════╝░\n ");
    printf("######################################## #############\n");
    printf("\nPrepare-se para uma partida emocionante de TETRIS!\n");
    printf("Pressione ENTER...\n");

    // Aguarde o usuário iniciar
    getchar();
}

// Função para exibir as instruções do jogo
void exibirInstrucoes() {
    system("clear"); // Limpa o terminal para as instruções
    printf("############################################################\n");
    printf("#                                                          #\n");
    printf("#                   INSTRUÇÕES DO TETRIS                   #\n");
    printf("#                                                          #\n");
    printf("# Use as setas para mover as peças:                        #\n");
    printf("#  A: Mover para a Esquerda                                #\n");
    printf("#  D: Mover para a Direita                                 #\n");
    printf("#  W: Girar a peça                                         #\n");
    printf("#  S: Acelerar a queda da peça                             #\n");
    printf("#                                                          #\n");
    printf("############################################################\n");

    printf("\nPressione ENTER para começar...");
    getchar();
}


// Função que verifica se a peça colidiu
int checkCollision(Piece *piece) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[piece->type][piece->rotation][i][j]) {
                int x = piece->x + i;
                int y = piece->y + j;
                if (x < 0 || x >= WIDTH || y >= HEIGHT || board[x][y]) {
                    return 1;  // Colidiu com a borda ou outra peça
                }
            }
        }
    }
    return 0;  // Não houve colisão
}

// Função que coloca a peça no tabuleiro
void placePiece(Piece *piece) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[piece->type][piece->rotation][i][j]) {
                board[piece->x + i][piece->y + j] = 1;  // Marca o tabuleiro com a peça
            }
        }
    }
}

// Função que rotaciona a peça
void rotatePiece() {
    int oldRotation = currentPiece.rotation;
    currentPiece.rotation = (currentPiece.rotation + 1) % 4;  // Rotaciona para a próxima posição
    if (checkCollision(&currentPiece)) {
        currentPiece.rotation = oldRotation;  // Se houver colisão, volta para a rotação anterior
    }
}

// Função que move a peça na horizontal
void movePiece(int dx) {
    currentPiece.x += dx;  // Desloca a peça para a esquerda (dx=-1) ou para a direita (dx=1)
    if (checkCollision(&currentPiece)) {
        currentPiece.x -= dx;  // Se houver colisão, desfaz o movimento
    }
}

// Função que desenha a peça na tela
void drawPiece(Piece *piece) {
    screenSetColor(RED, BLACK);  // Define a cor para desenhar a peça
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[piece->type][piece->rotation][i][j]) {  // Verifica se a célula da peça está ativa
                screenGotoxy(SCRSTARTX + (piece->x + i) * BLOCK_SIZE, SCRSTARTY + piece->y + j);  // Calcula a posição na tela
                printf("[]");  // Desenha o bloco da peça
            }
        }
    }
}


void drawBoard() {
    screenClear();
    screenSetColor(CYAN, BLACK);
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (board[i][j]) {
                screenGotoxy(SCRSTARTX + i * BLOCK_SIZE, SCRSTARTY + j);
                printf("[]");
            }
        }
    }
    // Exibe o nível e a pontuação
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 2, SCRSTARTY);
    printf("Nível: %d", level);
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 2, SCRSTARTY + 1);
    printf("Pontuação: %d", score);
}

void removeFullLines() {
    // Função que remove linhas completas
    for (int j = 0; j < HEIGHT; j++) {
        int full = 1;
        for (int i = 0; i < WIDTH; i++) {
            if (!board[i][j]) {
                full = 0;
                break;
            }
        }
        if (full) {
            for (int k = j; k > 0; k--) {
                for (int i = 0; i < WIDTH; i++) {
                    board[i][k] = board[i][k - 1];
                }
            }
            for (int i = 0; i < WIDTH; i++) {
                board[i][0] = 0;
            }
            score += 100; // Adiciona 100 pontos por linha completa
        }
    }
}

void spawnPiece() {
    currentPiece.x = WIDTH / 2 - 2;
    currentPiece.y = 0;
    currentPiece.type = rand() % 7;
    currentPiece.rotation = 0;
    if (checkCollision(&currentPiece)) {
        screenDestroy();
        printf("Game Over\n");
        exit(0);
    }
}

void dropPiece() {
    currentPiece.y++;
    if (checkCollision(&currentPiece)) {
        currentPiece.y--;
        placePiece(&currentPiece);
        removeFullLines();
        spawnPiece();
    }
}

void processInput() {
    if (keyhit()) {
        int key = readch();
        switch (key) {
            case 'a': movePiece(-1); break;
            case 'd': movePiece(1); break;
            case 's': dropPiece(); break;
            case 'w': rotatePiece(); break;
        }
    }
}

int main() {
    exibirTelaInicial();
    exibirInstrucoes();
    srand(time(NULL));
    screenInit(1);
    keyboardInit();
    timerInit(500);

    spawnPiece();

    while (1) {
        processInput();
        if (timerTimeOver()) {
            dropPiece();
        }
        drawBoard();
        drawPiece(&currentPiece);
        screenUpdate();
    }

    screenDestroy();
    keyboardDestroy();
    return 0;
}
