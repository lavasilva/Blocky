#include "screen.h"
#include "timer.h"
#include "keyboard.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LARGURA 10
#define ALTURA 20
#define TAM_BLOCO 2

int nivel = 1; 
int pontuacao = 0;
int atualModo = 1;

void screenDrawBorders();

char tetrominos[7][4][4][4] = {
    { 
        { {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0} },
        { {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0} }
    },
    { 
        { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }
    },
    { 
        { {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} }
    },
    { 
        { {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} }
    },
    { 
        { {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0} }
    },
    { 
        { {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} },
        { {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0} }
    },
    { 
        { {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0} },
        { {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0} }
    }
};  

int tabuleiro[LARGURA][ALTURA];

typedef struct {
    int x, y;
    int type;
    int rotacao;
} Peca;

Peca atualPeca;
struct RankingCelula *head = NULL;

typedef struct RankingCelula {
    char nome[50];
    int pontuacao;
    struct RankingCelula *next;
} RankingCelula;

void exibirTelaInicial() {
    system("clear"); 

    screenDrawBorders();

    int titulo_linhas = 6; 
    int titulo_comprimento = 50;  
    int start_x = (MAXX - titulo_comprimento) / 2; 

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

    } while (modo < 1 || modo > 2); 

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

    if (modo == 1) { 
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

    } else if (modo == 2) {  
        screenGotoxy(start_x, 9);
        printf("                INSTRUÇÕES DO MODO DESAFIO                 \n");

        screenGotoxy(start_x, 12);
        printf("Neste modo, os controles A e D são invertidos...           \n");
        screenGotoxy(start_x, 13);
        printf("E as peças caem 3x mais rápido com o S! Bom jogo!          \n");
    }

    screenGotoxy(start_x, 15);
    printf("                                                               \n");
    screenGotoxy(start_x, 16);
    printf("               Pressione ENTER para começar...            \n");
    screenGotoxy(start_x, 17);
    printf("                                                               \n");

    getchar();
}

int checkColisao(Peca *peca) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[peca->type][peca->rotacao][i][j]) {
                int x = peca->x + i;
                int y = peca->y + j;
                if (x < 0 || x >= LARGURA || y >= ALTURA || tabuleiro[x][y]) {
                    return 1;  
                }
            }
        }
    }
    return 0;  
}

void colocaPeca(Peca *peca) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[peca->type][peca->rotacao][i][j]) {
                tabuleiro[peca->x + i][peca->y + j] = 1;  
            }
        }
    }
}

void rotacionaPeca() {
    int antigaRotacao = atualPeca.rotacao;
    atualPeca.rotacao = (atualPeca.rotacao + 1) % 4;  
    if (checkColisao(&atualPeca)) {
        atualPeca.rotacao = antigaRotacao;  
    }
}

void rotacionaPecaContrario() {
    int antigaRotacao = atualPeca.rotacao;
    atualPeca.rotacao = (atualPeca.rotacao + 3) % 4; 

    if (checkColisao(&atualPeca)) {
        atualPeca.rotacao = antigaRotacao; 
    }
}

void movePeca(int dx) {
    atualPeca.x += dx;  
    if (checkColisao(&atualPeca)) {
        atualPeca.x -= dx; 
    }
}

void desenhaPeca(Peca *peca) {
    screenSetColor(RED, BLACK);  
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[peca->type][peca->rotacao][i][j]) { 
                screenGotoxy(SCRSTARTX + (peca->x + i) * TAM_BLOCO, SCRSTARTY + peca->y + j);  
                printf("[]");  
            }
        }
    }
}


