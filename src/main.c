#include "screen.h"
#include "timer.h"
#include "keyboard.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WIDTH 10
#define HEIGHT 20
#define BLOCK_SIZE 2

//Todas as nossas funções -- sempre add novas aqui pra facilitar!
void screenDrawBorders();
void exibirTelaInicial();
void exibirInstrucoes();
int checkCollision();
void placePiece();
void rotatePiece();
void movePiece();
void drawPiece();
void drawBoard();
void removeFullLines();
void salvarRanking();
int carregarRanking();
void salvarPontuacaoNoRanking();
void exibirRanking();
void exibirGameOver();
void exibirMenu();
void spawnPiece();
void dropPiece();
void processInput();
//add dropPieceMaisRapido, rotatePieceContrario aqui dps (org ordem)

int level = 1; 
int score = 0;
int currentMode = 1;

void screenDrawBorders();
// Definição das formas das peças com todas as rotações possíveis
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

// Estado do tabuleiro
int board[WIDTH][HEIGHT];

// Estrutura p/ representar uma peça
typedef struct {
    int x, y;
    int type;
    int rotation;
} Piece;

Piece currentPiece;

// Estrutura p/ armazenar o ranking
typedef struct {
    char nome[50];
    int pontuacao;
} Ranking;

void exibirTelaInicial() {
    system("clear"); // Limpando o terminal -- checar se podemos mudar isso (ajuste pra 'pica-pisca' do terminal)

    // Chama a função para desenhar as bordas
    screenDrawBorders();

    // Centralizar o título ASCII
    int titulo_linhas = 6; 
    int titulo_comprimento = 50;  
    int start_x = (MAXX - titulo_comprimento) / 2;  // Calculando a posição de início para centralizar -- vamos usar em vários momentos

    screenGotoxy(start_x, 5);
    printf("██████╗░██╗░░░░░░█████╗░░█████╗░██╗░░██╗██╗░░░██╗\n");
    screenGotoxy(start_x, 6);
    printf("██╔══██╗██║░░░░░██╔══██╗██╔══██╗██║░██╔╝╚██╗░██╔╝\n");
    screenGotoxy(start_x, 7);
    printf("██████╦╝██║░░░░░██║░░██║██║░░╚═╝█████═╝░░╚████╔╝░\n");
    screenGotoxy(start_x, 8);
    printf("██╔══██╗██║░░░░░██║░░██║██║░░██╗██╔═██╗░░░╚██╔╝░░\n");
    screenGotoxy(start_x, 9);
    printf("██████╦╝███████╗╚█████╔╝╚█████╔╝██║░╚██╗░░░██║░░░\n");
    screenGotoxy(start_x, 10);
    printf("╚═════╝░╚══════╝░╚════╝░░╚════╝░╚═╝░░╚═╝░░░╚═╝░░░\n");

    char nome[50];
    screenGotoxy((MAXX - 42) / 2, 12);
    printf("Digite seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    screenGotoxy((MAXX - 42) / 2, 14);
    printf("Bem-vindo(a), %s! Prepare-se para o jogo!", nome);

    screenGotoxy((MAXX - 42) / 2, 16);
    printf("Pressione ENTER para começar...\n");

    // Aguardando usuário ...
    getchar();
}

int escolherModo() {
    int modo;
    char input[10];

    do {
        system("clear"); 
        
        screenGotoxy((MAXX - 128) / 2, 5);  
        printf("      __  __ ___ _  _ _   _   ___ ___ ___ _  _  ___ ___ ___  _   _    \n");
        screenGotoxy((MAXX - 128) / 2, 6);
        printf("     |  \\/  | __| \\| | | | | | _ \\ _ \\_ _| \\| |/ __|_ _| _ \\/_\\ | |   \n");
        screenGotoxy((MAXX - 128) / 2, 7);
        printf("     | |\\/| | _|| .` | |_| | |  _/   /| || .` | (__ | ||  _/ _ \\| |__ \n");
        screenGotoxy((MAXX - 128) / 2, 8);
        printf("     |_|  |_|___|_|\\_|\\___/  |_| |_|_\\___|_|\\_|\\___|___|_|/_/ \\_\\____|\n");

        screenGotoxy((MAXX - 24) / 2, 12);
        printf("1. Modo Clássico\n");

        screenGotoxy((MAXX - 24) / 2, 14);
        printf("2. Modo Desafio\n");

        screenGotoxy((MAXX - 24) / 2, 16);
        printf("Escolha uma opção: ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) != NULL) {
            modo = atoi(input);  
        } else {
            modo = 0;
        }

        if (modo < 1 || modo > 2) {
            printf("Opção inválida. Tente novamente.\n");
            printf("Pressione ENTER para voltar para o menu...");
            getchar();  
        }

    } while (modo < 1 || modo > 2);  // Continua até escolha válida

    return modo; 
}


void exibirInstrucoes(int modo) {
    system("clear");

    screenDrawBorders();

    int instrucoes_comprimento = 60;
    int start_x = (MAXX - instrucoes_comprimento) / 2;

    screenGotoxy(start_x, 5);  
    screenGotoxy(start_x, 6);
    printf("                                                              \n");

    screenGotoxy(start_x, 7);
    printf("                                                              \n");
    screenGotoxy(start_x, 8);
    printf("                                                              \n");

    if (modo == 1) {  // Modo Clássico
        screenGotoxy(start_x, 9);
        printf("                INSTRUÇÕES DO MODO CLÁSSICO               \n");

        screenGotoxy(start_x, 12);
        printf(" Use as setas para mover as peças:                         \n");
        screenGotoxy(start_x, 13);
        printf("  A: Mover para a Esquerda                                 \n");
        screenGotoxy(start_x, 14);
        printf("  D: Mover para a Direita                                  \n");
        screenGotoxy(start_x, 15);
        printf("  W: Girar a peça                                          \n");
        screenGotoxy(start_x, 16);
        printf("  S: Acelerar a queda da peça                              \n");

    } else if (modo == 2) {  // Modo Desafio
        screenGotoxy(start_x, 9);
        printf("                INSTRUÇÕES DO MODO DESAFIO                \n");

        screenGotoxy(start_x, 12);
        printf(" Neste modo, os controles são invertidos!                 \n");
        screenGotoxy(start_x, 13);
        printf("  A: Mover para a Direita                                  \n");
        screenGotoxy(start_x, 14);
        printf("  D: Mover para a Esquerda                                 \n");
        screenGotoxy(start_x, 15);
        printf("  W: Girar a peça (sentido anti-horário)                   \n");
        screenGotoxy(start_x, 16);
        printf("  S: Acelera a queda da peça                               \n");
    }

    screenGotoxy(start_x, 15);
    printf("                                                          \n");
    screenGotoxy(start_x, 16);
    printf("      Pressione ENTER para começar...                     \n");
    screenGotoxy(start_x, 17);
    printf("                                                          \n");

    // Enter do usuário
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
                    return 1;  // Colidiu com a borda/outra peça
                }
            }
        }
    }
    return 0;  // Sem colisão
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
    currentPiece.rotation = (currentPiece.rotation + 1) % 4;  // Rotaciona p/ próxima posição
    if (checkCollision(&currentPiece)) {
        currentPiece.rotation = oldRotation;  // Sem colisão, volta p/ rotação anterior
    }
}

