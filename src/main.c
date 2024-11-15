#include "screen.h"
#include "timer.h"
#include "keyboard.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WIDTH 10
#define HEIGHT 20
#define BLOCK_SIZE 2


void desenharBordas();
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

int nivel = 1;  // Nível do jogo
int placar = 0;  // Pontuação

// Estado do tabuleiro
int board[WIDTH][HEIGHT];

// Estrutura para representar uma peça
typedef struct {
    int x, y;
    int tipo;
    int rodar;
} Peca;

Peca currentPeca;

// Estrutura para armazenar o ranking
typedef struct {
    char nome[50];
    int pontuacao;
} Ranking;



void exibirTelaInicial() {
    system("clear"); // Limpa o terminal (ajuste para "cls" se estiver no Windows)

    // Chama a função para desenhar as bordas
    desenharBordas();

    int titulo_linhas = 6;  // O título tem 6 linhas
    int titulo_comprimento = 50;  // Comprimento médio do título (ajuste conforme necessário)
    int start_x = (MAXX - titulo_comprimento) / 2;  // Calcula a posição de início para centralizar


    screenGotoxy(start_x, 5);  // Posição de início para o título (ajuste a linha se necessário)
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

   // Solicitar o nome do jogador
    char nome[50];
    screenGotoxy((MAXX - 42) / 2, 12);  // Posição para a mensagem de solicitação do nome
    printf("Digite seu nome: ");
    fgets(nome, sizeof(nome), stdin);  // Lê o nome do jogador

    // Remover o caractere de nova linha do nome, se houver
    nome[strcspn(nome, "\n")] = '\0';

    // Exibir a mensagem com o nome do jogador
    screenGotoxy((MAXX - 42) / 2, 14);
    printf("Bem-vindo(a), %s! Prepare-se para o jogo!", nome);

    // Exibe a mensagem de preparação centralizada
    screenGotoxy((MAXX - 42) / 2, 16);
    printf("Pressione ENTER para começar...\n");

    // Aguarde o usuário iniciar
    getchar();
}


void exibirInstrucoes() {
    system("clear"); // Limpa o terminal para as instruções
    
    // Desenha as bordas ao redor da área de instruções
    desenharBordas();

    // Centralizar o título das instruções
    int instrucoes_comprimento = 60; // Comprimento médio das instruções
    int start_x = (MAXX - instrucoes_comprimento) / 2;  // Recalcular a posição de início para centralizar

    // Exibe o título das instruções com borda
    screenGotoxy(start_x, 5);  // Posição de início para o título
    screenGotoxy(start_x, 6);
    printf("                                                          \n");
    screenGotoxy(start_x, 7);
    printf("                   INSTRUÇÕES DO TETRIS                   \n");
    screenGotoxy(start_x, 8);
    printf("                                                          \n");

    // Exibe o conteúdo das instruções, centralizado
    screenGotoxy(start_x, 9);
    printf(" Use as setas para mover as peças:                        \n");
    screenGotoxy(start_x, 10);
    printf("  A: Mover para a Esquerda                                 \n");
    screenGotoxy(start_x, 11);
    printf("  D: Mover para a Direita                                  \n");
    screenGotoxy(start_x, 12);
    printf("  W: Girar a peça                                         \n");
    screenGotoxy(start_x, 13);
    printf("  S: Acelerar a queda da peça                             \n");
    screenGotoxy(start_x, 14);
    printf("                                                          \n");

    // Exibe a mensagem dentro da borda
    screenGotoxy(start_x, 15);
    printf("                                                          \n");
    screenGotoxy(start_x, 16);
    printf("      Pressione ENTER para começar...                     \n");
    screenGotoxy(start_x, 17);
    printf("                                                          \n");

    // Espera o usuário pressionar Enter para continuar
    getchar();
}

// Função que verifica se a peça colidiu
int verColisao(Peca *peca) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[peca->tipo][peca->rodar][i][j]) {
                int x = peca->x + i;
                int y = peca->y + j;
                if (x < 0 || x >= WIDTH || y >= HEIGHT || board[x][y]) {
                    return 1;  // Colidiu com a borda ou outra peça
                }
            }
        }
    }
    return 0;  // Não houve colisão
}

// Função que coloca a peça no tabuleiro
void colocarPeca(Peca *peca) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[peca->tipo][peca->rodar][i][j]) {
                board[peca->x + i][peca->y + j] = 1;  // Marca o tabuleiro com a peça
            }
        }
    }
}

