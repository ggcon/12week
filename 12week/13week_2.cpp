//1�� ����
//���� ����
//ȭ���� 60������
//�Էµ� �׿� ���缭

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

//�ʱ�ȭ �Լ�
void Init() {
    printf("�ʱ�ȭ\n");
}

//������ �Լ�
void Render() {
    system("cls");
    printf("������ 60 ������\n");
}

//������Ʈ �Լ�(Ű �Է��� ����)
void Update() {
    if (_kbhit()) {
        char key = _getch();
        printf("Ű �Է� : %c\n", key);

        if (key == 27) {
            printf("����\n");
            exit(0);
        }
    }
}

//���ӷ��� �Լ�// ������ �n 
void GameLoop() {
    Init();


    clock_t lastTime = clock(); // ���� ������ �ð� ���
    int fps = 60;               // ��ǥ FPS
    double frameTime = 1000.0 / fps; // �� �����Ӵ� �ҿ� �ð� (�и��� ����)

    //�ݺ��� ����
    while (1) {
        clock_t currentTime = clock(); // ���� �ð�
        double elapsedTime = (double)(currentTime - lastTime) / CLOCKS_PER_SEC * 1000; // ��� �ð�(ms)

        if (elapsedTime >= frameTime) {
            lastTime = currentTime; // ���� ������ �ð� ����

            Update(); // �Է� ó��
            Render(); // ������
        }
        else {
            // ���� �ð��� Sleep���� ��� (CPU ���ϸ� ���̱� ����)
            Sleep((DWORD)(frameTime - elapsedTime));
        }
    }
}


//���� �Լ�
int main() {
    GameLoop();
    return 0;
}