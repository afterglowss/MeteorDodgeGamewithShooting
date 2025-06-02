#pragma once
#include "bullet.h"
#include "raylib.h"

static int shootCooldown = 0;
void FireBulletOrLaser(Bullet *bullets, Player* playerRef, Item* item, Sound fire) {
	if (shootCooldown > 0) return;

	PlaySound(fire);
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (!bullets[i].active) {
			bullets[i].active = true;
			bullets[i].isLaser = playerRef->laserMode;

			bullets[i].isLaser = item->isItem && (item->type == LASER_GUN) && (GetTime() - item->itemStartTime[1] <= LASER_TIME);

			float rad = playerRef->angle * (PI / 180.0f);

			bullets[i].position = playerRef->head;

			//플레이어 방향으로 생성
			Vector2 direction = (Vector2){
				cosf(rad),
				sinf(rad)
			};

			float speed = bullets[i].isLaser ? LASER_SPEED : BULLET_SPEED;

			bullets[i].velocity = (Vector2){ direction.x * speed , direction.y * speed };

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
void DrawBullets(Bullet* bullets, Item* item) {
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (!bullets[i].active) continue;

		if (bullets[i].isLaser) {
			DrawLineEx(bullets[i].position, GetLaserEndPos(&bullets[i]), 3.0f, ORANGE);
		}
		else
		{
			DrawCircleV(bullets[i].position, BULLET_RADIUS, YELLOW);
		}
	}
}

Vector2 GetLaserEndPos(Bullet* bullets) {
	if (!bullets->isLaser) return bullets->position;

	Vector2 endPos = {
		bullets->position.x + bullets->velocity.x * LASER_LENGTH,
		bullets->position.y + bullets->velocity.y * LASER_LENGTH
	};
	return endPos;
}