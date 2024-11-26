//1번 문제
//게임 루프
//화면은 60프레임

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

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
void Update() {
	if (_kbhit()) {
		char key = _getch();
		printf("키 입력 : %c/n", key);

		if (key == 'q') {
			printf("종료\n");
			exit(0);
		}
	}
}

//게임루프 함수
void GameLoop() {
	Init();
	while (1) {
		Update();
		Render();
		//Sleep(1000 / 60); 이거 없으면 cpu 불탐
	}
}

//메인 함수
int main () {
	GameLoop();
	return 0;
}