//1번 문제
//게임 루프
//화면은 60프레임
//60분의 1초로 델타타임 만들기
//cpu가 불타지 않게 남은 시간은 sleep()으로 쉬게


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

void Initialize() {
	system("cls");
	printf("초기화...\n");
}

void Render() {
	printf("렌더링...\n");
}

void Update() {
	if (_kbhit()) {
		char key = _getch();
		printf("키 입력 : %c\n", key);

		if (key == '27') {
			printf("종료\n");
			exit(0);
		}
	}
}

void Loop() {
	Initialize();

	// 프레임 타이머
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