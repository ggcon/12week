#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 24
#define PI 3.14159265358979323846

char screenBuffer[WIDTH * HEIGHT * 2]; // 스크린 버퍼 (1픽셀 = 2문자)

// 2D 벡터 구조체
typedef struct {
    float x, y, w; // x, y 좌표와 동차 좌표 w
} vec3;

// 3x3 행렬 구조체
typedef struct {
    float m[3][3]; // 3x3 행렬
} Matrix3x3;

// 전역 변수: 태양, 지구, 달 중심 좌표
vec3 sun = { 20.0f, 12.0f, 1.0f };
vec3 earth = { 32.0f, 12.0f, 1.0f }; // 초기 위치
vec3 moon = { 36.0f, 12.0f, 1.0f };  // 초기 위치

// 태양, 지구, 달의 공전 및 자전 주기
const float SUN_ROTATION_SPEED = -360.0f / 3000;  // 3초 1바퀴 (반시계)
const float EARTH_ROTATION_SPEED = 360.0f / 2000; // 2초 1바퀴 (시계)
const float EARTH_ORBIT_SPEED = 360.0f / 3000;    // 3초 1바퀴 (시계)
const float MOON_ROTATION_SPEED = 360.0f / 1000;  // 1초 1바퀴 (시계)
const float MOON_ORBIT_SPEED = -360.0f / 2000;    // 2초 1바퀴 (반시계)

// 단위 행렬 초기화
void initIdentityMatrix(Matrix3x3* mat) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            mat->m[i][j] = (i == j) ? 1 : 0;
}

// 회전 행렬 생성
Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    float radian = angle * PI / 180;
    mat.m[0][0] = cos(radian);
    mat.m[0][1] = -sin(radian);
    mat.m[1][0] = sin(radian);
    mat.m[1][1] = cos(radian);
    return mat;
}

// 이동 행렬 생성
Matrix3x3 createTranslationMatrix(float tx, float ty) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    mat.m[0][2] = tx;
    mat.m[1][2] = ty;
    return mat;
}

// 크기 조정 행렬 생성
Matrix3x3 createScaleMatrix(float sx, float sy) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    mat.m[0][0] = sx;
    mat.m[1][1] = sy;
    return mat;
}

// 행렬과 벡터 곱셈
vec3 Mul(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = b.m[0][0] * a.x + b.m[0][1] * a.y + b.m[0][2] * a.w;
    result.y = b.m[1][0] * a.x + b.m[1][1] * a.y + b.m[1][2] * a.w;
    result.w = a.w;
    return result;
}

