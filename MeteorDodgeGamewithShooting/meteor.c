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

    //화면 외부에서 내부로 랜덤한 방향
    float angle = ((float)(rand() % 360)) * DEG2RAD;
    Vector2 direction = (Vector2){
        cosf(angle),
        sinf(angle)
    };

    // 속도
    float speed = 5;
    m.velocity = (Vector2){ direction.x * speed, direction.y * speed };

    return m;
}

// 운석 초기화
void InitMeteors() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < MAX_METEORS; i++) {
        meteors[i] = CreateRandomMeteor(i);
    }
}

//운석 위치 업데이트-17
void UpdateMeteors() {
    for (int i = 0; i < MAX_METEORS; i++) {
        meteors[i].position.x += meteors[i].velocity.x;
        meteors[i].position.y += meteors[i].velocity.y;

        // 화면을 벗어나면 다시 생성
        if (meteors[i].position.x < -100 || meteors[i].position.x > SCREEN_WIDTH + 100 ||
            meteors[i].position.y < -100 || meteors[i].position.y > SCREEN_HEIGHT + 100) {
            meteors[i] = CreateRandomMeteor(i);
        }
    }
}

// 운석 그리기
void DrawMeteors() {
    for (int i = 0; i < MAX_METEORS; i++) {
        DrawCircleV(meteors[i].position, meteors[i].radius, meteorColors[i]);
    }
}
