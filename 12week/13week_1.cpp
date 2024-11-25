//1번 문제
//게임 루프
//화면은 60프레임

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

		if (key == 'q') {
			printf("종료\n");
			exit(0);
		}
	}
}

void GameLoop() {
	Initialize();

	clock_t start_time = clock(); // 현재 시간을 기록
	while (1) {
		Update(); // Update는 계속 호출하여 키 입력을 처리
		// 현재 시간과 시작 시간의 차이를 확인하여 1초마다 렌더링
		if ((clock() - start_time) >= CLOCKS_PER_SEC) { // CLOCKS_PER_SEC는 1초
			Render();
			start_time = clock(); // 시간을 초기화하여 다음 1초를 기다림
		}
	}
}


int main() {
	GameLoop();
	return 0;
}
