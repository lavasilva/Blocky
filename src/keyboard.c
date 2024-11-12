#include <termios.h>
#include <unistd.h>
#include "keyboard.h"

static struct termios initialSettings, newSettings;
static int peekCharacter = -1;

void keyboardInit() {
    tcgetattr(0, &initialSettings);
    newSettings = initialSettings;
    newSettings.c_lflag &= ~ICANON; // Desabilita o modo canônico
    newSettings.c_lflag &= ~ECHO;   // Desabilita o eco
    newSettings.c_lflag &= ~ISIG;   // Desabilita os sinais
    newSettings.c_cc[VMIN] = 1;
    newSettings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &newSettings);
}

void keyboardDestroy() {
    tcsetattr(0, TCSANOW, &initialSettings);
}

int keyboardHit() {  // Função para verificar se uma tecla foi pressionada
    unsigned char ch;
    int nread;

    if (peekCharacter != -1)
        return 1;

    newSettings.c_cc[VMIN] = 0;
    tcsetattr(0, TCSANOW, &newSettings);
    nread = read(0, &ch, 1);
    newSettings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &newSettings);

    if (nread == 1) {
        peekCharacter = ch;
        return 1;
    }

    return 0;
}

int keyboardRead() {  // Função para ler a tecla pressionada
    char ch;

    if (peekCharacter != -1) {
        ch = peekCharacter;
        peekCharacter = -1;
        return ch;
    }
    read(0, &ch, 1);
    return ch;
}
