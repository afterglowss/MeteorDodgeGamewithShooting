#pragma once
#include <stdlib.h>
#include "raylib.h"
#include "player.h"

#define MAX_BULLETS 50
#define BULLET_SPEED 15
#define BULLET_RADIUS 4
#define SHOOT_COOLDOWN_FRAMES 12

typedef struct Bullet {
	Vector2 position;
	Vector2 velocity;
	bool active;
} Bullet;

void FireBullet(Bullet* bullets, Player* playerRef);
void UpdateBullets(Bullet* bullets);
void DrawBullets(Bullet* bullets);