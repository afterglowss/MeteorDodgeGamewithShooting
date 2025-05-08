#include "meteor.h"

static Meteor meteors[MAX_METEORS];
static Color meteorColors[MAX_METEORS];
#define minBright 100

// 무작위 운석 생성 함수
static Meteor CreateRandomMeteor(int index) {
    Meteor m;

    // 반지름: 10~40
    m.radius = (float)(rand() % 31 + 10);

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
        m.position = (Vector2){ rand() % SCREEN_WIDTH, -m.radius };
        break;
    case 1: // Bottom
        m.position = (Vector2){ rand() % SCREEN_WIDTH, SCREEN_HEIGHT + m.radius };
        break;
    case 2: // Left
        m.position = (Vector2){ -m.radius, rand() % SCREEN_HEIGHT };
        break;
    case 3: // Right
        m.position = (Vector2){ SCREEN_WIDTH + m.radius, rand() % SCREEN_HEIGHT };
        break;
    }

    // 화면 중심 향하는 방향
    Vector2 target = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    Vector2 direction = Vector2Normalize((Vector2) { target.x - m.position.x, target.y - m.position.y });


    return m;
}

// 운석 초기화
void InitMeteors() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < MAX_METEORS; i++) {
        meteors[i] = CreateRandomMeteor(i);
    }
}


// 운석 그리기
void DrawMeteors() {
    for (int i = 0; i < MAX_METEORS; i++) {
        DrawCircleV(meteors[i].position, meteors[i].radius, meteorColors[i]);
    }
}
