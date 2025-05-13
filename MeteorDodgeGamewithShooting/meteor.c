#include "meteor.h"

static Meteor meteors[MAX_METEORS];
static Color meteorColors[MAX_METEORS];
#define minBright 100

// 무작위 운석 생성 함수
static void RepawnMeteor(int index) {
    float radius = (float)(rand() % 31 + 10);
    meteors[index].radius = radius;

    // 무작위 색상 저장(밝게)
    meteorColors[index] = (Color){
    minBright + rand() % (256 - minBright),
    minBright + rand() % (256 - minBright),
    minBright + rand() % (256 - minBright),
    255
    };

    // 화면 밖 랜덤한 위치
    int edge = rand() % 4;
    switch (edge) {
    case 0: // Top
        meteors[index].position = (Vector2){ rand() % SCREEN_WIDTH, -radius };
        break;
    case 1: // Bottom
        meteors[index].position = (Vector2){ rand() % SCREEN_WIDTH, SCREEN_HEIGHT + radius };
        break;
    case 2: // Left
        meteors[index].position = (Vector2){ -radius, rand() % SCREEN_HEIGHT };
        break;
    case 3: // Right
        meteors[index].position = (Vector2){ SCREEN_WIDTH + radius, rand() % SCREEN_HEIGHT };
        break;
    }


    //화면 외부에서 내부로 랜덤한 방향
    float angle = ((float)(rand() % 360)) * DEG2RAD;
    Vector2 direction = (Vector2){
        cosf(angle),
        sinf(angle)
    };

    //속도
    float speed = 5;
    meteors[index].velocity = (Vector2){direction.x * speed, direction.y * speed};
}


// 운석 초기화
void InitMeteors() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < MAX_METEORS; i++) {
        RepawnMeteor(i);
    }
}

//운석 위치 업데이트-17
void UpdateMeteors() {
    for (int i = 0; i < MAX_METEORS; i++) {
        meteors[i].position.x += meteors[i].velocity.x;
        meteors[i].position.y += meteors[i].velocity.y;

        if (meteors[i].position.x < -100 || meteors[i].position.x > SCREEN_WIDTH + 100 ||
            meteors[i].position.y < -100 || meteors[i].position.y > SCREEN_HEIGHT + 100) {
            RepawnMeteor(i);  // 기존 meteor 재사용
        }
    }
}

// 운석 그리기
void DrawMeteors() {
    for (int i = 0; i < MAX_METEORS; i++) {
        DrawCircleV(meteors[i].position, meteors[i].radius, meteorColors[i]);
    }
}
