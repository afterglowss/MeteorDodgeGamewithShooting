#pragma once
#include "meteor.h"
#include "game.h"

int highScore = 0;

// 무작위 운석 생성 함수
static void RespawnMeteor(Meteor* m, int index) {
    m->radius = (float)(rand() % 31 + 10);

    // 무작위 색상 저장(밝게)
    m->color = (Color){
    minBright + rand() % (256 - minBright),
    minBright + rand() % (256 - minBright),
    minBright + rand() % (256 - minBright),
    255
    };

    // 화면 밖 랜덤한 위치
    int edge = rand() % 4;
    switch (edge) {
    case 0: // TOP
        m->position = (Vector2){ rand() % SCREEN_WIDTH, -m->radius };
        break;
    case 1: // BOTTOM
        m->position = (Vector2){ rand() % SCREEN_WIDTH, SCREEN_HEIGHT + m->radius };
        break;
    case 2: // LEFT
        m->position = (Vector2){ -m->radius, rand() % SCREEN_HEIGHT };
        break;
    case 3: // RIGHT
        m->position = (Vector2){ SCREEN_WIDTH + m->radius, rand() % SCREEN_HEIGHT };
        break;
    }


    //화면 외부에서 내부로 랜덤한 방향
    float angle = ((float)(rand() % 360)) * DEG2RAD;
    Vector2 direction = (Vector2){
        cosf(angle),
        sinf(angle)
    };

    //속도
    float speed = 3;
    m->velocity = (Vector2){ direction.x * speed, direction.y * speed };
}


// 운석 초기화
void InitMeteors(Meteor* meteors) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < MAX_METEORS; i++) {
        RespawnMeteor(&meteors[i], i);
    }
}

//운석 위치 업데이트-17
void UpdateMeteors(Meteor* meteors, Player* playerRef, Bullet* bullets, int *score) {
    for (int i = 0; i < MAX_METEORS; i++) {
        meteors[i].position.x += meteors[i].velocity.x;
        meteors[i].position.y += meteors[i].velocity.y;

        if (meteors[i].position.x < -100 || meteors[i].position.x > SCREEN_WIDTH + 100 ||
            meteors[i].position.y < -100 || meteors[i].position.y > SCREEN_HEIGHT + 100) {
            RespawnMeteor(&meteors[i], i);  // 삭제된 meteor 재사용
        }
    }

    //운석-총알 충돌 처리: 20
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) continue;

        for (int j = 0; j < MAX_METEORS; j++) {
            if (CheckCollisionCircles(bullets[i].position, BULLET_RADIUS,
                meteors[j].position, meteors[j].radius)) {
                GenerateExplosion(meteors[j].position, meteors[j].color);
                bullets[i].active = false;
                // 총알과 운석이 충돌했을 경우 점수 100점 추가
                *score += 100;
                // 최고 점수보다 현재 점수가 높을 경우 최고 점수 갱신
                if (*score > highScore) highScore = *score;
                RespawnMeteor(&meteors[j], j);
                break;
            }
        }
    }

    // 무적 상태일 경우 충돌 검사 무시
    if (playerRef->isCollision) {
        double diffTime = GetTime() - playerRef->deathTime;
        if (diffTime < 2.0) return;  // 아직 무적 상태면 충돌 검사 건너뜀
        else playerRef->isCollision = false;  // 무적 시간 끝났으면 초기화
    }

    //운석-플레이어 충돌 처리: 19
    for (int i = 0; i < MAX_METEORS; i++) {
        if (CheckCollisionCircles(playerRef->position, PLAYER_SIZE / 2.0f,
            meteors[i].position, meteors[i].radius)) {
            GenerateExplosion(playerRef->position, RED);
            playerCollision(playerRef);
            playerRef->lives--;
            break;
        }
    }
}

// 운석 그리기
void DrawMeteors(Meteor* meteors) {
    for (int i = 0; i < MAX_METEORS; i++) {
        DrawCircleV(meteors[i].position, meteors[i].radius, meteors[i].color);
    }
}