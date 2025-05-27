#pragma once
#include "meteor.h"
#include "game.h"

int highScore = 0;
int checkScore = 0;
float speed;

// ������ � ���� �Լ�
void RespawnMeteor(Meteor* m, int index) {
    m->radius = (float)(rand() % 31 + 10);

    // ������ ���� ����(���)
    m->color = (Color){
    minBright + rand() % (256 - minBright),
    minBright + rand() % (256 - minBright),
    minBright + rand() % (256 - minBright),
    255
    };

    // ȭ�� �� ������ ��ġ
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


    //ȭ�� �ܺο��� ���η� ������ ����
    float angle = ((float)(rand() % 360)) * DEG2RAD;
    Vector2 direction = (Vector2){
        cosf(angle),
        sinf(angle)
    };

    //�ӵ�
    m->velocity = (Vector2){ direction.x * speed, direction.y * speed };
}


// � �ʱ�ȭ
void InitMeteors(Meteor* meteors) {
    srand((unsigned int)time(NULL));
    speed = 3;
    for (int i = 0; i < MAX_METEORS; i++) {
        RespawnMeteor(&meteors[i], i);
    }
}

//� ��ġ ������Ʈ-17
void UpdateMeteors(Meteor* meteors, Player* playerRef, Bullet* bullets, int* score, bool* gameOver,
    Item* item, Sound collisionBullet, Sound collisionPlayer) {
    double currentTime = GetTime();

  
    bool freezeActive = item->isItem && (item->type == STOP_METEOR) && (currentTime - item->itemStartTime[0] <= 3.0);

    for (int i = 0; i < MAX_METEORS; i++) {
        if (!freezeActive) {
            meteors[i].position.x += meteors[i].velocity.x;
            meteors[i].position.y += meteors[i].velocity.y;
        }

        if (meteors[i].position.x < -100 || meteors[i].position.x > SCREEN_WIDTH + 100 ||
            meteors[i].position.y < -100 || meteors[i].position.y > SCREEN_HEIGHT + 100) {
            RespawnMeteor(&meteors[i], i);  // ������ meteor ����
        }
    }

    //�-�Ѿ� �浹 ó��: 20
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) continue;

        for (int j = 0; j < MAX_METEORS; j++) {

            if (CheckCollisionCircles(bullets[i].position, BULLET_RADIUS,
                meteors[j].position, meteors[j].radius)) {
                GenerateExplosion(meteors[j].position, meteors[j].color);
                bullets[i].active = false;
                // �Ѿ˰� ��� �浹���� ��� ���� 100�� �߰�
                *score += 100;
                checkScore += 100;
                //1000�� ȹ�� �� ������ �ӵ� +0.5f
                if (checkScore / 1000 == 1) 
                {
                    speed += 0.5f;
                    checkScore = 0;
                }
                // �ְ� �������� ���� ������ ���� ��� �ְ� ���� ����
                if (*score > highScore) highScore = *score;
                RespawnMeteor(&meteors[j], j);
                break;
            }
        }
    }

    // �÷��̾� ���� ������ ��� �浹 �˻� ����
    if (playerRef->isCollision) {
        double diffTime = GetTime() - playerRef->deathTime;
        if (diffTime < 2.0) return;  // ���� ���� ���¸� �浹 �˻� �ǳʶ�
        else playerRef->isCollision = false;  // ���� �ð� �������� �ʱ�ȭ
    }

    //�-�÷��̾� �浹 ó��: 19
    for (int i = 0; i < MAX_METEORS; i++) {
        
        if (item->isItem && item->type == INVINCIBLE_PLAYER) break;
        
        else if (CheckCollisionCircles(playerRef->position, PLAYER_SIZE / 2.0f,
            meteors[i].position, meteors[i].radius)) {
            GenerateExplosion(playerRef->position, RED);
            playerCollision(playerRef);
            playerRef->lives--;
            // lives <= 0 �̸� ���� ����
            if (playerRef->lives <= 0) *gameOver = true;
            break;
        }
        
    }
}

// � �׸���
void DrawMeteors(Meteor* meteors) {
    for (int i = 0; i < MAX_METEORS; i++) {
        DrawCircleV(meteors[i].position, meteors[i].radius, meteors[i].color);
    }
}