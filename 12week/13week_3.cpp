#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 24

char screenBuffer[WIDTH * HEIGHT * 2 + 1]; // null 문자를 위해 +1 추가

// 스크린 버퍼 초기화
void bufferClear() {
    for (int i = 0; i < WIDTH * HEIGHT * 2; i++) {
        screenBuffer[i] = ' '; // 초기값은 공백 문자로 채움
    }
    screenBuffer[WIDTH * HEIGHT * 2] = '\0'; // 문자열 끝을 null로 설정

    //커서 숨기기
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;  // 커서를 숨김
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 화면 중앙에 "버퍼" 출력
void bufferMessage(const char* message) {
    int messageLength = strlen(message);
    int startX = (WIDTH - messageLength) / 2; // 중앙에 배치
    int startY = HEIGHT / 2;                 // 중앙 줄

    for (int i = 0; i < messageLength; i++) {
        int index = (startY * WIDTH + startX + i) * 2;
        screenBuffer[index] = message[i];
        screenBuffer[index + 1] = ' '; // 두 번째 문자: 공백
    }
}

// 화면 출력
void Render() {
    COORD coord = { 0, 0 };  // 콘솔 커서를 (0, 0)으로 이동
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    printf("%s", screenBuffer);
}

// 게임 루프
void GameLoop() {
    bufferClear();          // 버퍼 초기화
    bufferMessage("HelloBuffer");     // "버퍼" 메시지 설정
    
    while (1) {
        Render();                 // 버퍼 렌더링
        Sleep(1000 / 60);         // 60FPS 유지
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    GameLoop();
    return 0;
}
