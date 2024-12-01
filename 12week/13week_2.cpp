//1번 문제
//게임 루프
//화면은 60프레임
//입력도 그에 맞춰서

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

//초기화 함수
void Init() {
    printf("초기화\n");
}

//렌더링 함수
void Render() {
    system("cls");
    printf("렌더링 60 프레임\n");
}

//업데이트 함수(키 입력을 받음)
void Update() {
    if (_kbhit()) {
        char key = _getch();
        printf("키 입력 : %c\n", key);

        if (key == 27) {
            printf("종료\n");
            exit(0);
        }
    }
}

//게임루프 함수// 교수님 쳌 
void GameLoop() {
    Init();


    clock_t lastTime = clock(); // 이전 프레임 시간 기록
    int fps = 60;               // 목표 FPS
    double frameTime = 1000.0 / fps; // 한 프레임당 소요 시간 (밀리초 단위)

    //반복문 시작
    while (1) {
        clock_t currentTime = clock(); // 현재 시간
        double elapsedTime = (double)(currentTime - lastTime) / CLOCKS_PER_SEC * 1000; // 경과 시간(ms)

        if (elapsedTime >= frameTime) {
            lastTime = currentTime; // 이전 프레임 시간 갱신

            Update(); // 입력 처리
            Render(); // 렌더링
        }
        else {
            // 남은 시간을 Sleep으로 대기 (CPU 부하를 줄이기 위해)
            Sleep((DWORD)(frameTime - elapsedTime));
        }
    }
}


//메인 함수
int main() {
    GameLoop();
    return 0;
}