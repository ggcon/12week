#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 24

char screenBuffer[WIDTH * HEIGHT * 2 + 1]; // +1은 null 문자용

void Init() {
    // 버퍼 초기화
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            screenBuffer[(i * WIDTH + j) * 2] = ' '; // 첫 번째 char: 공백
            screenBuffer[(i * WIDTH + j) * 2 + 1] = ' '; // 두 번째 char: 공백
        }
    }
    screenBuffer[WIDTH * HEIGHT * 2] = '\0'; // 문자열 끝 표시

    // "렌더링..." 문구 추가
    const char* message = "렌더링...";
    for (int i = 0; message[i] != '\0'; i++) {
        screenBuffer[i * 2] = message[i];
        screenBuffer[i * 2 + 1] = ' '; // 두 번째 char도 공백으로
    }
}

void Render() {
    printf("%s\n", screenBuffer);
}

void Update() {
    // 아무 동작 없이 바로 넘어감
}

void GameLoop() {
    Init();
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
