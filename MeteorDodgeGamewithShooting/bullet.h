#include <stdlib.h>
#include "raylib.h"

#define MAX_BULLETS 50
#define BULLET_SPEED 1
#define BULLET_RADIUS 4
#define SHOOT_COOLDOWN_FRAMES 12

typedef struct Bullet {
	Vector2 position;
	Vector2 velocity;
	bool active;
} Bullet;

void FireBullet();
void UpdateBullets();
void DrawBullets();