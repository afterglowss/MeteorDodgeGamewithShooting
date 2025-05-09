#pragma once

#define PLAYER_SIZE 20
#define PLAYER_ACCEL 0.5f
#define PLAYER_FRICTION 0.9f
#define TRAIL_LENGTH 20
#define ROTATE_LERP_FACTOR 0.15f
#define INVINCIBLE_TIME 120
#include "raylib.h"
#include "raymath.h"

struct Player
{
	Vector2 position;
	Vector2 velocity;
	float size;
	int lives;
}typedef Player;

void InitPlayer();
void UpdatePlayer();
void DrawPlayer();

