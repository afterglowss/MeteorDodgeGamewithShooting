#pragma once
#include "raylib.h"
#include "raymath.h"
#include "game.h"
#include "player.h"
#include "bullet.h"
#include <stdlib.h>
#include <time.h>
#include "item.h"

#define MAX_METEORS 40		// �ִ� � ��
#define MIN_BRIGHT 100		// �ּ� ���
#define STOPMETEOR_TIME 5	// � ���� ������ �ð�

extern int highScore;		// ���� ���� �� ���� �ִ� ���� ���������� ����

typedef struct Meteor {
	Vector2 position;		// � ��ġ
	Vector2 velocity;		// � �ӵ�
	Color color;			// � ����
	float radius;			// � ������
}Meteor;

void InitMeteors(Meteor* meteors);
void UpdateMeteors(Meteor* meteors, Player* playerRef, Bullet* bullets, int* score, bool* gameOver,
	Item* item, Sound collisionBullet, Sound collisionPlayer);
void DrawMeteors(Meteor* meteors);
void RespawnMeteor(Meteor* m, int index);