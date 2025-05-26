#include "item.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>

#define ITEM_RADIUS 15
#define ITEM_VISIBLE_DURATION 5.0     // 아이템이 유지되는 시간 (초)
#define ITEM_RESPAWN_DELAY 10.0       // 아이템이 사라진 후 다시 나타날 때까지의 대기 시간 (초)

static double itemActiveTime = 0.0;   // 아이템이 나타난 시점
static double lastInactiveTime = 0.0; // 아이템이 사라진 시점

void InitItem(Item* item) {
    item->active = false;
    item->position = (Vector2){ 0, 0 };
    item->type = STOP_METEOR;
    itemActiveTime = 0;
    lastInactiveTime = GetTime();  // 시작할 때 비활성화로 시작
}

void UpdateItem(Item* item, Player* player, bool* meteorFreeze, double* freezeStartTime, 
    Sound invincibleSound, Sound getItemSound) {
    double currentTime = GetTime();

    //운석 일시정지 아이템
    // 아이템이 비활성 상태일 때, 일정 시간이 지나면 다시 생성
    if (!item->active && (currentTime - lastInactiveTime >= ITEM_RESPAWN_DELAY)) {
        item->active = true;
        item->position = (Vector2){ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT };
        item->type = STOP_METEOR;
        itemActiveTime = currentTime;
    }

    // 아이템이 활성 상태일 때
    if (item->active) {
        // 시간이 다 지나면 자동 비활성화
        if (currentTime - itemActiveTime >= ITEM_VISIBLE_DURATION) {
            item->active = false;
            lastInactiveTime = currentTime;
            return;
        }

        // 플레이어가 아이템을 먹었는지 확인
        if (CheckCollisionCircles(player->position, PLAYER_SIZE / 2.0f, item->position, ITEM_RADIUS)) {
            if (item->type == STOP_METEOR) {
                *meteorFreeze = true;
                *freezeStartTime = currentTime;

                // 운석 정지 아이템을 먹었을 때 효과음
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