// Função que rotaciona a peça no sentido anti-horário 
void rotatePieceContrario() {
    int oldRotation = currentPiece.rotation;
    currentPiece.rotation = (currentPiece.rotation + 3) % 4;  // Subtrair rotação (anti-horário)

    if (checkCollision(&currentPiece)) {
        currentPiece.rotation = oldRotation;  // Sem colisão, volta para rotação anterior
    }
}

// Função que move a peça (horizontal)
void movePiece(int dx) {
    currentPiece.x += dx;  // Esquerda (dx=-1) / Direita (dx=1)
    if (checkCollision(&currentPiece)) {
        currentPiece.x -= dx;  // Com colisão desfaz o movimento
    }
}

// Função que desenha a peça na tela
void drawPiece(Piece *piece) {
    screenSetColor(RED, BLACK);  // Definindo cor
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[piece->type][piece->rotation][i][j]) {  // Verificando se a célula está ativa
                screenGotoxy(SCRSTARTX + (piece->x + i) * BLOCK_SIZE, SCRSTARTY + piece->y + j);  // Calculando a posição na tela
                printf("[]");  // Desenho do bloxo da peça
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
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY);
    printf(" _______________________");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 1);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 2);
    printf("< Nível: %d              >", level);
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 3);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 4);
    printf("< Pontuação: %d          >", score);
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 5);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 6);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 7);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 8);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 9);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 10);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 11);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 12);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 13);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 14);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 15);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 16);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 17);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 18);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 19);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 1, SCRSTARTY + 20);
    printf("<_______________________>");

}

// Função que remove linhas completas
void removeFullLines() {
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
            score += 100; // 100pts de linha completa
        }
    }
}

//
void salvarRanking(Ranking *ranking, int numJogadores) {
    FILE *file = fopen("ranking.txt", "w");
    if (file == NULL) {
        printf("Erro ao salvar o ranking!\n");
        return;
    }
    for (int i = 0; i < numJogadores; i++) {
        fprintf(file, "%s %d\n", ranking[i].nome, ranking[i].pontuacao);
    }
    fclose(file);
}

