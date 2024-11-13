#include "screen.h"
#include "timer.h"
#include "keyboard.h"
#include <stdlib.h>
#include <time.h>

#define WIDTH 10
#define HEIGHT 20
#define BLOCK_SIZE 2
#define SCRSTARTX 5
#define SCRSTARTY 5
#define MAXX 80
#define MAXY 25

void screenDrawBorders();
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
    
    // Chama a função para desenhar as bordas
    screenDrawBorders();

    // Centralizar o título ASCII
    int titulo_linhas = 6;  // O título tem 6 linhas
    int titulo_comprimento = 50;  // Comprimento médio do título (ajuste conforme necessário)
    int start_x = (MAXX - titulo_comprimento) / 2;  // Calcula a posição de início para centralizar

    // Exibe o título ASCII centralizado
    screenGotoxy(start_x, 5);  // Posição de início para o título (ajuste a linha se necessário)
    printf("████████╗███████╗████████╗██████╗░██╗░███████╗\n");
    screenGotoxy(start_x, 6);
    printf("╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝\n");
    screenGotoxy(start_x, 7);
    printf("░░░██║░░░█████╗░░░░░██║░░░██████╔╝██║╚█████╗░\n");
    screenGotoxy(start_x, 8);
    printf("░░░██║░░░██╔══╝░░░░░██║░░░██╔══██╗██║░╚═══██╗\n");
    screenGotoxy(start_x, 9);
    printf("░░░██║░░░███████╗░░░██║░░░██║░░██║██║██████╔╝\n");
    screenGotoxy(start_x, 10);
    printf("░░░╚═╝░░░╚══════╝░░░╚═╝░░░╚═╝░░╚═╝╚═════╝░░\n");

    // Define a cor do texto e aguarda o usuário pressionar uma tecla
    screenSetColor(WHITE, BLACK);
    printf("\nPressione qualquer tecla para começar...\n");
    getchar();  // Aguarda uma tecla ser pressionada
    system("clear");
}

void screenDrawBorders() {
    screenSetColor(WHITE, BLACK);

    // Desenha a borda superior
    for (int i = 0; i < WIDTH + 2; i++) {
        screenGotoxy(SCRSTARTX + i * BLOCK_SIZE, SCRSTARTY - 1);
        printf("[]");
    }

    // Desenha a borda inferior
    for (int i = 0; i < WIDTH + 2; i++) {
        screenGotoxy(SCRSTARTX + i * BLOCK_SIZE, SCRSTARTY + HEIGHT);
        printf("[]");
    }

    // Desenha as bordas laterais
    for (int j = 0; j < HEIGHT; j++) {
        screenGotoxy(SCRSTARTX - 1, SCRSTARTY + j);
        printf("[]");
        screenGotoxy(SCRSTARTX + (WIDTH + 1) * BLOCK_SIZE, SCRSTARTY + j);
        printf("[]");
    }
}

void drawBoard() {
    screenClear();
    screenSetColor(CYAN, BLACK);

    // Desenha o tabuleiro dentro da borda
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (board[i][j]) {
                // Ajusta a posição das peças dentro da área do tabuleiro
                screenGotoxy(SCRSTARTX + (i + 1) * BLOCK_SIZE, SCRSTARTY + (j + 1));  
                printf("[]");
            }
        }
    }

    // Exibe o nível e a pontuação
    screenGotoxy(SCRSTARTX + (WIDTH + 1) * BLOCK_SIZE + 2, SCRSTARTY + 1);
    printf("Nível: %d", level);
    screenGotoxy(SCRSTARTX + (WIDTH + 1) * BLOCK_SIZE + 2, SCRSTARTY + 2);
    printf("Pontuação: %d", score);
}

void drawPiece(Piece *piece) {
    screenSetColor(RED, BLACK);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[piece->type][piece->rotation][i][j]) {  // Verifica se a célula da peça está ativa
                screenGotoxy(SCRSTARTX + (piece->x + i + 1) * BLOCK_SIZE, SCRSTARTY + piece->y + j + 1);  
                printf("[]");
            }
        }
    }
}

int main() {
    exibirTelaInicial();  // Exibe a tela inicial com bordas e título
    srand(time(NULL));    // Semente para geração aleatória
    screenInit(1);        // Inicializa a tela
    keyboardInit();       // Inicializa o teclado
    timerInit(500);       // Inicializa o timer com intervalo de 500 ms

    spawnPiece();         // Gera uma peça inicial

    while (1) {
        processInput();    // Processa a entrada do usuário (movimentação das peças)

        if (timerTimeOver()) {  // Se o tempo do timer acabou, a peça cai
            dropPiece();
        }

        drawBoard();        // Desenha o tabuleiro
        drawPiece(&currentPiece); // Desenha a peça atual
        screenUpdate();     // Atualiza a tela (com todos os desenhos)

        // Verifica se o jogo terminou (por exemplo, se uma peça colidiu com outra ou com o topo)
        if (isGameOver()) {
            break;  // Encerra o loop do jogo caso o jogo tenha terminado
        }
    }

    screenDestroy();      // Destrói a tela (libera recursos)
    keyboardDestroy();    // Destrói os recursos do teclado
    return 0;
}
