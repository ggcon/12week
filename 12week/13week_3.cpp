#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 24

char screenBuffer[WIDTH * HEIGHT * 2]; 

void clearScreenBuffer() {
    // ���� �ʱ�ȭ
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            screenBuffer[(i * WIDTH + j) * 2] = ' '; // ù ��° char: ����
            screenBuffer[(i * WIDTH + j) * 2 + 1] = ' '; // �� ��° char: ����
        }
    }
}

void Render() {
    COORD coord = { 0, 0 };  // (0, 0) ��ǥ�� Ŀ�� �̵�
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int index = (y * WIDTH + x) * 2;  // �ȼ��� 2����
            putchar(screenBuffer[index]);    // ù ��° ����
            putchar(screenBuffer[index + 1]); // �� ��° ����
        }
        putchar('\n');  // �� �� ��
    }
}

void Update() {
    // �ƹ� ���� ���� �ٷ� �Ѿ
}

void GameLoop() {
    clearScreenBuffer();
    Render(); // �� ���� �������Ͽ� ȭ�鿡 ǥ��

    while (1) {
        Update();
        Sleep(100); // CPU ������ ���߱� ���� Sleep �߰�
    }
}

int main() {
    GameLoop();
    return 0;
}