//
int carregarRanking(Ranking *ranking) {
    FILE *file = fopen("ranking.txt", "r");
    int numJogadores = 0;
    if (file != NULL) {
        while (fscanf(file, "%49s %d", ranking[numJogadores].nome, &ranking[numJogadores].pontuacao) != EOF) {
            numJogadores++;
        }
        fclose(file);
    }
    return numJogadores;
}

//
void salvarPontuacaoNoRanking(int score) {
    char nome[50];

    printf("Digite seu nome para o ranking: ");
    fflush(stdout);  // Garantindo q msg seja exibida de imediato
    fgets(nome, sizeof(nome), stdin);  
    nome[strcspn(nome, "\n")] = '\0';  

    FILE *rankingFile = fopen("ranking.txt", "a");
    if (rankingFile == NULL) {
        printf("Erro ao abrir o arquivo de ranking.\n");
        return;
    }

    // Adicionando no arquivo
    fprintf(rankingFile, "%s %d\n", nome, score);

    fclose(rankingFile);

    printf("Ranking Atualizado!\n");
}

// qsort, p/ ordenar em ordem decrescente
int compararPontuacao(const void *a, const void *b) {
    Ranking *rankingA = (Ranking *)a;
    Ranking *rankingB = (Ranking *)b;
    return rankingB->pontuacao - rankingA->pontuacao;
}

//
void exibirRanking() {
    Ranking ranking[100]; 
    int numJogadores = carregarRanking(ranking);

    qsort(ranking, numJogadores, sizeof(Ranking), compararPontuacao);

    if (numJogadores == 0) {
        printf("Nenhum ranking encontrado.\n");
        return;
    }

    system("clear");

    screenGotoxy((MAXX - 144) / 2, 5);
    printf("      ___    _   _  _ _  _____ _  _  ___   ___   ___  ___      _  ___   ___   _   ___   ___  ___ ___ ___ \n");
    screenGotoxy((MAXX - 144) / 2, 6);
    printf("     | _ \\  /_\\ | \\| | |/ /_ _| \\| |/ __| |   \\ / _ \\/ __|  _ | |/ _ \\ / __| /_\\ |   \\ / _ \\| _ \\ __/ __|\n");
    screenGotoxy((MAXX - 144) / 2, 7);
    printf("     |   / / _ \\| .` | ' < | || .` | (_ | | |) | (_) \\__ \\ | || | (_) | (_ |/ _ \\| |) | (_) |   / _|\\__ \\\n");
    screenGotoxy((MAXX - 144) / 2, 8);
    printf("     |_|_\\/_/ \\_\\_|\\_|_|\\_\\___|_|\\_|\\___| |___/ \\___/|___/  \\__/ \\___/ \\___/_/ \\_\\___/ \\___/|_|_\\___|___/\n");

    int linhaNum = 10; 
    for (int i = 0; i < numJogadores; i++) {
        //Posição, nome e pts
        char linha[100];
        snprintf(linha, sizeof(linha), "%d. %s - %d", i + 1, ranking[i].nome, ranking[i].pontuacao);

        int comprimentoLinha = strlen(linha);
        int start_x = (MAXX - comprimentoLinha) / 2;

        screenGotoxy(start_x, linhaNum++);
        printf("%s\n", linha);
    }

    char msg[] = "Pressione ENTER para voltar pro menu principal...";
    int msgLength = strlen(msg);
    int start_x = (MAXX - msgLength) / 2;
    screenGotoxy(start_x, linhaNum + 1);
    printf("%s\n", msg);

    // Enter...
    getchar();
}


// Função para exibir "Game Over" e voltar ao menu
void exibirGameOver() {
    system("clear"); 

    screenDrawBorders();

    int titulo_comprimento = 72;  // Comprimento médio do título (ajuste conforme necessário)
    int start_x = (MAXX - titulo_comprimento) / 2; 

    screenGotoxy(start_x, 5); 
    printf(" ██████   █████  ███    ███ ███████      ██████  ██    ██ ███████ ██████  \n");
    screenGotoxy(start_x, 6);
    printf("██       ██   ██ ████  ████ ██          ██    ██ ██    ██ ██      ██   ██ \n");
    screenGotoxy(start_x, 7);
    printf("██   ███ ███████ ██ ████ ██ █████       ██    ██ ██    ██ █████   ██████  \n");
    screenGotoxy(start_x, 8);
    printf("██    ██ ██   ██ ██  ██  ██ ██          ██    ██  ██  ██  ██      ██   ██ \n");
    screenGotoxy(start_x, 9);
    printf(" ██████  ██   ██ ██      ██ ███████      ██████    ████   ███████ ██   ██ \n");

    // Exibindo centralizada - resolvido!!
    screenGotoxy((MAXX - 38) / 2, 12);
    printf("O Jogo Acabou! Você perdeu!\n");

   printf("\nPressione ENTER para voltar ao menu principal...\n");
    getchar();  // Enter..

}


