#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 24

char screenBuffer[WIDTH * HEIGHT * 2 + 1]; // +1�� null ���ڿ�

void Init() {
    // ���� �ʱ�ȭ
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            screenBuffer[(i * WIDTH + j) * 2] = ' '; // ù ��° char: ����
            screenBuffer[(i * WIDTH + j) * 2 + 1] = ' '; // �� ��° char: ����
        }
    }
    screenBuffer[WIDTH * HEIGHT * 2] = '\0'; // ���ڿ� �� ǥ��

    // "������..." ���� �߰�
    const char* message = "������...";
    for (int i = 0; message[i] != '\0'; i++) {
        screenBuffer[i * 2] = message[i];
        screenBuffer[i * 2 + 1] = ' '; // �� ��° char�� ��������
    }
}

void Render() {
    printf("%s\n", screenBuffer);
}

void Update() {
    // �ƹ� ���� ���� �ٷ� �Ѿ
}

void GameLoop() {
    Init();
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
