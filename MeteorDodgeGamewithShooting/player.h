#pragma once

#define PLAYER_SIZE 20
#define PLAYER_ACCEL 0.5f
#define PLAYER_FRICTION 0.9f
#define TRAIL_LENGTH 20
#define ROTATE_LERP_FACTOR 0.15f
#define INVINCIBLE_TIME 3

#include "raylib.h"
#include "raymath.h"

struct Player
{
	Vector2 position;

	Vector2 trail[TRAIL_LENGTH];
	Vector2 velocity;
	Vector2 head,left,right;
	bool isCollision;
	double deathTime;
	float angle;
	float size;
	int lives;
	int trailIdx;
	bool laserMode;
	double laserStartTime;
}typedef Player;

void InitPlayer(Player *playerRef);
void UpdatePlayer(Player *playerRef);
void DrawPlayer(Player* playerRef); 
void playerCollision(Player* playerRef);

