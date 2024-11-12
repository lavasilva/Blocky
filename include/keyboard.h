#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

void keyboardInit();
void keyboardDestroy();
int keyboardHit();  // Verifica se uma tecla foi pressionada
int keyboardRead(); // Lê a tecla pressionada

#endif /* __KEYBOARD_H__ */
