#include "player.h"
#include <stdio.h>
#include "raylib.h"
#include "game.h"

void InitPlayer(Player* playerRef) {

	playerRef->position = (Vector2){ 600, 400 };  // 초기 위치
	playerRef->velocity = (Vector2){ 0, 0 };      // 초기 속도
	playerRef->head = (Vector2){ 0, 0 };
	playerRef->angle = 0.0f;
	playerRef->lives = 5;
	playerRef->isCollision = false;
}

void playerCollision(Player *playerRef) {
	playerRef->position = (Vector2){ 600 , 400 };
	playerRef->deathTime = GetTime();
	playerRef->isCollision = true;
}

void DrawPlayer(Player* playerRef) {
	float rad = playerRef->angle * (PI / 180.0f);

	// 플레이어가 바라보는 위치
	playerRef->head.x = playerRef->position.x + PLAYER_SIZE * cos(rad);
	playerRef->head.y = playerRef->position.y + PLAYER_SIZE * sin(rad);

	// -90도 방향 (왼쪽)
	float leftRad = (playerRef->angle - 90.0f) * (PI / 180.0f);
	playerRef->left.x = playerRef->position.x + PLAYER_SIZE / 2 * cos(leftRad);
	playerRef->left.y = playerRef->position.y + PLAYER_SIZE / 2 * sin(leftRad);

	// +90도 방향 (오른쪽)
	float rightRad = (playerRef->angle + 90.0f) * (PI / 180.0f);
	playerRef->right.x = playerRef->position.x + PLAYER_SIZE / 2 * cos(rightRad);
	playerRef->right.y = playerRef->position.y + PLAYER_SIZE / 2 * sin(rightRad);


	//########## 플레이어 깜빡임 처리 #########//
	
	if (playerRef->isCollision == true) {
		double diffTime = GetTime() - playerRef->deathTime;
		if (diffTime < 2) {
			if (fmod(diffTime, 0.4) < 0.2) {
				DrawCircleV(playerRef->position, 5.0f, RED);
				DrawTriangle(playerRef->head, playerRef->left, playerRef->right, RED);
			}
			else {
			}
		}
		else {
			playerRef->isCollision = false;
		}
		DrawText(TextFormat("%.2f", diffTime), 10, 10, 20, RED);
	}
	else {
		DrawCircleV(playerRef->position, 5.0f, RED);
		DrawTriangle(playerRef->head, playerRef->left, playerRef->right, RED);
	}
}

void UpdatePlayer(Player* playerRef) {

	
	//######### 속도/ 위치 업데이트 ###########//

	float deltaTime = GetFrameTime();
	float rad = (PI / 180.0f);
	float turnspeed = 360.0;
	float maxspeed = 10.0f;

	// 플레이어 회전
	if (IsKeyDown(KEY_LEFT))  playerRef->angle -= turnspeed * deltaTime;
	if (IsKeyDown(KEY_RIGHT)) playerRef->angle += turnspeed * deltaTime;

	// 속도 증가
	float acceleration = 0.0f;
	if (IsKeyDown(KEY_UP)) {
		acceleration = PLAYER_ACCEL;
	}
	else {
		// 감속
		playerRef->velocity.x *= PLAYER_FRICTION;
		playerRef->velocity.y *= PLAYER_FRICTION;
	}

	// 바라보는 방향으로 속도 적용
	Vector2 direction = {
		cosf(playerRef->angle * rad),
		sinf(playerRef->angle * rad)
	};

	//속도 업데이트
	playerRef->velocity.x += direction.x * acceleration;
	playerRef->velocity.y += direction.y * acceleration;

	// 속도 제한
	float speed = Vector2Length(playerRef->velocity);
	if (speed > maxspeed) {
		playerRef->velocity = Vector2Scale(Vector2Normalize(playerRef->velocity), maxspeed);
	}

	// 위치 업데이트
	playerRef->position.x += playerRef->velocity.x;
	playerRef->position.y += playerRef->velocity.y;

}

