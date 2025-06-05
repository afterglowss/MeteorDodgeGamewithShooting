#pragma once
#include "raylib.h"
#include "player.h"

typedef struct Player Player;


typedef enum {      // 아이템 타입 열거형으로 정의
    STOP_METEOR,
    INVINCIBLE_PLAYER,
    LASER_GUN
} ItemType;

// 아이템 구조체 정의
typedef struct Item {
    Vector2 position;           // 아이템 위치
    bool active;                // 아이템 활성화 여부
    bool isItem;                // 플레이어가 먹은 상태인지
    ItemType type;              // 아이템 타입
    double itemStartTime[3];    // 아이템 적용 시작 시간 저장하는 배열
} Item;

void InitItem(Item* item);
void UpdateItem(Item* item, Player* player, Sound invincibleSound, Sound getItemSound, Music gameSceneMusic);
void DrawItem(Item* item);
void DrawStar(Vector2 center, float outerRadius, float innerRadius, float rotationAngleDeg, Color color);
