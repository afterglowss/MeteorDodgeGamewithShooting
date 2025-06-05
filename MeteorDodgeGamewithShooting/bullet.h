#pragma once
#include <stdlib.h>
#include "raylib.h"
#include "player.h"
#include "item.h"

#define MAX_BULLETS 50				// �ִ� �Ѿ� ����
#define BULLET_SPEED 15				// �Ѿ� �ӵ�
#define BULLET_RADIUS 4				// �Ѿ� ������
#define SHOOT_COOLDOWN_FRAMES 12	// �Ѿ� �߻� ��Ÿ��
#define LASER_SPEED 30				// ������ �ӷ�
#define LASER_LENGTH 5				// ������ ����
#define LASER_TIME 5				// ������ ������ ���� �ð�


// �Ѿ� ����ü ����
typedef struct Bullet {
	Vector2 position;	// �Ѿ� ��ġ
	Vector2 velocity;	// �Ѿ� �ӵ�
	bool active;		// �Ѿ� Ȱ��ȭ ����
	bool isLaser;		// ������ ���� ����
} Bullet;


void FireBulletOrLaser(Bullet* bullets, Player* playerRef, Item* item, Sound fire);	// �Ѿ� �߻� �Լ�
void UpdateBullets(Bullet* bullets);	
void DrawBullets(Bullet* bullets, Item * item);
// ������ ���� ��� �Ѿ��� �������̱� ������ ������ ���� �� ������ ��� ���� �Լ�
Vector2 GetLaserEndPos(Bullet* bullets);	