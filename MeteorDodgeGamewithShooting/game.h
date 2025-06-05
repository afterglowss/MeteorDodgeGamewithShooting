#pragma once
#include "raylib.h"
#include "player.h"

#define SCREEN_WIDTH 1200           // 화면 가로 크기
#define SCREEN_HEIGHT 800           // 화면 세로 크기

#define MAX_PARTICLES 100           // 최대 충돌 파편 객체 수
#define PARTICLE_LIFETIME 30        // 파편 생존 시각
#define PARTICLE_PER_EXPLOSION 10   // 충돌마다 생성되는 파편 수

// 파편 구조체
typedef struct Particle {
    Vector2 position;
    Vector2 velocity;
    int lifetime;
    bool active;
    Color color;
} Particle;

// 파편 배열 전역변수로 선언
extern Particle particles[MAX_PARTICLES];

void UpdateParticles();
void DrawParticles();
// 충돌 시 파편 생성하는 함수
void GenerateExplosion(Vector2 position, Color color);
// 무작위 방향 생성 함수
Vector2 RandomDirection();
// 게임 전체 UI 작성하는 함수
void DrawUI(Player player, int score, bool gameOver, bool gameStarted, int selectedMenu, 
    const char** menuItems, int menuCount, Sound gameOverSound, bool *gameOverSoundPlayed);