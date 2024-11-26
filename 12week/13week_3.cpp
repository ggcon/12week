#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 24

char screenBuffer[WIDTH * HEIGHT * 2]; 

void clearScreenBuffer() {
    // 버퍼 초기화
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            screenBuffer[(i * WIDTH + j) * 2] = ' '; // 첫 번째 char: 공백
            screenBuffer[(i * WIDTH + j) * 2 + 1] = ' '; // 두 번째 char: 공백
        }
    }
}

void Render() {
    COORD coord = { 0, 0 };  // (0, 0) 좌표로 커서 이동
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int index = (y * WIDTH + x) * 2;  // 픽셀당 2문자
            putchar(screenBuffer[index]);    // 첫 번째 문자
            putchar(screenBuffer[index + 1]); // 두 번째 문자
        }
        putchar('\n');  // 한 줄 끝
    }
}

void Update() {
    // 아무 동작 없이 바로 넘어감
}

void GameLoop() {
    clearScreenBuffer();
    Render(); // 한 번만 렌더링하여 화면에 표시

    while (1) {
        Update();
        Sleep(100); // CPU 사용률을 낮추기 위해 Sleep 추가
    }
}

int main() {
    GameLoop();
    return 0;
}
