#include "screen.h"
#include "timer.h"
#include "keyboard.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LARGURA 10
#define ALTURA 20
#define TAM_BLOCO 2

//Todas as nossas funções listadas antes da main -- sempre add novas lá pra facilitar!

int nivel = 1; 
int pontuacao = 0;
int atualModo = 1;

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
int board[LARGURA][ALTURA];

// Estrutura p/ representar uma peça
typedef struct {
    int x, y;
    int type;
    int rotacao;
} Peca;

Peca atualPeca;

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
int checkColisao(Peca *peca) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[peca->type][peca->rotacao][i][j]) {
                int x = peca->x + i;
                int y = peca->y + j;
                if (x < 0 || x >= LARGURA || y >= ALTURA || board[x][y]) {
                    return 1;  // Colidiu com a borda/outra peça
                }
            }
        }
    }
    return 0;  // Sem colisão
}

// Função que coloca a peça no tabuleiro
void colocaPeca(Peca *peca) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[peca->type][peca->rotacao][i][j]) {
                board[peca->x + i][peca->y + j] = 1;  // Marca o tabuleiro com a peça
            }
        }
    }
}

// Função que rotaciona a peça
void rotacionaPeca() {
    int antigaRotacao = atualPeca.rotacao;
    atualPeca.rotacao = (atualPeca.rotacao + 1) % 4;  // Rotaciona p/ próxima posição
    if (checkColisao(&atualPeca)) {
        atualPeca.rotacao = antigaRotacao;  // Sem colisão, volta p/ rotação anterior
    }
}

// Função que rotaciona a peça no sentido anti-horário 
void rotacionaPecaContrario() {
    int antigaRotacao = atualPeca.rotacao;
    atualPeca.rotacao = (atualPeca.rotacao + 3) % 4;  // Subtrair rotação (anti-horário)

    if (checkColisao(&atualPeca)) {
        atualPeca.rotacao = antigaRotacao;  // Sem colisão, volta para rotação anterior
    }
}

// Função que move a peça (horizontal)
void movePeca(int dx) {
    atualPeca.x += dx;  // Esquerda (dx=-1) / Direita (dx=1)
    if (checkColisao(&atualPeca)) {
        atualPeca.x -= dx;  // Com colisão desfaz o movimento
    }
}

// Função que desenha a peça na tela
void desenhaPeca(Peca *peca) {
    screenSetColor(RED, BLACK);  // Definindo cor
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[peca->type][peca->rotacao][i][j]) {  // Verificando se a célula está ativa
                screenGotoxy(SCRSTARTX + (peca->x + i) * TAM_BLOCO, SCRSTARTY + peca->y + j);  // Calculando a posição na tela
                printf("[]");  // Desenho do bloxo da peça
            }
        }
    }
}


void drawBoard() {
    screenClear();
    screenSetColor(CYAN, BLACK);
    for (int i = 0; i < LARGURA; i++) {
        for (int j = 0; j < ALTURA; j++) {
            if (board[i][j]) {
                screenGotoxy(SCRSTARTX + i * TAM_BLOCO, SCRSTARTY + j);
                printf("[]");
            }
        }
    }
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY);
    printf(" _______________________");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 1);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 2);
    printf("< Nível: %d              >", nivel);
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 3);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 4);
    printf("< Pontuação: %d          >", pontuacao);
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 5);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 6);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 7);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 8);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 9);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 10);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 11);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 12);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 13);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 14);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 15);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 16);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 17);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 18);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 19);
    printf("<                       >");
    screenGotoxy(SCRSTARTX + LARGURA * TAM_BLOCO + 1, SCRSTARTY + 20);
    printf("<_______________________>");

}

