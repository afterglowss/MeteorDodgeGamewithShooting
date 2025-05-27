#pragma once
#include "raylib.h"
#include "player.h"

typedef struct Player Player;


typedef enum {
    STOP_METEOR,
    INVINCIBLE_PLAYER,
    LASER_GUN
} ItemType;

typedef struct Item {
    Vector2 position;
    bool active;
    bool isItem;
    ItemType type;
    double itemStartTime[3];
} Item;

void InitItem(Item* item);
void UpdateItem(Item* item, Player* player, Sound invincibleSound, Sound getItemSound, Music gameSceneMusic);
void DrawItem(Item* item);
void DrawStar(Vector2 center, float outerRadius, float innerRadius, float rotationAngleDeg, Color color);
