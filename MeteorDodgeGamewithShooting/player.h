#pragma once

#define PLAYER_SIZE 20				// 플레이어 크기
#define PLAYER_ACCEL 0.5f			// 플레이어 가속력
#define PLAYER_FRICTION 0.9f		// 플레이어 마찰력
#define TRAIL_LENGTH 20				// 잔상 길이
#define INVINCIBLE_TIME 5			// 플레이어 무적 시간

#include "raylib.h"
#include "raymath.h"

typedef struct Item Item;			// 헤더 꼬임으로 인해 구조체 명칭만 따로 선언

struct Player
{
	Vector2 position;				// 플레이어 위치
	Vector2 trail[TRAIL_LENGTH];	// 잔상 배열
	Vector2 velocity;				// 플레이어 속도
	Vector2 head,left,right;		// 삼각형인 플레이어의 머리, 왼쪽, 오른쪽 꼭짓점
	Color playerColor;
	bool isCollision;				// 충돌 상태 flag
	double deathTime;				// 사망한 시각
	float angle;					// 플레이어 각도
	float size;
	int lives;						// 플레이어 생명
	int trailIdx;
}typedef Player;

void InitPlayer(Player *playerRef);
void UpdatePlayer(Player *playerRef, Item* item);
void DrawPlayer(Player* playerRef, Item* item);

// 플레이어가 충돌 시 호출되는 함수
void PlayerCollision(Player* playerRef);
// 플레이어가 화면 바깥으로 나가는 것 제한하는 함수
void ScreenRestrictPlayer(Player* playerRef);