//1�� ����
//���� ����
//ȭ���� 60������

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

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
void Update() {
	if (_kbhit()) {
		char key = _getch();
		printf("Ű �Է� : %c/n", key);

		if (key == 'q') {
			printf("����\n");
			exit(0);
		}
	}
}

//���ӷ��� �Լ�
void GameLoop() {
	Init();
	while (1) {
		Update();
		Render();
		//Sleep(1000 / 60); �̰� ������ cpu ��Ž
	}
}

//���� �Լ�
int main () {
	GameLoop();
	return 0;
}