// Função que rotaciona a peça
void rodarPeca() {
    int rotacãoAntiga = currentPeca.rodar;
    currentPeca.rodar = (currentPeca.rodar + 1) % 4;  // Rotaciona para a próxima posição
    if (verColisao(&currentPeca)) {
        currentPeca.rodar = rotacãoAntiga;  // Se houver colisão, volta para a rotação anterior
    }
}

// Função que move a peça na horizontal
void moverPeca(int dx) {
    currentPeca.x += dx;  // Desloca a peça para a esquerda (dx=-1) ou para a direita (dx=1)
    if (verColisao(&currentPeca)) {
        currentPeca.x -= dx;  // desfaz o movimento
    }
}

// Função que desenha a peça na tela
void desenharPeca(Peca *peca) {
    screenSetColor(RED, BLACK);  // Define a cor para desenhar a peça
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[peca->tipo][peca->rodar][i][j]) {  // Verifica se a célula da peça está ativa
                screenGotoxy(SCRSTARTX + (peca->x + i) * BLOCK_SIZE, SCRSTARTY + peca->y + j);  // Calcula a posição na tela
                printf("[]");  // Desenha o bloco da peça
            }
        }
    }
}


void desenharTabuleiro() {
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
 
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 2, SCRSTARTY);
    printf("Nível: %d", nivel);
    screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE + 2, SCRSTARTY + 1);
    printf("Pontuação: %d", placar);
}

void removerLinhas() {
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
            placar += 100; // Adiciona 100 pontos por linha completa
        }
    }
}



// Função que salva o ranking em um arquivo
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

// Função que carrega o ranking do arquivo
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



// Função para salvar a pontuação no ranking
void salvarPontuacaoNoRanking(int placar) {
    char nome[50];

    printf("Digite seu nome para o ranking: ");
    fflush(stdout);  // Garante que a mensagem é exibida imediatamente
    fgets(nome, sizeof(nome), stdin); 
    nome[strcspn(nome, "\n")] = '\0';  

    //abre o arquivo para adicionar a pontuação
    FILE *rankingFile = fopen("ranking.txt", "a");
    if (rankingFile == NULL) {
        printf("Erro ao abrir o arquivo de ranking.\n");
        return;
    }

    // Adiciona o nome e a pontuação ao arquivo
    fprintf(rankingFile, "%s - %d\n", nome, placar);

    // Fecha o arquivo
    fclose(rankingFile);

    printf("Ranking Atualizado!\n");
}