// Função que remove linhas completas
void removeLinhaCompleta() {
    for (int j = 0; j < ALTURA; j++) {
        int full = 1;
        for (int i = 0; i < LARGURA; i++) {
            if (!board[i][j]) {
                full = 0;
                break;
            }
        }
        if (full) {
            for (int k = j; k > 0; k--) {
                for (int i = 0; i < LARGURA; i++) {
                    board[i][k] = board[i][k - 1];
                }
            }
            for (int i = 0; i < LARGURA; i++) {
                board[i][0] = 0;
            }
            pontuacao += 100; // 100pts de linha completa
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
void salvarPontuacaoNoRanking(int pontuacao) {
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
    fprintf(rankingFile, "%s %d\n", nome, pontuacao);

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


void exibirMenu(int pontuacao) {
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
                    salvarPontuacaoNoRanking(pontuacao);
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

void gerarPeca() {
    atualPeca.x = LARGURA / 2 - 2;
    atualPeca.y = 0;
    atualPeca.type = rand() % 7;
    atualPeca.rotacao = 0;
    if (checkColisao(&atualPeca)) {
        screenDestroy();
        exibirGameOver();
        exibirMenu(pontuacao);
        exit(0);
    }
}

void descePeca() {
    atualPeca.y++;
    if (checkColisao(&atualPeca)) {
        atualPeca.y--;
        colocaPeca(&atualPeca);
        removeLinhaCompleta();
        gerarPeca();
    }
}

void descePecaMaisRapido() {
    atualPeca.y++; //1a descida
    if (!checkColisao(&atualPeca)) {
        atualPeca.y++; // S/ colisão? 2a descida
        if (!checkColisao(&atualPeca)) {
            atualPeca.y++; // S/ colisão? 3a descida
        }
    }

    if (checkColisao(&atualPeca)) {
        atualPeca.y--;  // Volta a posição se colidir
        colocaPeca(&atualPeca);
        removeLinhaCompleta();
        gerarPeca();  // Gerando nova peça
    }
}

void processaInput() {
    if (keyhit()) {
        int key = readch();

        if (atualModo == 1) {  // Modo Clássico
            switch (key) {
                case 'a': movePeca(-1); break; // A == esquerda
                case 'd': movePeca(1); break; // D -- direita
                case 's': descePeca(); break;
                case 'w': rotacionaPeca(); break;
            }
        } else if (atualModo == 2) {  // Modo Desafio
            switch (key) {
                case 'a': movePeca(1); break;  // A == direita 
                case 'd': movePeca(-1); break; // D == esquerda 
                case 's': descePecaMaisRapido(); break; // desce 2x mais
                case 'w': rotacionaPecaContrario(); break; // anti-horario
            }
        }
    }
}

void screenDrawBorders();
void exibirTelaInicial();
void exibirInstrucoes(int modo);
int checkColisao(Peca *peca);
void colocaPeca(Peca *peca);
void rotacionaPeca();
void rotacionaPecaContrario();
void movePeca(int dx);
void desenhaPeca(Peca *peca);
void drawBoard();
void removeLinhaCompleta();
void salvarRanking(Ranking *ranking, int numJogadores);
int carregarRanking(Ranking *ranking);
void salvarPontuacaoNoRanking(int pontuacao);
void exibirRanking();
void exibirGameOver();
void exibirMenu(int pontuacao);
void gerarPeca();
void descePeca();
void descePecaMaisRapido();
void processaInput();
//add descePecaMaisRapido, rotacionaPecaContrario aqui dps (org ordem)

int main() {
    exibirTelaInicial();
    int modoSelecionado = escolherModo();
    atualModo = modoSelecionado;

    exibirInstrucoes(modoSelecionado);

    srand(time(NULL));
    screenInit(1);
    keyboardInit();
    timerInit(500); // Intervalo de 500ms

    gerarPeca(); // Gerando a primeira peça

    while (1) {
        processaInput(); // Entradas do usuário -- movimentação e rotação da peça!
        
        if (timerTimeOver()) { // Verificando se o tempo acabou p/ descer a peça
            descePeca();
        }

        drawBoard(); 
        desenhaPeca(&atualPeca);
        screenUpdate();         
    }

    screenDestroy(); // free()?
    keyboardDestroy(); 
    return 0;
}