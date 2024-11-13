int main() {
    exibirTelaInicial();
    exibirInstrucoes();
    srand(time(NULL));
    screenInit(1); // Chama screenInit passando 1 para desenhar a borda
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
    return 0;
}
