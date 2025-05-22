#pragma once
#include "raylib.h"
#include "player.h"
#define SCREEN_WIDTH 1200  
#define SCREEN_HEIGHT 800

#define MAX_PARTICLES 100
#define PARTICLE_LIFETIME 30
#define PARTICLE_PER_EXPLOSION 10

typedef struct Particle {
    Vector2 position;
    Vector2 velocity;
    int lifetime;
    bool active;
    Color color;
} Particle;

extern Particle particles[MAX_PARTICLES];

void UpdateParticles();
void DrawParticles();
void GenerateExplosion(Vector2 position, Color color);

Vector2 RandomDirection();

void DrawUI(Player player, int score, bool gameOver, bool gameStarted, int selectedMenu, const char** menuItems, int menuCount);