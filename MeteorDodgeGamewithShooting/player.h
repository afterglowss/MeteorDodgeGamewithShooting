#pragma once

#define PLAYER_SIZE 20				// �÷��̾� ũ��
#define PLAYER_ACCEL 0.5f			// �÷��̾� ���ӷ�
#define PLAYER_FRICTION 0.9f		// �÷��̾� ������
#define TRAIL_LENGTH 20				// �ܻ� ����
#define INVINCIBLE_TIME 5			// �÷��̾� ���� �ð�

#include "raylib.h"
#include "raymath.h"

typedef struct Item Item;			// ��� �������� ���� ����ü ��Ī�� ���� ����

struct Player
{
	Vector2 position;				// �÷��̾� ��ġ
	Vector2 trail[TRAIL_LENGTH];	// �ܻ� �迭
	Vector2 velocity;				// �÷��̾� �ӵ�
	Vector2 head,left,right;		// �ﰢ���� �÷��̾��� �Ӹ�, ����, ������ ������
	Color playerColor;
	bool isCollision;				// �浹 ���� flag
	double deathTime;				// ����� �ð�
	float angle;					// �÷��̾� ����
	float size;
	int lives;						// �÷��̾� ����
	int trailIdx;
}typedef Player;

void InitPlayer(Player *playerRef);
void UpdatePlayer(Player *playerRef, Item* item);
void DrawPlayer(Player* playerRef, Item* item);

// �÷��̾ �浹 �� ȣ��Ǵ� �Լ�
void PlayerCollision(Player* playerRef);
// �÷��̾ ȭ�� �ٱ����� ������ �� �����ϴ� �Լ�
void ScreenRestrictPlayer(Player* playerRef);