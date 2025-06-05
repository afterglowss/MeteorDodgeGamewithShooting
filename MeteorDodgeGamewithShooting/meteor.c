#pragma once
#include "meteor.h"
#include "game.h"

int highScore = 0;
int checkScore = 0;         // 1000점마다 운석 속도를 올리기 위한
float speed;

// 무작위 운석 생성 함수
void RespawnMeteor(Meteor* m, int index) {
    m->radius = (float)(rand() % 31 + 10);

    // 무작위 색상 저장(밝게)
    m->color = (Color){
    MIN_BRIGHT + rand() % (256 - MIN_BRIGHT),
    MIN_BRIGHT + rand() % (256 - MIN_BRIGHT),
    MIN_BRIGHT + rand() % (256 - MIN_BRIGHT),
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
    m->velocity = (Vector2){ direction.x * speed, direction.y * speed };
}


// 운석 초기화
void InitMeteors(Meteor* meteors) {
    srand((unsigned int)time(NULL));
    speed = 3;
    for (int i = 0; i < MAX_METEORS; i++) {
        RespawnMeteor(&meteors[i], i);
    }
}

//운석 위치 업데이트
void UpdateMeteors(Meteor* meteors, Player* playerRef, Bullet* bullets, int* score, bool* gameOver,
    Item* item, Sound collisionBullet, Sound collisionPlayer) {
    double currentTime = GetTime();

  
    bool freezeActive = item->isItem && (item->type == STOP_METEOR) && (currentTime - item->itemStartTime[0] <= STOPMETEOR_TIME);

    for (int i = 0; i < MAX_METEORS; i++) {
        if (!freezeActive) {
            meteors[i].position.x += meteors[i].velocity.x;
            meteors[i].position.y += meteors[i].velocity.y;
        }
        // 화면 바깥 +100만큼 나가면 운석 삭제
        if (meteors[i].position.x < -100 || meteors[i].position.x > SCREEN_WIDTH + 100 ||
            meteors[i].position.y < -100 || meteors[i].position.y > SCREEN_HEIGHT + 100) {
            RespawnMeteor(&meteors[i], i);  // 삭제된 meteor 재사용
        }
    }

    //운석-총알 충돌 처리
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) continue;

        for (int j = 0; j < MAX_METEORS; j++) {
            bool hit = false;

            if (bullets[i].isLaser) {
                hit = CheckCollisionCircleLine(meteors[j].position, meteors[j].radius,
                    bullets[i].position, GetLaserEndPos(&bullets[i]));
            }
            else {
                hit = CheckCollisionCircles(bullets[i].position, BULLET_RADIUS,
                    meteors[j].position, meteors[j].radius);
            }

            if (hit) {
                // 운석-총알 충돌 효과음 재생
                PlaySound(collisionBullet);
                // 충돌 이펙트 생성
                GenerateExplosion(meteors[j].position, meteors[j].color);

                // 부딪힌 총알 삭제
                if (!bullets[i].isLaser)
                    bullets[i].active = false;

                // 총알과 운석이 충돌했을 경우 점수 100점 추가
                *score += 100;
                checkScore += 100;
                //1000점 획득 할 때마다 속도 +0.5f
                if (checkScore / 1000 == 1)
                {
                    speed += 0.5f;
                    checkScore = 0;
                }
                // 최고 점수보다 현재 점수가 높을 경우 최고 점수 갱신
                if (*score > highScore) highScore = *score;
                RespawnMeteor(&meteors[j], j);
                break;
            }
        }
    }

    // 플레이어 무적 상태일 경우 충돌 검사 무시
    if (playerRef->isCollision) {
        double diffTime = GetTime() - playerRef->deathTime;
        if (diffTime < INVINCIBLE_TIME) return;  // 아직 무적 상태면 충돌 검사 건너뜀
        else playerRef->isCollision = false;  // 무적 시간 끝났으면 초기화
    }

    //운석-플레이어 충돌 처리
    for (int i = 0; i < MAX_METEORS; i++) {
        
        if (item->isItem && item->type == INVINCIBLE_PLAYER) break;
        
        else if (CheckCollisionCircles(playerRef->position, PLAYER_SIZE / 2.0f,
            meteors[i].position, meteors[i].radius)) {
            // 운석-플레이어 충돌 효과음 재생
            PlaySound(collisionPlayer);
            GenerateExplosion(playerRef->position, RED);
            PlayerCollision(playerRef);
            playerRef->lives--;
            // lives <= 0 이면 게임 오버
            if (playerRef->lives <= 0) *gameOver = true;
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