void desenhaTabuleiro() {
    screenClear();
    screenSetColor(CYAN, BLACK);
    for (int i = 0; i < LARGURA; i++) {
        for (int j = 0; j < ALTURA; j++) {
            if (tabuleiro[i][j]) {
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

void removeLinhaCompleta() {
    for (int j = 0; j < ALTURA; j++) {
        int full = 1;
        for (int i = 0; i < LARGURA; i++) {
            if (!tabuleiro[i][j]) {
                full = 0;
                break;
            }
        }
        if (full) {
            for (int k = j; k > 0; k--) {
                for (int i = 0; i < LARGURA; i++) {
                    tabuleiro[i][k] = tabuleiro[i][k - 1];
                }
            }
            for (int i = 0; i < LARGURA; i++) {
                tabuleiro[i][0] = 0;
            }
            pontuacao += 100; 
        }
    }
}

void salvarRanking(RankingCelula *head) {
    FILE *file = fopen("ranking.txt", "w");
    if (file == NULL) {
        printf("Erro ao salvar o ranking!\n");
        return;
    }

    RankingCelula *current = head;
    while (current != NULL) {
        fprintf(file, "%s %d\n", current->nome, current->pontuacao);
        current = current->next;
    }
    fclose(file);
}

RankingCelula* carregarRanking() {
    FILE *file = fopen("ranking.txt", "r");
    if (file == NULL) {
        printf("Nenhum ranking salvo encontrado.\n");
        return NULL;
    }

    RankingCelula *head = NULL, *tail = NULL;
    while (!feof(file)) {
        RankingCelula *novaCelula = (RankingCelula*)malloc(sizeof(RankingCelula));
        if (fscanf(file, "%49s %d", novaCelula->nome, &novaCelula->pontuacao) == 2) {
            novaCelula->next = NULL;
            if (head == NULL) {
                head = novaCelula;
                tail = novaCelula;
            } else {
                tail->next = novaCelula;
                tail = novaCelula;
            }
        } else {
            free(novaCelula);
        }
    }
    fclose(file);
    return head;
}

void salvarPontuacaoNoRanking(RankingCelula **head, int pontuacao) {
    char nome[50];
    printf("Digite seu nome para o ranking: ");
    fflush(stdout);
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    RankingCelula *novaCelula = (RankingCelula*)malloc(sizeof(RankingCelula));
    strcpy(novaCelula->nome, nome);
    novaCelula->pontuacao = pontuacao;
    novaCelula->next = NULL;

    if (*head == NULL || (*head)->pontuacao <= pontuacao) {
        novaCelula->next = *head;
        *head = novaCelula;
    } else {
        RankingCelula *current = *head;
        while (current->next != NULL && current->next->pontuacao > pontuacao) {
            current = current->next;
        }
        novaCelula->next = current->next;
        current->next = novaCelula;
    }

    FILE *file = fopen("ranking.txt", "a");  
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de ranking.\n");
        return;
    }
    fprintf(file, "%s %d\n", nome, pontuacao);
    fclose(file);

    printf("Ranking Atualizado!\n");
}

void exibirRanking() {
    FILE *file = fopen("ranking.txt", "r");
    if (file == NULL) {
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
    int posicao = 1;
    char nome[50];
    int pontuacao;

    while (fscanf(file, "%49s %d", nome, &pontuacao) == 2) {
        char linha[100];
        snprintf(linha, sizeof(linha), "%d. %s - %d", posicao++, nome, pontuacao);

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

    getchar();
    fclose(file);
}


void liberarRanking(RankingCelula *head) {
    RankingCelula *current = head;
    while (current != NULL) {
        RankingCelula *next = current->next;
        free(current);
        current = next;
    }
}

void exibirGameOver() {
    system("clear"); 

    screenDrawBorders();

    int titulo_comprimento = 72;  
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

    screenGotoxy((MAXX - 38) / 2, 12);
    printf("O Jogo Acabou! Você perdeu!\n");

   printf("\nPressione ENTER para voltar ao menu principal...\n");
    getchar();  

}


void exibirMenu(RankingCelula **head, int pontuacao) {
    int opcao;
    char input[10];
    int pontuacaoSalva = 0;  
    int rankingExibido = 0;  

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

        screenGotoxy((MAXX - 24) / 2, 10);
        printf("1. Salvar pontuação\n");

        screenGotoxy((MAXX - 24) / 2, 11);
        printf("2. Ver ranking\n");

        screenGotoxy((MAXX - 24) / 2, 12);
        printf("3. Sair\n");

        screenGotoxy((MAXX - 24) / 2, 14);  
        printf("Escolha uma opção: ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) != NULL) {
            opcao = atoi(input); 
        } else {
            opcao = 0;
        }

        switch (opcao) {
            case 1:
                if (!pontuacaoSalva) {  
                    salvarPontuacaoNoRanking(head, pontuacao);
                    pontuacaoSalva = 1; 
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
        exibirMenu(&head, pontuacao);
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
    atualPeca.y++;
    if (!checkColisao(&atualPeca)) {
        atualPeca.y++; 
        if (!checkColisao(&atualPeca)) {
            atualPeca.y++; 
        }
    }

    if (checkColisao(&atualPeca)) {
        atualPeca.y--; 
        colocaPeca(&atualPeca);
        removeLinhaCompleta();
        gerarPeca(); 
    }
}

void processaInput() {
    if (keyhit()) {
        int key = readch();

        if (atualModo == 1) { 
            switch (key) {
                case 'a': movePeca(-1); break; 
                case 'd': movePeca(1); break; 
                case 's': descePeca(); break;
                case 'w': rotacionaPeca(); break;
            }
        } else if (atualModo == 2) {  
            switch (key) {
                case 'a': movePeca(1); break; 
                case 'd': movePeca(-1); break;
                case 's': descePecaMaisRapido(); break; 
                case 'w': rotacionaPecaContrario(); break; 
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
void desenhaTabuleiro();
void removeLinhaCompleta();
void salvarRanking(RankingCelula *head);
RankingCelula* carregarRanking();
void salvarPontuacaoNoRanking(RankingCelula **head, int pontuacao); 
void exibirRanking();
void exibirGameOver();
void exibirMenu(RankingCelula **head, int pontuacao);
void gerarPeca();
void descePeca();
void descePecaMaisRapido();
void processaInput();

int main() {
    exibirTelaInicial();
    int modoSelecionado = escolherModo();
    atualModo = modoSelecionado;

    exibirInstrucoes(modoSelecionado);

    srand(time(NULL));
    screenInit(1);
    keyboardInit();
    timerInit(500); 

    gerarPeca(); 

    while (1) {
        processaInput();
        
        if (timerTimeOver()) { 
            descePeca();
        }

        desenhaTabuleiro(); 
        desenhaPeca(&atualPeca);
        screenUpdate();         
    }

    screenDestroy(); 
    keyboardDestroy(); 
    return 0;
}