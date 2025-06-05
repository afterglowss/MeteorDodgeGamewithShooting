#include "player.h"
#include <stdio.h>
#include "raylib.h"
#include "game.h"
#include "item.h"
#include "time.h"

void InitPlayer(Player* playerRef) {
    playerRef->playerColor = RED;
    playerRef->position = (Vector2){ 600, 400 };  // 초기 위치
    playerRef->velocity = (Vector2){ 0, 0 };      // 초기 속도
    playerRef->head = (Vector2){ 0, 0 };
    playerRef->angle = 0.0f;
    playerRef->lives = 5;
    playerRef->isCollision = false;
    playerRef->trailIdx = 0;
}

void PlayerCollision(Player* playerRef) {
    // 충돌 시 중심에서 재생성
    playerRef->position = (Vector2){ 600 , 400 };
    // 죽은 시간 저장
    playerRef->deathTime = GetTime();
    playerRef->isCollision = true;
    // 플레이어 잔상 모두 삭제
    for (int i = 0; i < TRAIL_LENGTH; i++) {
        playerRef->trail[i] = (Vector2){ 0, 0 };
    }
    playerRef->trailIdx = 0;
}

void DrawPlayer(Player* playerRef, Item *item) {
    float rad = playerRef->angle * (PI / 180.0f);

    // 플레이어가 바라보는 위치
    playerRef->head.x = playerRef->position.x + PLAYER_SIZE * cos(rad);
    playerRef->head.y = playerRef->position.y + PLAYER_SIZE * sin(rad);

    // -90도 방향 (왼쪽)
    float leftRad = (playerRef->angle - 90.0f) * (PI / 180.0f);
    playerRef->left.x = playerRef->position.x + PLAYER_SIZE / 2 * cos(leftRad);
    playerRef->left.y = playerRef->position.y + PLAYER_SIZE / 2 * sin(leftRad);

    // +90도 방향 (오른쪽)
    float rightRad = (playerRef->angle + 90.0f) * (PI / 180.0f);
    playerRef->right.x = playerRef->position.x + PLAYER_SIZE / 2 * cos(rightRad);
    playerRef->right.y = playerRef->position.y + PLAYER_SIZE / 2 * sin(rightRad);


    // 잔상 그리기
    for (int i = 0; i < TRAIL_LENGTH; i++) {
        int idx = (playerRef->trailIdx + i) % TRAIL_LENGTH;
        float trace = (float)i / TRAIL_LENGTH;
        Color fade = (Color){ 255,0,0 ,(unsigned char)(trace * 100) };
        DrawCircleV(playerRef->trail[idx], 4.0f, fade);
    }


    // 플레이어 깜빡임 처리 
    if (playerRef->isCollision == true && !(item->isItem && item->type == INVINCIBLE_PLAYER)) {
        // 사망 시점부터 달라진 시간 계산
        double diffTime = GetTime() - playerRef->deathTime;
        // 2초가 안 지났다면 깜빡이기
        if (diffTime < 2) {
            if (fmod(diffTime, 0.4) < 0.2) {
                DrawCircleV(playerRef->position, 5.0f, RED);
                DrawTriangle(playerRef->head, playerRef->left, playerRef->right, RED);
            }
        }
        // 2초가 지났다면 충돌 상태 false
        else {
            playerRef->isCollision = false;
        }
    }
    // 플레이어가 먹은 아이템이 무적 아이템일 경우
    else if (item->isItem && item->type == INVINCIBLE_PLAYER) {
        double diffTime = GetTime() - item->itemStartTime[2];
        if (diffTime < INVINCIBLE_TIME) {
            // 무지개로 빛나기
            Color rainbowColors[] = {
                RED, ORANGE, YELLOW, GREEN, BLUE, DARKBLUE, PURPLE
            };
            int rainbowCount = sizeof(rainbowColors) / sizeof(rainbowColors[0]);

            static int currentColorIndex = 0;
            static double lastColorChangeTime = 0;

            double currentTime = GetTime();
            double blinkInterval = 0.1; 

            // 일정 시간 경과 시 다음 색상으로 전환
            if (currentTime - lastColorChangeTime > blinkInterval) {
                currentColorIndex = (currentColorIndex + 1) % rainbowCount;
                lastColorChangeTime = currentTime;
            }
            playerRef->playerColor = rainbowColors[currentColorIndex];
            DrawCircleV(playerRef->position, 5.0f, playerRef->playerColor);
            DrawTriangle(playerRef->head, playerRef->left, playerRef->right, playerRef->playerColor);
        }
        else item->isItem = false;
    }
    // 무적 아이템을 먹은 상태가 아니라면 일반적인 붉은색 원에 삼각형 그리기
    else {
        DrawCircleV(playerRef->position, 5.0f, RED);
        DrawTriangle(playerRef->head, playerRef->left, playerRef->right, RED);
    }
}

