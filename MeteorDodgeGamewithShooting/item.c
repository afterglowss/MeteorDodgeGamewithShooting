#include "item.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "meteor.h"
#include "player.h"
#include "bullet.h"

#define ITEM_RADIUS 15
#define ITEM_VISIBLE_DURATION 5.0     // 아이템이 유지되는 시간 (초)
#define ITEM_RESPAWN_DELAY 10.0       // 아이템이 사라진 후 다시 나타날 때까지의 대기 시간 (초)

static double itemActiveTime = 0.0;   // 아이템이 나타난 시점
static double lastInactiveTime = 0.0; // 아이템이 사라진 시점

void InitItem(Item* item) {
    item->active = false;
    item->position = (Vector2){ 0, 0 };
    itemActiveTime = 0;
    lastInactiveTime = GetTime();  // 시작할 때 비활성화로 시작
    for (int i = 0; i < 3; i++) item->itemStartTime[i] = 0;
}

void UpdateItem(Item* item, Player* player, Sound invincibleSound, Sound getItemSound, Music gameSceneMusic) {
    double currentTime = GetTime();

    //운석 일시정지 아이템
    // 아이템이 비활성 상태일 때, 일정 시간이 지나면 다시 생성
    if (!item->active && (currentTime - lastInactiveTime >= ITEM_RESPAWN_DELAY)) {
        item->active = true;
        item->position = (Vector2){ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT };
        //아이템 랜덤 생성
        int itemIdx = rand() % 3;
        
        switch (itemIdx)
        {
        case 0:
            item->type = STOP_METEOR;
            break;
        case 1:
            item->type = LASER_GUN;
            break;
        case 2:
            item->type = INVINCIBLE_PLAYER;
            break;
        default:
            break;
        }
        
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
        lastInactiveTime = currentTime;

        // 플레이어가 아이템을 먹었는지 확인
        if (CheckCollisionCircles(player->position, PLAYER_SIZE / 2.0f, item->position, ITEM_RADIUS)) {

            switch (item->type)
            {
            case STOP_METEOR:
                item->itemStartTime[0] = currentTime;
                PlaySound(getItemSound);
                break;
            case LASER_GUN:
                item->itemStartTime[1] = currentTime;
                PlaySound(getItemSound);
                break;
            case INVINCIBLE_PLAYER:
                item->itemStartTime[2] = currentTime;
                StopMusicStream(gameSceneMusic);
                PlaySound(invincibleSound);
                break;
            default:
                break;
            }
            
            item->isItem = true;
            item->active = false;
            lastInactiveTime = currentTime;
        }
    }

    // 플레이어 무적 아이템을 얻은 이후 시간 계산
    if (!item->active && item->isItem && item->type == INVINCIBLE_PLAYER) {
        // 5초 지났을 경우 효과음 종료
        if (currentTime - item->itemStartTime[2] >= INVINCIBLE_TIME) {
            StopSound(invincibleSound);
            // 멈춰뒀던 게임 음악 플레이
            if (!IsMusicStreamPlaying(gameSceneMusic)) {
                PlayMusicStream(gameSceneMusic);
            }
        }
    }
}

void DrawItem(Item* item) {
    if (!item->active) return;

    switch (item->type)
    {
        //운석 정지 아이템
    case STOP_METEOR:
        DrawStar(item->position, ITEM_RADIUS, ITEM_RADIUS * 0.4f, GetTime() * 30.0f, GREEN);
        break;
        //플레이어 무적 아이템
    case INVINCIBLE_PLAYER:
        DrawStar(item->position, ITEM_RADIUS, ITEM_RADIUS * 0.4f, GetTime() * 30.0f, YELLOW);
        break;
        //레이저 건 아이템
    case LASER_GUN:
        DrawStar(item->position, ITEM_RADIUS, ITEM_RADIUS * 0.4f, GetTime() * 30.0f, ORANGE);
        break;
    }
}

void DrawStar(Vector2 center, float outerRadius, float innerRadius, float rotationAngleDeg, Color color)
{
    Vector2 vertices[10]; // 정적 배열로 선언 (가장 안전)

    // 회전 각도를 라디안으로 변환
    float rotationAngleRad = rotationAngleDeg * (PI / 180.0f);

    // 10개의 꼭짓점 계산
    for (int i = 0; i < 10; i++)
    {
        float angle = (i * PI / 5.0f) + rotationAngleRad - (PI / 2.0f);

        float currentRadius = (i % 2 == 0) ? outerRadius : innerRadius;

        vertices[i].x = center.x + currentRadius * cosf(angle);
        vertices[i].y = center.y + currentRadius * sinf(angle);
    }

    //5개의 바깥쪽 뾰족한 부분 (각 꼭지) 그리기
    for (int i = 0; i < 5; i++)
    {
        DrawTriangle(vertices[(i * 2 + 1) % 10], vertices[i * 2], vertices[(i * 2 - 1 + 10) % 10], color);
    }

    //중앙의 오각형 채우기
    for (int i = 0; i < 5; i++)
    {
        DrawTriangle(center, vertices[(i * 2 + 3) % 10], vertices[(i * 2 + 1) % 10], color);
    }
}
