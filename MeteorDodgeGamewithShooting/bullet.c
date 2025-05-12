#pragma once
#include "bullet.h"
#include "raylib.h"

static Bullet bullets[MAX_BULLETS];
static int shootCooldown = 0;

//총알 생성, 그냥 정해진 어느 위치에서 생성되게
void FireBullet() {
	if (shootCooldown > 0) return;

	for (int i = 0; i < MAX_BULLETS; i++) {
		if (!bullets[i].active) {
			bullets[i].active = true;

			//중앙에서 생성, 추후 플레이어 위치에서 생성
			bullets[i].position = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

			//고정 방향, 추후 플레이어 방향으로 생성
			Vector2 direction = { 1,0 };
			bullets[i].velocity = (Vector2){ direction.x * BULLET_SPEED, direction.y * BULLET_SPEED };

			shootCooldown = SHOOT_COOLDOWN_FRAMES;
			break;
		}
	}
}

//총알 위치 업데이트
void UpdateBullets() {}

//총알 그리기
void DrawBullets() {
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullets[i].active) {
			DrawCircleV(bullets[i].position, BULLET_RADIUS, RED);
		}
	}
}