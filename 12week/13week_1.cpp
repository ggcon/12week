//1번 문제
//게임 루프
//화면은 60프레임
//입력도 그에 맞춰서

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void Update() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 27) { // ESC 키
            printf("종료\n");
            exit(0);
        }
    }
}

void Render() {
    system("cls");
    printf("렌더링 중...\n");
}

void GameLoop() {
    const int fps = 60;
    const DWORD frameTime = 1000 / fps; // 한 프레임당 시간 (밀리초 단위)

    while (1) {
        DWORD start = GetTickCount(); // 현재 시간(ms)

        Update();  // 입력 처리
        Render();  // 화면 출력

        DWORD elapsed = GetTickCount() - start; // 프레임 처리 시간 계산
        if (elapsed < frameTime) {
            Sleep(frameTime - elapsed); // 남은 시간만큼 대기
        }
    }
}

int main() {
    GameLoop();
    return 0;
}
