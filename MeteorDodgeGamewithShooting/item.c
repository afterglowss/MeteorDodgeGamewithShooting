#include "item.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>

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
    DrawCircleLines((int)item->position.x, (int)item->position.y, ITEM_RADIUS, BLACK);
    DrawStar(item->position, ITEM_RADIUS - 1, 5, RED, RED);
}


void DrawStar(Vector2 center, float radius, int points, Color fillColor, Color outlineColor) {
    if (points < 2) return;

    float angleStep = 2 * PI / (points * 2);
    Vector2* starVertices = (Vector2*)malloc(sizeof(Vector2) * points * 2);
    if (!starVertices) return;

    for (int i = 0; i < points * 2; i++) {
        float r = (i % 2 == 0) ? radius : radius * 0.5f;
        float angle = i * angleStep - PI / 2;
        starVertices[i] = (Vector2){
            center.x + cosf(angle) * r,
            center.y + sinf(angle) * r
        };
    }

    // Fill each star arm as triangle (outer - inner - next outer)
    for (int i = 0; i < points; i++) {
        int outer = i * 2;
        int inner = (outer + 1) % (points * 2);
        int nextOuter = (outer + 2) % (points * 2);
        DrawTriangle(starVertices[outer], starVertices[inner], starVertices[nextOuter], fillColor);
    }

    // Draw outline
    for (int i = 0; i < points * 2; i++) {
        DrawLineV(starVertices[i], starVertices[(i + 1) % (points * 2)], outlineColor);
    }

    free(starVertices);
}
