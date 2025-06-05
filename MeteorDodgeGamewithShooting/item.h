#pragma once
#include "raylib.h"
#include "player.h"

typedef struct Player Player;


typedef enum {      // ������ Ÿ�� ���������� ����
    STOP_METEOR,
    INVINCIBLE_PLAYER,
    LASER_GUN
} ItemType;

// ������ ����ü ����
typedef struct Item {
    Vector2 position;           // ������ ��ġ
    bool active;                // ������ Ȱ��ȭ ����
    bool isItem;                // �÷��̾ ���� ��������
    ItemType type;              // ������ Ÿ��
    double itemStartTime[3];    // ������ ���� ���� �ð� �����ϴ� �迭
} Item;

void InitItem(Item* item);
void UpdateItem(Item* item, Player* player, Sound invincibleSound, Sound getItemSound, Music gameSceneMusic);
void DrawItem(Item* item);
void DrawStar(Vector2 center, float outerRadius, float innerRadius, float rotationAngleDeg, Color color);
