#pragma once
#include "raylib.h"
#include "raymath.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>

#define MAX_METEORS 40

typedef struct Meteor {
	Vector2 position;
	Vector2 velocity;
	float radius;
}Meteor;

void InitMeteors();
void UpdateMeteors();
void DrawMeteors();