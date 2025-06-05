#pragma once
#include "bullet.h"
#include "raylib.h"

// 총알 발사 쿨타임 전역 변수
static int shootCooldown = 0;

void FireBulletOrLaser(Bullet *bullets, Player* playerRef, Item* item, Sound fire) {
	if (shootCooldown > 0) return;
	// 총알 발사 사운드 재생
	PlaySound(fire);

	// 총알 배열 반복문
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (!bullets[i].active) {
			// 비활성화 상태라면 활성화시키기
			bullets[i].active = true;

			// 플레이어가 레이저 아이템을 먹은 상태라면 isLaser = true
			bullets[i].isLaser = item->isItem && (item->type == LASER_GUN) && (GetTime() - item->itemStartTime[1] <= LASER_TIME);

			float rad = playerRef->angle * (PI / 180.0f);

			// 총알 발사 위치를 플레이어의 헤드로 고정
			bullets[i].position = playerRef->head;

			// 플레이어 방향으로 생성
			Vector2 direction = (Vector2){
				cosf(rad),
				sinf(rad)
			};

			// 레이저면 레이저 speed로 바꾸기
			float speed = bullets[i].isLaser ? LASER_SPEED : BULLET_SPEED;

			// 총알 속도 계산
			bullets[i].velocity = (Vector2){ direction.x * speed , direction.y * speed };

			// 발사 쿨타임 저장
			shootCooldown = SHOOT_COOLDOWN_FRAMES;
			break;
		}
	}
}

// 총알 위치 업데이트
void UpdateBullets(Bullet* bullets) {
	// 총알 발사 쿨타임이 아직 남았다면 프레임마다 줄이기
	if (shootCooldown > 0) shootCooldown--;

	// 총알 배열 돌면서 위치 업데이트
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

// 총알 그리기
void DrawBullets(Bullet* bullets, Item* item) {
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (!bullets[i].active) continue;

		// 레이저면 직선 그리기
		if (bullets[i].isLaser) {
			DrawLineEx(bullets[i].position, GetLaserEndPos(&bullets[i]), 3.0f, ORANGE);
		}
		// 총알이면 원 그리기
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