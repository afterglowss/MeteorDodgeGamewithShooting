#pragma once
#include "raylib.h"
#include "raymath.h"
#include "game.h"
#include "player.h"
#include <stdlib.h>
#include <time.h>

#define MAX_METEORS 40

typedef struct Meteor {
	Vector2 position;
	Vector2 velocity;
	float radius;
}Meteor;

void InitMeteors(Meteor *meteors);
void UpdateMeteors(Meteor* meteors, Player* playerRef);
void DrawMeteors(Meteor* meteors);