void exibirMenu(int score) {
    int opcao;
    char input[10];
    int pontuacaoSalva = 0;  // Flag -- verificar se a pontuação já foi salva e mostrar msg 
    int rankingExibido = 0;  // Flag -- verificar se o ranking já foi exibido e mostrar msg 

    do {
        system("clear"); 

        screenGotoxy((MAXX - 128) / 2, 5); 
        printf("      __  __ ___ _  _ _   _   ___ ___ ___ _  _  ___ ___ ___  _   _    \n");
        screenGotoxy((MAXX - 128) / 2, 6);
        printf("     |  \\/  | __| \\| | | | | | _ \\ _ \\_ _| \\| |/ __|_ _| _ \\/_\\ | |   \n");
        screenGotoxy((MAXX - 128) / 2, 7);
        printf("     | |\\/| | _|| .` | |_| | |  _/   /| || .` | (__ | ||  _/ _ \\| |__ \n");
        screenGotoxy((MAXX - 128) / 2, 8);
        printf("     |_|  |_|___|_|\\_|\\___/  |_| |_|_\\___|_|\\_|\\___|___|_|/_/ \\_\\____|\n");

        // Ajustes p/ centralizar  
        screenGotoxy((MAXX - 24) / 2, 10);
        printf("1. Salvar pontuação\n");

        screenGotoxy((MAXX - 24) / 2, 11);
        printf("2. Ver ranking\n");

        screenGotoxy((MAXX - 24) / 2, 12);
        printf("3. Sair\n");

        screenGotoxy((MAXX - 24) / 2, 14);  
        printf("Escolha uma opção: ");
        fflush(stdout); // Garantindo que a msg seja exibida de imediato

        if (fgets(input, sizeof(input), stdin) != NULL) {
            opcao = atoi(input);  // Lê str, converte para inteiro
        } else {
            opcao = 0;
        }

        switch (opcao) {
            case 1:
                if (!pontuacaoSalva) {  
                    salvarPontuacaoNoRanking(score);
                    pontuacaoSalva = 1;  // Marca flag -- pontuação salva
                } else {
                    printf("A pontuação já foi salva!\n");
                    printf("Pressione ENTER para continuar...");
                    getchar();
                }
                break;
            case 2:
                exibirRanking();
                break;
            case 3:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                printf("Pressione ENTER para voltar para o menu principal...");
                getchar();
                break;
        }

    } while (opcao != 3);
}

void spawnPiece() {
    currentPiece.x = WIDTH / 2 - 2;
    currentPiece.y = 0;
    currentPiece.type = rand() % 7;
    currentPiece.rotation = 0;
    if (checkCollision(&currentPiece)) {
        screenDestroy();
        exibirGameOver();
        exibirMenu(score);
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

void dropPieceMaisRapido() {
    currentPiece.y++; // 1a descida

    if (!checkCollision(&currentPiece)) {  // Verificando colisão dps de 1 descida
        currentPiece.y++;  // Sem colisão, 2x descida
    }
    
    if (checkCollision(&currentPiece)) {  // Fez a segunda colisão verificar
        currentPiece.y--;  // Colisão? Volta p/ posição anterior
        placePiece(&currentPiece); 
        removeFullLines();  
        spawnPiece();  // Gerando +1 nova peça
    }
}

void processInput() {
    if (keyhit()) {
        int key = readch();

        if (currentMode == 1) {  // Modo Clássico
            switch (key) {
                case 'a': movePiece(-1); break; // A == esquerda
                case 'd': movePiece(1); break; // D -- direita
                case 's': dropPiece(); break;
                case 'w': rotatePiece(); break;
            }
        } else if (currentMode == 2) {  // Modo Desafio
            switch (key) {
                case 'a': movePiece(1); break;  // A == direita 
                case 'd': movePiece(-1); break; // D == esquerda 
                case 's': dropPieceMaisRapido(); break; // desce 2x mais
                case 'w': rotatePieceContrario(); break; // anti-horario
            }
        }
    }
}

int main() {
    exibirTelaInicial();
    int modoSelecionado = escolherModo();
    currentMode = modoSelecionado;

    exibirInstrucoes(modoSelecionado);

    srand(time(NULL));
    screenInit(1);
    keyboardInit();
    timerInit(500); // Intervalo de 500ms

    spawnPiece(); // Gerando a primeira peça

    while (1) {
        processInput(); // Entradas do usuário -- movimentação e rotação da peça!
        
        if (timerTimeOver()) { // Verificando se o tempo acabou p/ descer a peça
            dropPiece();
        }

        drawBoard(); 
        drawPiece(&currentPiece);
        screenUpdate();         
    }

    screenDestroy(); // free()?
    keyboardDestroy(); 
    return 0;
}