// 화면 초기화
void clearScreenBuffer() {
    for (int i = 0; i < WIDTH * HEIGHT * 2; i++) {
        screenBuffer[i] = ' '; // 모든 버퍼를 공백으로 초기화
    }
    //커서 숨기기
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;  // 커서를 숨김
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 스크린 버퍼에 텍스트 기록
void writeToBuffer(int x, int y, const char* text) {
    int len = strlen(text); // 문자열 길이 확인
    for (int i = 0; i < len; i++) {
        int index = (y * WIDTH + x + i) * 2; // 스크린 버퍼 인덱스 계산
        if (index >= 0 && index < WIDTH * HEIGHT * 2) { // 범위 내 확인
            screenBuffer[index] = text[i]; // 첫 번째 문자 삽입
            screenBuffer[index + 1] = text[i]; // 두 번째 문자 삽입
        }
    }
}

// 스크린 버퍼 내용 출력
void Draw() {
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

// 태양 그리기 (삼각형)
void drawSun(float angle) {
    vec3 vertices[3] = { // 삼각형 꼭짓점 정의
        {0.0f, -5.0f, 1.0f},
        {-4.33f, 2.5f, 1.0f},
        {4.33f, 2.5f, 1.0f}
    };

    Matrix3x3 rotation = createRotationMatrix(angle); // 회전 행렬 생성

    for (int i = 0; i < 3; i++) {
        vec3 rotatedVertex = Mul(vertices[i], rotation); // 회전 적용
        rotatedVertex.x += sun.x; // 태양 중심으로 이동
        rotatedVertex.y += sun.y;
        writeToBuffer((int)(rotatedVertex.x), (int)(rotatedVertex.y), "S"); // 버퍼에 출력
    }
}

// 지구 그리기 (정사각형)
void drawEarth(float angle) {
    // 지구의 공전 (태양을 기준으로)
    vec3 earthOrbit = Mul(earth, createRotationMatrix(angle));
    earthOrbit.x = sun.x + 12.0f * cos(angle * PI / 180);
    earthOrbit.y = sun.y + 12.0f * sin(angle * PI / 180);
    
    // 사각형의 4개 꼭짓점 (크기 3)
    vec3 vertices[4] = {
        {-1.0f, -1.0f, 1.0f},  // 왼쪽 아래
        {1.0f, -1.0f, 1.0f},   // 오른쪽 아래
        {1.0f, 1.0f, 1.0f},    // 오른쪽 위
        {-1.0f, 1.0f, 1.0f}    // 왼쪽 위
    };

    Matrix3x3 rotation = createRotationMatrix(angle); // 회전 행렬 생성

    for (int i = 0; i < 4; i++) {
        vec3 rotatedVertex = Mul(vertices[i], rotation); // 회전 적용
        rotatedVertex.x += earthOrbit.x; // 중심 이동
        rotatedVertex.y += earthOrbit.y;
        writeToBuffer((int)(rotatedVertex.x), (int)(rotatedVertex.y), "E"); // 버퍼에 기록
    }
}

// 달 그리기 (원형) 지름 3
void drawMoon(float moonAngle, float earthAngle) {
    vec3 earthOrbit = { sun.x + 12.0f * cos(earthAngle * PI / 180), sun.y + 12.0f * sin(earthAngle * PI / 180), 1.0f };

    //지구와의 간격
    float moonX = earthOrbit.x + 4.0f * cos(moonAngle * PI / 180);
    float moonY = earthOrbit.y + 4.0f * sin(moonAngle * PI / 180);

    //달 지름
    const float radius = 0.75f;

    //자전
    for (float theta = 0; theta < 360; theta += 10) {
        float x = radius * cos(theta * PI / 180);
        float y = radius * sin(theta * PI / 180);
        writeToBuffer((int)(moonX + x), (int)(moonY + y), "M");
    }
}

// 태양계 그리기
void drawScene(float sunAngle, float earthAngle, float moonAngle) {
    clearScreenBuffer();
    drawSun(sunAngle);
    drawEarth(earthAngle);
    drawMoon(moonAngle, earthAngle);
    Draw();
}

//학번이름 출력
void printTextCentered(const char* text) {
    const char* message = text;
    int len = strlen(text);
    int startX = WIDTH;  // 픽셀 단위로 중앙 위치 계산
    int startY = HEIGHT;

    // 화면 버퍼를 초기화한 후 텍스트 삽입
    clearScreenBuffer();

    for (int i = 0; i <= len; i++) {
        int index = (startY * WIDTH + startX + i) * 1;  // 픽셀당 2문자
        screenBuffer[index] = message[i];       // 첫 번째 문자
        screenBuffer[index + 1] = message[i];  // 두 번째 문자
    }

    // 화면에 버퍼 출력
    Draw();
}

int main() {
    // 스크린 버퍼 초기화
    clearScreenBuffer();
    
    //페이즈, 공전각도 초기화
    int phase = 0;
    float sunAngle = 0.0f, earthAngle = 0.0f, moonAngle = 0.0f;

    printTextCentered("학번: 20180746 이름: 최성현");

    while (1) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 27) break;         // ESC로 종료
            if (key == ' ') phase = (phase + 1) % 3;  // 스페이스바로 상태 전환
        }

        if (phase == 0) continue;         // 학번/이름 표시
        
        else if (phase == 1) {
            clearScreenBuffer();
            drawScene(0, 0, 0); // 행성의 초기 위치 출력
            Draw();
        }
        else if (phase == 2) {
            drawScene(sunAngle, earthAngle, moonAngle);
            sunAngle += SUN_ROTATION_SPEED * 100;
            if (sunAngle <= -360.0f) sunAngle += 360.0f;
            earthAngle += EARTH_ORBIT_SPEED * 100;
            moonAngle += MOON_ORBIT_SPEED * 100;
        }

        Sleep(100); // 100ms 대기 (프레임 제한)
    }

    return 0;
}


