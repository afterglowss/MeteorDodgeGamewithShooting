#pragma once
#include "raylib.h"
#include "player.h"

typedef enum {
    STOP_METEOR = 0,
    INVINCIBLE_PLAYER,
    LASER_GUN
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