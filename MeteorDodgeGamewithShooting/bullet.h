#pragma once
#include <stdlib.h>
#include "raylib.h"
#include "player.h"
#include "item.h"

#define MAX_BULLETS 50				// 최대 총알 갯수
#define BULLET_SPEED 15				// 총알 속도
#define BULLET_RADIUS 4				// 총알 반지름
#define SHOOT_COOLDOWN_FRAMES 12	// 총알 발사 쿨타임
#define LASER_SPEED 30				// 레이저 속력
#define LASER_LENGTH 5				// 레이저 길이
#define LASER_TIME 5				// 레이저 아이템 유지 시간


// 총알 구조체 정의
typedef struct Bullet {
	Vector2 position;	// 총알 위치
	Vector2 velocity;	// 총알 속도
	bool active;		// 총알 활성화 여부
	bool isLaser;		// 레이저 상태 여부
} Bullet;


void FireBulletOrLaser(Bullet* bullets, Player* playerRef, Item* item, Sound fire);	// 총알 발사 함수
void UpdateBullets(Bullet* bullets);	
void DrawBullets(Bullet* bullets, Item * item);
// 레이저 건의 경우 총알이 직선형이기 때문에 레이저 건의 끝 지점을 얻기 위한 함수
Vector2 GetLaserEndPos(Bullet* bullets);	