#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include "matrix.h"

#define WIDTH 40
#define HEIGHT 24
#define M_PI 3.14159265358979323846

char screenBuffer[WIDTH * HEIGHT * 2 + 1]; // null ���ڸ� ���� +1 �߰�

// ��ũ�� ���� �ʱ�ȭ
void bufferClear() {
    for (int i = 0; i < WIDTH * HEIGHT * 2; i++) {
        screenBuffer[i] = ' '; // �ʱⰪ�� ���� ���ڷ� ä��
    }
    screenBuffer[WIDTH * HEIGHT * 2] = '\0'; // ���ڿ� ���� null�� ����

    // Ŀ�� �����
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;  // Ŀ���� ����
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// ȭ�� ���
void bufferDraw() {
    COORD coord = { 0, 0 };  // �ܼ� Ŀ���� (0, 0)���� �̵�
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%s", screenBuffer);
}

// ���� �׸��� �Լ�
void drawCircle(int centerX, int centerY, int radius) {
    // ������ 0������ 360������ ��ȭ��Ŵ
    for (int angle = 0; angle < 360; angle++) {
        // �������� ��ȯ
        float radian = angle * (M_PI / 180.0f);

        // ���� ��ǥ ���
        int x = centerX + (int)(radius * cosf(radian));
        int y = centerY + (int)(radius * sinf(radian));

        // ȭ�� ���ۿ� �� ���
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            int index = (y * WIDTH + x) * 2;
            screenBuffer[index] = '*';
            screenBuffer[index + 1] = ' '; // �� ��° ����: ����
        }
    }
}

// ���� ����
void GameLoop() {
    bufferClear();          // ���� �ʱ�ȭ

    // ������ 10�� ���� (20, 12) ��ġ�� �׸���
    drawCircle(20, 12, 10);     // ���� �߽� (20, 12), ������ 10

    while (1) {
        bufferDraw();                 // ���� ������
        Sleep(1000 / 60);         // 60FPS ����
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    GameLoop();
    return 0;
}
