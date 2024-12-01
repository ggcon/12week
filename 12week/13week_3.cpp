#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 24

char screenBuffer[WIDTH * HEIGHT * 2 + 1]; // null ���ڸ� ���� +1 �߰�

// ��ũ�� ���� �ʱ�ȭ
void bufferClear() {
    for (int i = 0; i < WIDTH * HEIGHT * 2; i++) {
        screenBuffer[i] = ' '; // �ʱⰪ�� ���� ���ڷ� ä��
    }
    screenBuffer[WIDTH * HEIGHT * 2] = '\0'; // ���ڿ� ���� null�� ����

    //Ŀ�� �����
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;  // Ŀ���� ����
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// ȭ�� �߾ӿ� "����" ���
void bufferMessage(const char* message) {
    int messageLength = strlen(message);
    int startX = (WIDTH - messageLength) / 2; // �߾ӿ� ��ġ
    int startY = HEIGHT / 2;                 // �߾� ��

    for (int i = 0; i < messageLength; i++) {
        int index = (startY * WIDTH + startX + i) * 2;
        screenBuffer[index] = message[i];
        screenBuffer[index + 1] = ' '; // �� ��° ����: ����
    }
}

// ȭ�� ���
void Render() {
    COORD coord = { 0, 0 };  // �ܼ� Ŀ���� (0, 0)���� �̵�
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    printf("%s", screenBuffer);
}

// ���� ����
void GameLoop() {
    bufferClear();          // ���� �ʱ�ȭ
    bufferMessage("HelloBuffer");     // "����" �޽��� ����
    
    while (1) {
        Render();                 // ���� ������
        Sleep(1000 / 60);         // 60FPS ����
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    GameLoop();
    return 0;
}
