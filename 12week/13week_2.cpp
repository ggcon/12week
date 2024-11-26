//1번 문제
//게임 루프
//화면은 60프레임
//60분의 1초로 델타타임 만들기
//cpu가 불타지 않게 남은 시간은 sleep()으로 쉬게

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

//초기화 함수
void Init() {
	system("cls");
	printf("초기화"\n);
}

//렌더링 함수
void Render() {
	printf("렌더링\n");
}

//업데이트 함수(키 입력을 받음)
void Update(float deltaTime) {
	if (_kbhit()) {
		char key = _getch();
		printf("키 입력 : %c (delta_time : %.2fms)\n", key, deltaTime);

		if (key == 'q') {
			printf("종료\n");
			exit(0);
		}
	}
}

//게임루프 함수
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

//메인 함수
int main() {
	GameLoop();
	return 0;
}