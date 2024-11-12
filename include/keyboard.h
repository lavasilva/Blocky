#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

void keyboardInit();
void keyboardDestroy();
int keyhit();  // Verifica se uma tecla foi pressionada
int readch();  // Lê a tecla pressionada

#endif /* __KEYBOARD_H__ */
