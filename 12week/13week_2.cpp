//1�� ����
//���� ����
//ȭ���� 60������
//60���� 1�ʷ� ��ŸŸ�� �����
//cpu�� ��Ÿ�� �ʰ� ���� �ð��� sleep()���� ����

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

//�ʱ�ȭ �Լ�
void Init() {
	system("cls");
	printf("�ʱ�ȭ"\n);
}

//������ �Լ�
void Render() {
	printf("������\n");
}

//������Ʈ �Լ�(Ű �Է��� ����)
void Update(float deltaTime) {
	if (_kbhit()) {
		char key = _getch();
		printf("Ű �Է� : %c (delta_time : %.2fms)\n", key, deltaTime);

		if (key == 'q') {
			printf("����\n");
			exit(0);
		}
	}
}

//���ӷ��� �Լ�
void GameLoop() {
	Init();

	clock_t lastTime = clock();
	const int targetFrameTime = 1000 / 60;

	while (1) {
		clock_t currentTime = clock();
		float deltaTime = (float)(currentTime - lastTime) * 1000 / CLOCKS_PER_SEC;

		Update(deltaTime);
		Render();
		
		int sleepTime = targetFrameTime - deltaTime;
		if (sleepTime > 0) {
			Sleep(sleepTime);
		}
	}
}

//���� �Լ�
int main() {
	GameLoop();
	return 0;
}