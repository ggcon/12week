//1�� ����
//���� ����
//ȭ���� 60������
//�Էµ� �׿� ���缭

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//������Ʈ �Լ�
void Update() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 27) { // ESC Ű
            printf("����\n");
            exit(0);
        }
    }
}

//������ �Լ�
void Render() {
    system("cls");
    printf("������ ��...\n");
}

//���ӷ��� �Լ�
void GameLoop() { //���ӷ����� �����ض�
    const int fps = 60;
    const DWORD frameTime = 1000 / fps; // �� �����Ӵ� �ð� (�и��� ����)

    while (1) {
        DWORD start = GetTickCount(); // ���� �ð�(ms)

        Update();  // �Է� ó��
        Render();  // ȭ�� ���

        DWORD elapsed = GetTickCount() - start; // ������ ó�� �ð� ���
        if (elapsed < frameTime) {
            Sleep(frameTime - elapsed); // ���� �ð���ŭ ���
        }
    }
}

int main() {
    GameLoop();
    return 0;
}
