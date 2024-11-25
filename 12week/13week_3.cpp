//80, 24 ������ ��ũ������
//�ѹ��� printf �� ������ �׷���
//���۸� 1���� �迭�� ���
//printf�� string���� ���

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>  // _kbhit(), _getch() �Լ� ����� ���� ���
#include <windows.h>

#define WIDTH 80
#define HEIGHT 24

// ���� ������ ��ũ�� ���� ����
char screenBuffer[WIDTH * HEIGHT];
char clearBuffer[WIDTH * HEIGHT];   // Ŭ���� ���� (���� ���)

int screenWidth = WIDTH;
int screenHeight = HEIGHT;

// ȭ�� �ʱ�ȭ �Լ�
void Init() {
    // ȭ�� ���۸� �� �������� �ʱ�ȭ
    for (int i = 0; i < screenWidth * screenHeight; i++) {
        screenBuffer[i] = ' ';  // ���� ���, ���� ����
        clearBuffer[i] = ' ';   // Ŭ���� ���۵� ���� ������� �ʱ�ȭ
    }

    //Ŀ�� �����
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;  // Ŀ���� ����
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// ȭ���� �׸��� �Լ�
void Draw(char* Buffer) {
    //0,0���� �̵�
    COORD coord = { 0, 0 };  // ��ǥ (0, 0)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // ��ũ�� ���� ���
    for (int y = 0; y < screenHeight; y++) {
        for (int x = 0; x < screenWidth; x++) {
            putchar(Buffer[y * screenWidth + x]);
        }
        putchar('\n');
    }
}

// ȭ�� ������Ʈ �Լ�
void Update() {
    // "������" �ؽ�Ʈ�� ȭ�� �߾ӿ� ���
    const char* message = "������";
    int msgLen = 6;  // "������"�� ����

    // �߾� ��ġ ���
    int startX = (screenWidth - msgLen) / 2;
    int startY = screenHeight / 2;

    // ȭ�� ���ۿ� �޽��� ���� (����� �ؽ�Ʈ�� ǥ��)
    for (int i = 0; i < msgLen; i++) {
        screenBuffer[(startY * screenWidth) + (startX + i)] = message[i];
    }
}

// ���� ����
int main() {
    // ���� �ʱ�ȭ
    Init();

    // ������ Ÿ�̸�
    clock_t lastTime = clock();
    int fps = 60;
    double frameTime = 1000.0 / fps;

    while (1) {
        // ESC Ű�� �������� Ȯ��
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 27) {  // ESC Ű�� ������ ���� ����
                break;
            }
        }

        // ���� �ð� ���
        clock_t now = clock();
        double deltaTime = (double)(now - lastTime) / CLOCKS_PER_SEC * 1000.0;

        // ������ ���� (60fps ����)
        if (deltaTime >= frameTime) {
            lastTime = now;

            // ���� ������Ʈ
            Update();

            // ȭ�� �׸���
            //Draw(clearBuffer);
            Draw(screenBuffer);
        }
    }

    return 0;
}