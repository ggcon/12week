#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include "matrix.h"

#define WIDTH 40
#define HEIGHT 24
#define M_PI 3.14159265358979323846

char screenBuffer[WIDTH * HEIGHT * 2 + 1]; // null 문자를 위해 +1 추가

// 스크린 버퍼 초기화
void bufferClear() {
    for (int i = 0; i < WIDTH * HEIGHT * 2; i++) {
        screenBuffer[i] = ' '; // 초기값은 공백 문자로 채움
    }
    screenBuffer[WIDTH * HEIGHT * 2] = '\0'; // 문자열 끝을 null로 설정

    // 커서 숨기기
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;  // 커서를 숨김
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 화면 출력
void bufferDraw() {
    COORD coord = { 0, 0 };  // 콘솔 커서를 (0, 0)으로 이동
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%s", screenBuffer);
}

// 원을 그리는 함수
void drawCircle(int centerX, int centerY, int radius) {
    // 각도를 0도부터 360도까지 변화시킴
    for (int angle = 0; angle < 360; angle++) {
        // 라디안으로 변환
        float radian = angle * (M_PI / 180.0f);

        // 원의 좌표 계산
        int x = centerX + (int)(radius * cosf(radian));
        int y = centerY + (int)(radius * sinf(radian));

        // 화면 버퍼에 점 찍기
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            int index = (y * WIDTH + x) * 2;
            screenBuffer[index] = '*';
            screenBuffer[index + 1] = ' '; // 두 번째 문자: 공백
        }
    }
}

// 게임 루프
void GameLoop() {
    bufferClear();          // 버퍼 초기화

    // 반지름 10인 원을 (20, 12) 위치에 그리기
    drawCircle(20, 12, 10);     // 원의 중심 (20, 12), 반지름 10

    while (1) {
        bufferDraw();                 // 버퍼 렌더링
        Sleep(1000 / 60);         // 60FPS 유지
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    GameLoop();
    return 0;
}
