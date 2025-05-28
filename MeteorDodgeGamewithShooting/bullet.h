#pragma once
#include <stdlib.h>
#include "raylib.h"
#include "player.h"
#include "item.h"

#define MAX_BULLETS 50
#define BULLET_SPEED 15
#define BULLET_RADIUS 4
#define SHOOT_COOLDOWN_FRAMES 12
#define LASER_SPEED 30
#define LASER_LENGTH 5

#define LASER_SPEED 30
#define LASER_LENGTH 5
#define LASER_TIME 5

typedef struct Bullet {
	Vector2 position;
	Vector2 velocity;
	bool active;
	bool isLaser;
} Bullet;

void FireBulletOrLaser(Bullet* bullets, Player* playerRef, Item* item, Sound fire);
void UpdateBullets(Bullet* bullets);
void DrawBullets(Bullet* bullets, Item * item);
Vector2 GetLaserEndPos(Bullet* bullets);