void exibirRanking() {
    FILE *rankingFile = fopen("ranking.txt", "r");
    char linha[100];

    if (rankingFile == NULL) {
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

    // Exibe as linhas do arquivo centralizadas
    int linhaNum = 10;  // A partir da linha 10 para exibir o conteúdo
    while (fgets(linha, sizeof(linha), rankingFile) != NULL) {
        // Calcula o comprimento da linha e centraliza
        int comprimentoLinha = strlen(linha);
        int start_x = (MAXX - comprimentoLinha) / 2;
        screenGotoxy(start_x, linhaNum);
        printf("%s", linha);  // Exibe cada linha do ranking
        linhaNum++;  // Avança para a próxima linha
    }

    fclose(rankingFile);

    char msg[] = "Pressione ENTER para voltar pro menu principal...";
    int msgLength = strlen(msg);
    int start_x = (MAXX - msgLength) / 2;  // Calcula a posição de início para centralizar
    screenGotoxy(start_x, linhaNum + 1);  // Coloca a mensagem após as linhas do ranking
    printf("%s\n", msg);

    getchar(); 
}


// Função para exibir "Game Over" e voltar ao menu
void exibirGameOver() {
    system("clear"); 

    // Chama a função para desenhar as bordas
    desenharBordas();

    int titulo_comprimento = 72;  // Comprimento médio do título (ajuste conforme necessário)
    int start_x = (MAXX - titulo_comprimento) / 2;  // Calcula a posição de início para centralizar

    // Exibe o título ASCII centralizado
    screenGotoxy(start_x, 5);  // Posição de início para o título (ajuste a linha se necessário)
    printf(" ██████   █████  ███    ███ ███████      ██████  ██    ██ ███████ ██████  \n");
    screenGotoxy(start_x, 6);
    printf("██       ██   ██ ████  ████ ██          ██    ██ ██    ██ ██      ██   ██ \n");
    screenGotoxy(start_x, 7);
    printf("██   ███ ███████ ██ ████ ██ █████       ██    ██ ██    ██ █████   ██████  \n");
    screenGotoxy(start_x, 8);
    printf("██    ██ ██   ██ ██  ██  ██ ██          ██    ██  ██  ██  ██      ██   ██ \n");
    screenGotoxy(start_x, 9);
    printf(" ██████  ██   ██ ██      ██ ███████      ██████    ████   ███████ ██   ██ \n");

    // Exibe a mensagem de "game over" centralizada
    screenGotoxy((MAXX - 38) / 2, 12);
    printf("O Jogo Acabou! Você perdeu!\n");

   printf("\nPressione ENTER para voltar ao menu principal...\n");
    getchar();  // Aguarda o ENTER

}


void exibirMenu(int placar) {
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

        // Centraliza as opções do menu
        screenGotoxy((MAXX - 24) / 2, 10);  // Ajuste para centralizar "1. Salvar pontuação"
        printf("1. Salvar pontuação\n");

        screenGotoxy((MAXX - 24) / 2, 11);  // Ajuste para centralizar "2. Ver ranking"
        printf("2. Ver ranking\n");

        screenGotoxy((MAXX - 24) / 2, 12);  // Ajuste para centralizar "3. Sair"
        printf("3. Sair\n");

        // Centraliza o prompt para escolha
        screenGotoxy((MAXX - 24) / 2, 14);  // Ajuste para centralizar "Escolha uma opção: "
        printf("Escolha uma opção: ");
        fflush(stdout);  // Garante que a mensagem seja exibida

        // Lê a entrada como string
        if (fgets(input, sizeof(input), stdin) != NULL) {
            opcao = atoi(input);  // Converte para inteiro
        } else {
            opcao = 0;
        }

        switch (opcao) {
            case 1:
                if (!pontuacaoSalva) {  // Verifica se a pontuação já foi salva
                    salvarPontuacaoNoRanking(placar);
                    pontuacaoSalva = 1;  // Marca que a pontuação foi salva
                } else {
                    printf("A pontuação já foi salva!\n");
                    printf("Pressione ENTER para continuar...");
                    getchar();  // Aguarda o usuário pressionar ENTER
                }
                break;
            case 2:
                if (!rankingExibido) {  // Verifica se o ranking já foi exibido
                    exibirRanking();
                    rankingExibido = 1;  // Marca que o ranking foi exibido
                } else {
                    printf("O ranking já foi exibido!\n");
                    printf("Pressione ENTER para continuar...");
                    getchar();  // Aguarda o usuário pressionar ENTER
                }
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
    currentPeca.x = WIDTH / 2 - 2;
    currentPeca.y = 0;
    currentPeca.tipo = rand() % 7;
    currentPeca.rodar = 0;
    if (verColisao(&currentPeca)) {
        screenDestroy();
        exibirGameOver();
        exibirMenu(placar);
        saida(0);
    }
}

void derrubarPeca() {
    currentPeca.y++;
    if (verColisao(&currentPeca)) {
        currentPeca.y--;
        colocarPeca(&currentPeca);
        removerLinhas();
        gerarPeca();
    }
}

void processInput() {
    if (keyhit()) {
        int key = readch();
        switch (key) {
            case 'a': moverPeca(-1); break;
            case 'd': moverPeca(1); break;
            case 's': derrubarPeca(); break;
            case 'w': rodarPeca(); break;
        }
    }
}

int main() {
    exibirTelaInicial();
    exibirInstrucoes();
    srand(time(NULL));
    screenInit(1);
    keyboardInit();
    timerInit(500); // Inicializa o temporizador com intervalo de 500ms

    gerarPeca(); // Gera a primeira peça

    while (1) {
        processInput(); // Processa as entradas do usuário (movimentação e rotação da peça)
        
        if (timerTimeOver()) { // Verifica se o tempo acabou
            derrubarPeca(); // Faz a peça cair uma linha
        }

        desenharTabuleiro(); // Desenha o tabuleiro
        desenharPeca(&currentPeca); // Desenha a peça atual
        screenUpdate(); // Atualiza a tela
    }

    screenDestroy(); // Libera os recursos da tela
    keyboardDestroy(); // Finaliza a leitura do teclado
    return 0;
}
