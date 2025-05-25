#pragma once
#include "bullet.h"
#include "raylib.h"


static int shootCooldown = 0;

//총알 생성, player의 head에서 생성되게
void FireBullet(Bullet *bullets, Player* playerRef, Sound fire) {
	if (shootCooldown > 0) return;
	PlaySound(fire);
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (!bullets[i].active) {
			bullets[i].active = true;

			float rad = playerRef->angle * (PI / 180.0f);

			//플레이어 head 위치에서 생성
			bullets[i].position = (Vector2){
				playerRef->position.x + PLAYER_SIZE * cos(rad),
				playerRef->position.y + PLAYER_SIZE * sin(rad)
			};

			//플레이어 방향으로 생성
			Vector2 direction = (Vector2){
				cosf(rad),
				sinf(rad)
			};
			bullets[i].velocity = (Vector2){ direction.x * BULLET_SPEED, direction.y * BULLET_SPEED };

			shootCooldown = SHOOT_COOLDOWN_FRAMES;
			break;
		}
	}
}

//총알 위치 업데이트
void UpdateBullets(Bullet* bullets) {
	if (shootCooldown > 0) shootCooldown--;

	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullets[i].active) {
			bullets[i].position.x += bullets[i].velocity.x;
			bullets[i].position.y += bullets[i].velocity.y;

			//화면 밖으로 나가면 삭제
			if (bullets[i].position.x < 0 || bullets[i].position.x > GetScreenWidth()
				|| bullets[i].position.y < 0 || bullets[i].position.y > GetScreenHeight()) {
				bullets[i].active = false;
			}
		}
	}
}

//총알 그리기
void DrawBullets(Bullet* bullets) {
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullets[i].active) {
			DrawCircleV(bullets[i].position, BULLET_RADIUS, YELLOW);
		}
	}
}