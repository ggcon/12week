//1�� ����
//���� ����
//ȭ���� 60������
//60���� 1�ʷ� ��ŸŸ�� �����
//cpu�� ��Ÿ�� �ʰ� ���� �ð��� sleep()���� ����


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

void Initialize() {
	system("cls");
	printf("�ʱ�ȭ...\n");
}

void Render() {
	printf("������...\n");
}

void Update() {
	if (_kbhit()) {
		char key = _getch();
		printf("Ű �Է� : %c\n", key);

		if (key == '27') {
			printf("����\n");
			exit(0);
		}
	}
}

void Loop() {
	Initialize();

	// ������ Ÿ�̸�
	clock_t lastTime = clock();
	int fps = 60;
	double frameTime = 1000.0 / fps;

	clock_t start_time = clock();
	while (1) {
		Update();

		if ((clock() - start_time) >= CLOCKS_PER_SEC) {
			Render();
			start_time = clock();
			Sleep(16);
		}

	}
}

int main() {
	Loop();
	return 0;
}