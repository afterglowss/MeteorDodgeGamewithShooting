#include "player.h"
#include <stdio.h>
#include "raylib.h"


void InitPlayer(Player* playerRef) {

    playerRef->position = (Vector2){ 400, 300 };  // 초기 위치
    playerRef->velocity = (Vector2){ 0, 0 };      // 초기 속도
    playerRef->angle = 0.0f;
}

void DrawPlayer(Player* playerRef) {
    float rad = playerRef->angle * (PI / 180.0f);

    // 플레이어가 바라보는 위치
    Vector2 head;
    head.x = playerRef->position.x + PLAYER_SIZE * cos(rad);
    head.y = playerRef->position.y + PLAYER_SIZE * sin(rad);

    // -90도 방향 (왼쪽)
    float leftRad = (playerRef->angle - 90.0f) * (PI / 180.0f);
    Vector2 left;
    left.x = playerRef->position.x + PLAYER_SIZE / 2 * cos(leftRad);
    left.y = playerRef->position.y + PLAYER_SIZE / 2 * sin(leftRad);

    // +90도 방향 (오른쪽)
    float rightRad = (playerRef->angle + 90.0f) * (PI / 180.0f);
    Vector2 right;
    right.x = playerRef->position.x + PLAYER_SIZE / 2 * cos(rightRad);
    right.y = playerRef->position.y + PLAYER_SIZE / 2 * sin(rightRad);

    // 플레이어 본체
    DrawCircleV(playerRef->position, 5.0f, RED);

    // 참고용 시각화 (선택 사항)
    DrawTriangle(head, left, right, RED);
}

void UpdatePlayer(Player* playerRef) {
    float deltaTime = GetFrameTime();


    float rad = (PI / 180.0f);
    float turnspeed = 360.0;
    float maxspeed = 0.1f;

    // 플레이어 회전
    if (IsKeyDown(KEY_LEFT))  playerRef->angle -= turnspeed * deltaTime;
    if (IsKeyDown(KEY_RIGHT)) playerRef->angle += turnspeed * deltaTime;

    // 속도 증가
    float acceleration = 0.0f;
    if (IsKeyDown(KEY_UP)) {
        acceleration = PLAYER_ACCEL;
    }
    else {
        // 감속
        playerRef->velocity.x *= PLAYER_FRICTION;
        playerRef->velocity.y *= PLAYER_FRICTION;
    }

    // 바라보는 방향으로 속도 적용
    Vector2 direction = {
        cosf(playerRef->angle * rad),
        sinf(playerRef->angle * rad)
    };

    //속도 업데이트
    playerRef->velocity.x += direction.x * acceleration * deltaTime;
    playerRef->velocity.y += direction.y * acceleration * deltaTime;

    // 속도 제한
    float speed = Vector2Length(playerRef->velocity);
    if (speed > maxspeed) {
        playerRef->velocity = Vector2Scale(Vector2Normalize(playerRef->velocity), maxspeed);
    }

    // 위치 업데이트
    playerRef->position.x += playerRef->velocity.x;
    playerRef->position.y += playerRef->velocity.y;

}

