//3����
//1�� ���� 3a��
//2�� ���� 2a��,
//3�� ���� a��
//���κп� �ָ�
//������ ��ħ(1�ȼ���)
//���� 1 ���Ǵ� 3�ȼ�
//15�� 75�� �����ִ�.
//��ǥ�� ���϶�(�ָԸ� �׷���)
// 
//369���� 

//40 x 24 ��ũ������

//1�� ����
//���� ����
//ȭ���� 60������

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
	
}

void Update() {
	if (_kbhit()) {
		char key = _getch();
		printf("Ű �Է� : %c\n", key);

		if (key == 'q') {
			printf("����\n");
			exit(0);
		}
	}
}

void GameLoop() {
	Initialize();

	clock_t start_time = clock(); // ���� �ð��� ���
	while (1) {
		Update(); // Update�� ��� ȣ���Ͽ� Ű �Է��� ó��
		// ���� �ð��� ���� �ð��� ���̸� Ȯ���Ͽ� 1�ʸ��� ������
		if ((clock() - start_time) >= CLOCKS_PER_SEC) { // CLOCKS_PER_SEC�� 1��
			Render();
			start_time = clock(); // �ð��� �ʱ�ȭ�Ͽ� ���� 1�ʸ� ��ٸ�
		}
	}
}


int main() {
	GameLoop();
	return 0;
}
