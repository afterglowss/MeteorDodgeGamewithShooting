#pragma once

#define PLAYER_SIZE 20
#define PLAYER_ACCEL 0.5f
#define PLAYER_FRICTION 0.9f
#define TRAIL_LENGTH 20

#include "raylib.h"
#include "raymath.h"

struct Player
{
	Vector2 position;
	Vector2 velocity;
	float angle;
	float size;
	int lives;
}typedef Player;

void InitPlayer(Player *playerRef);
void UpdatePlayer(Player *playerRef);
void DrawPlayer(Player *playerRef);

