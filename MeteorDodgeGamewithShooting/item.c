#include "item.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ITEM_RADIUS 15
#define ITEM_VISIBLE_DURATION 5.0     // �������� �����Ǵ� �ð� (��)
#define ITEM_RESPAWN_DELAY 10.0       // �������� ����� �� �ٽ� ��Ÿ�� �������� ��� �ð� (��)

static double itemActiveTime = 0.0;   // �������� ��Ÿ�� ����
static double lastInactiveTime = 0.0; // �������� ����� ����

void InitItem(Item* item) {
    item->active = false;
    item->position = (Vector2){ 0, 0 };
    item->type = STOP_METEOR;
    itemActiveTime = 0;
    lastInactiveTime = GetTime();  // ������ �� ��Ȱ��ȭ�� ����
}

void UpdateItem(Item* item, Player* player, bool* meteorFreeze, double* freezeStartTime, 
    Sound invincibleSound, Sound getItemSound) {
    double currentTime = GetTime();

    //� �Ͻ����� ������
    // �������� ��Ȱ�� ������ ��, ���� �ð��� ������ �ٽ� ����
    if (!item->active && (currentTime - lastInactiveTime >= ITEM_RESPAWN_DELAY)) {
        item->active = true;
        item->position = (Vector2){ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT };
        item->type = STOP_METEOR;
        itemActiveTime = currentTime;
    }

    // �������� Ȱ�� ������ ��
    if (item->active) {
        // �ð��� �� ������ �ڵ� ��Ȱ��ȭ
        if (currentTime - itemActiveTime >= ITEM_VISIBLE_DURATION) {
            item->active = false;
            lastInactiveTime = currentTime;
            return;
        }

        // �÷��̾ �������� �Ծ����� Ȯ��
        if (CheckCollisionCircles(player->position, PLAYER_SIZE / 2.0f, item->position, ITEM_RADIUS)) {
            if (item->type == STOP_METEOR) {
                *meteorFreeze = true;
                *freezeStartTime = currentTime;

                // � ���� �������� �Ծ��� �� ȿ����
                PlaySound(getItemSound);
            }
            item->active = false;
            lastInactiveTime = currentTime;
        }
    }
}

void DrawItem(Item* item) {
    if (!item->active) return;

    switch (item->type)
    {
        //� ���� ������
    case STOP_METEOR:
        DrawStar(item->position, ITEM_RADIUS, ITEM_RADIUS * 0.4f, GetTime() * 30.0f, GREEN);
        break;
        //�÷��̾� ���� ������
    case INVINCIBLE_PLAYER:
        DrawStar(item->position, ITEM_RADIUS, ITEM_RADIUS * 0.4f, GetTime() * 30.0f, YELLOW);
        break;
        //������ �� ������
    case LASER_GUN:
        DrawStar(item->position, ITEM_RADIUS, ITEM_RADIUS * 0.4f, GetTime() * 30.0f, ORANGE);
        break;
    }
}

void DrawStar(Vector2 center, float outerRadius, float innerRadius, float rotationAngleDeg, Color color)
{
    Vector2 vertices[10]; // ���� �迭�� ���� (���� ����)

    // ȸ�� ������ �������� ��ȯ
    float rotationAngleRad = rotationAngleDeg * (PI / 180.0f);

    // 10���� ������ ���
    for (int i = 0; i < 10; i++)
    {
        float angle = (i * PI / 5.0f) + rotationAngleRad - (PI / 2.0f);

        float currentRadius = (i % 2 == 0) ? outerRadius : innerRadius;

        vertices[i].x = center.x + currentRadius * cosf(angle);
        vertices[i].y = center.y + currentRadius * sinf(angle);
    }

    //5���� �ٱ��� ������ �κ� (�� ����) �׸���
    for (int i = 0; i < 5; i++)
    {
        DrawTriangle(vertices[(i * 2 + 1) % 10], vertices[i * 2], vertices[(i * 2 - 1 + 10) % 10], color);
    }

    //�߾��� ������ ä���
    for (int i = 0; i < 5; i++)
    {
        DrawTriangle(center, vertices[(i * 2 + 3) % 10], vertices[(i * 2 + 1) % 10], color);
    }
}
