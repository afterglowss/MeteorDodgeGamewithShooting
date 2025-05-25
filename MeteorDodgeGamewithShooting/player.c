#include "player.h"
#include <stdio.h>
#include "raylib.h"
#include "game.h"

void InitPlayer(Player* playerRef) {

    playerRef->position = (Vector2){ 600, 400 };  // �ʱ� ��ġ
    playerRef->velocity = (Vector2){ 0, 0 };      // �ʱ� �ӵ�
    playerRef->head = (Vector2){ 0, 0 };
    playerRef->angle = 0.0f;
    playerRef->lives = 5;
    playerRef->isCollision = false;
    playerRef->trailIdx = 0;
}

void playerCollision(Player* playerRef) {
    playerRef->position = (Vector2){ 600 , 400 };
    playerRef->deathTime = GetTime();
    playerRef->isCollision = true;
    for (int i = 0; i < TRAIL_LENGTH; i++) {
        playerRef->trail[i] = (Vector2){ 0, 0 };
    }
    playerRef->trailIdx = 0;
}

void DrawPlayer(Player* playerRef) {
    float rad = playerRef->angle * (PI / 180.0f);

    // �÷��̾ �ٶ󺸴� ��ġ
    playerRef->head.x = playerRef->position.x + PLAYER_SIZE * cos(rad);
    playerRef->head.y = playerRef->position.y + PLAYER_SIZE * sin(rad);

    // -90�� ���� (����)
    float leftRad = (playerRef->angle - 90.0f) * (PI / 180.0f);
    playerRef->left.x = playerRef->position.x + PLAYER_SIZE / 2 * cos(leftRad);
    playerRef->left.y = playerRef->position.y + PLAYER_SIZE / 2 * sin(leftRad);

    // +90�� ���� (������)
    float rightRad = (playerRef->angle + 90.0f) * (PI / 180.0f);
    playerRef->right.x = playerRef->position.x + PLAYER_SIZE / 2 * cos(rightRad);
    playerRef->right.y = playerRef->position.y + PLAYER_SIZE / 2 * sin(rightRad);


    //Ʈ���� �׸���
    for (int i = 0; i < TRAIL_LENGTH; i++) {
        int idx = (playerRef->trailIdx + i) % TRAIL_LENGTH;
        float trace = (float)i / TRAIL_LENGTH;
        Color fade = (Color){ 255,0,0 ,(unsigned char)(trace * 100) };
        DrawCircleV(playerRef->trail[idx], 4.0f, fade);
    }


    //########## �÷��̾� ������ ó�� #########//

    if (playerRef->isCollision == true) {
        double diffTime = GetTime() - playerRef->deathTime;
        if (diffTime < 2) {
            if (fmod(diffTime, 0.4) < 0.2) {
                DrawCircleV(playerRef->position, 5.0f, RED);
                DrawTriangle(playerRef->head, playerRef->left, playerRef->right, RED);
            }
            else {
            }
        }
        else {
            playerRef->isCollision = false;
        }
        DrawText(TextFormat("%.2f", diffTime), 10, 10, 20, RED);
    }
    else {
        DrawCircleV(playerRef->position, 5.0f, RED);
        DrawTriangle(playerRef->head, playerRef->left, playerRef->right, RED);
    }
}

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

    for (int i = 0; i < 3; i++) {
        Vector2* p = points[i];

        if (p->x < 0) playerRef->position.x += (0 - p->x);
        else if (p->x > SCREEN_WIDTH) playerRef->position.x -= (p->x - SCREEN_WIDTH);

        if (p->y < 0) playerRef->position.y += (0 - p->y);
        else if (p->y > SCREEN_HEIGHT) playerRef->position.y -= (p->y - SCREEN_HEIGHT);
    }
}



void UpdatePlayer(Player* playerRef) {
    float deltaTime = GetFrameTime();
    float rad = (PI / 180.0f);
    float turnspeed = 360.0;
    float maxspeed = 10.0f;

    // �װ� 1�ʰ� ���� ����
    bool canMove = true;
    if (playerRef->isCollision) {
        double diffTime = GetTime() - playerRef->deathTime;
        if (diffTime < 1) {
            canMove = false;
        }
    }
    if (!canMove) {
        playerRef->velocity = (Vector2){ 0, 0 };
        return;
    }

    // ȸ��
    if (IsKeyDown(KEY_LEFT))  playerRef->angle -= turnspeed * deltaTime;
    if (IsKeyDown(KEY_RIGHT)) playerRef->angle += turnspeed * deltaTime;

    // �ӵ� ����
    float acceleration = 0.0f;
    if (IsKeyDown(KEY_UP)) {
        acceleration = PLAYER_ACCEL;
    }
    else {
        playerRef->velocity.x *= PLAYER_FRICTION;
        playerRef->velocity.y *= PLAYER_FRICTION;
    }

    // ���� ���
    Vector2 direction = {
        cosf(playerRef->angle * rad),
        sinf(playerRef->angle * rad)
    };

    // �ӵ� ������Ʈ
    playerRef->velocity.x += direction.x * acceleration;
    playerRef->velocity.y += direction.y * acceleration;

    // �ӵ� ����
    float speed = Vector2Length(playerRef->velocity);
    if (speed > maxspeed) {
        playerRef->velocity = Vector2Scale(Vector2Normalize(playerRef->velocity), maxspeed);
    }

    // ��ġ ������Ʈ
    playerRef->position.x += playerRef->velocity.x;
    playerRef->position.y += playerRef->velocity.y;

    //Ʈ���� ��ġ ����
    playerRef->trail[playerRef->trailIdx] = playerRef->position;
    playerRef->trailIdx = (playerRef->trailIdx + 1) % TRAIL_LENGTH;

    //������ ��� Ȯ��
    if (playerRef->laserMode && (GetTime() - playerRef->laserStartTime > 5.0)) {
        playerRef->laserMode = false;
    }

    ScreenRestrictPlayer(playerRef);
}
