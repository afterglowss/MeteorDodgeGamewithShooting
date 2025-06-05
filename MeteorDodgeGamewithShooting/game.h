#pragma once
#include "raylib.h"
#include "player.h"

#define SCREEN_WIDTH 1200           // ȭ�� ���� ũ��
#define SCREEN_HEIGHT 800           // ȭ�� ���� ũ��

#define MAX_PARTICLES 100           // �ִ� �浹 ���� ��ü ��
#define PARTICLE_LIFETIME 30        // ���� ���� �ð�
#define PARTICLE_PER_EXPLOSION 10   // �浹���� �����Ǵ� ���� ��

// ���� ����ü
typedef struct Particle {
    Vector2 position;
    Vector2 velocity;
    int lifetime;
    bool active;
    Color color;
} Particle;

// ���� �迭 ���������� ����
extern Particle particles[MAX_PARTICLES];

void UpdateParticles();
void DrawParticles();
// �浹 �� ���� �����ϴ� �Լ�
void GenerateExplosion(Vector2 position, Color color);
// ������ ���� ���� �Լ�
Vector2 RandomDirection();
// ���� ��ü UI �ۼ��ϴ� �Լ�
void DrawUI(Player player, int score, bool gameOver, bool gameStarted, int selectedMenu, 
    const char** menuItems, int menuCount, Sound gameOverSound, bool *gameOverSoundPlayed);