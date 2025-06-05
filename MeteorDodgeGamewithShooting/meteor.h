#pragma once
#include "raylib.h"
#include "raymath.h"
#include "game.h"
#include "player.h"
#include "bullet.h"
#include <stdlib.h>
#include <time.h>
#include "item.h"

#define MAX_METEORS 40		// 최대 운석 수
#define MIN_BRIGHT 100		// 최소 밝기
#define STOPMETEOR_TIME 5	// 운석 정지 아이템 시간

extern int highScore;		// 게임 실행 중 얻은 최대 점수 전역변수로 저장

typedef struct Meteor {
	Vector2 position;		// 운석 위치
	Vector2 velocity;		// 운석 속도
	Color color;			// 운석 색상
	float radius;			// 운석 반지름
}Meteor;

void InitMeteors(Meteor* meteors);
void UpdateMeteors(Meteor* meteors, Player* playerRef, Bullet* bullets, int* score, bool* gameOver,
	Item* item, Sound collisionBullet, Sound collisionPlayer);
void DrawMeteors(Meteor* meteors);
void RespawnMeteor(Meteor* m, int index);