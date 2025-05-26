#pragma once
#include "raylib.h"
#include "player.h"

typedef enum {
    STOP_METEOR = 0,
    INVINCIBLE_PLAYER = 1,
    LASER_GUN = 2
} ItemType;

typedef struct Item {
    Vector2 position;
    bool active;
    ItemType type;
} Item;

void InitItem(Item* item);
void UpdateItem(Item* item, Player* player, bool* meteorFreeze, double* freezeStartTime,
    Sound invincibleSound, Sound getItemSound);
void DrawItem(Item* item);

void DrawStar(Vector2 center, float radius, int points, Color fillColor, Color outlineColor);