// 플레이어가 화면 바깥으로 나가지 않도록 제한
void ScreenRestrictPlayer(Player* playerRef) {
    float rad = playerRef->angle * (PI / 180.0f);

    Vector2 head = {
        playerRef->position.x + PLAYER_SIZE * cosf(rad),
        playerRef->position.y + PLAYER_SIZE * sinf(rad)
    };

    Vector2 left = {
        playerRef->position.x + (PLAYER_SIZE / 2) * cosf(rad - PI / 2),
        playerRef->position.y + (PLAYER_SIZE / 2) * sinf(rad - PI / 2)
    };

    Vector2 right = {
        playerRef->position.x + (PLAYER_SIZE / 2) * cosf(rad + PI / 2),
        playerRef->position.y + (PLAYER_SIZE / 2) * sinf(rad + PI / 2)
    };

    Vector2* points[] = { &head, &left, &right };

    // head, left, right 각각 화면을 나갈 수 없도록 수정
    for (int i = 0; i < 3; i++) {
        Vector2* p = points[i];

        if (p->x < 0) playerRef->position.x += (0 - p->x);
        else if (p->x > SCREEN_WIDTH) playerRef->position.x -= (p->x - SCREEN_WIDTH);

        if (p->y < 0) playerRef->position.y += (0 - p->y);
        else if (p->y > SCREEN_HEIGHT) playerRef->position.y -= (p->y - SCREEN_HEIGHT);
    }
}

void UpdatePlayer(Player* playerRef, Item* item) {
    float deltaTime = GetFrameTime();
    float rad = (PI / 180.0f);
    float turnspeed = 360.0;
    float maxspeed = 10.0f;

    // 죽고 1초간 조작 제한
    bool canMove = true;
    if (playerRef->isCollision) {
        double diffTime = GetTime() - playerRef->deathTime;
        if (diffTime < 1) {
            canMove = false;
        }
    }
    //움직일 수 없다면 속도 제한 이후 return 
    if (!canMove) {
        playerRef->velocity = (Vector2){ 0, 0 };
        return;
    }

    // 왼쪽, 오른쪽 방향키 입력시 해당 방향으로 회전
    if (IsKeyDown(KEY_LEFT))  playerRef->angle -= turnspeed * deltaTime;
    if (IsKeyDown(KEY_RIGHT)) playerRef->angle += turnspeed * deltaTime;

    // 가속도 고려해서 이동속도 증가
    float acceleration = 0.0f;
    if (IsKeyDown(KEY_UP)) {
        acceleration = PLAYER_ACCEL;
    }
    else {
        playerRef->velocity.x *= PLAYER_FRICTION;
        playerRef->velocity.y *= PLAYER_FRICTION;
    }

    // 방향 계산
    Vector2 direction = {
        cosf(playerRef->angle * rad),
        sinf(playerRef->angle * rad)
    };

    // 속도 업데이트
    playerRef->velocity.x += direction.x * acceleration;
    playerRef->velocity.y += direction.y * acceleration;

    // 속도 제한
    float speed = Vector2Length(playerRef->velocity);
    if (speed > maxspeed) {
        playerRef->velocity = Vector2Scale(Vector2Normalize(playerRef->velocity), maxspeed);
    }

    // 위치 업데이트
    playerRef->position.x += playerRef->velocity.x;
    playerRef->position.y += playerRef->velocity.y;

    // 트레일 위치 저장
    playerRef->trail[playerRef->trailIdx] = playerRef->position;
    playerRef->trailIdx = (playerRef->trailIdx + 1) % TRAIL_LENGTH;

    // 화면을 나가는지 계속 확인
    ScreenRestrictPlayer(playerRef);
}
