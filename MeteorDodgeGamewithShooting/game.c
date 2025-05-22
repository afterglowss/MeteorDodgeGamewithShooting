#include "game.h"
#include "player.h"

Particle particles[MAX_PARTICLES] = { 0 };

Vector2 RandomDirection() {
    float angle = (float)(rand() % 360) * PI / 180.0f;
    return (Vector2) { cosf(angle), sinf(angle) };
}

void GenerateExplosion(Vector2 position, Color color) {
    for (int i = 0, spawned = 0; i < MAX_PARTICLES && spawned < PARTICLE_PER_EXPLOSION; i++) {
        if (!particles[i].active) {
            particles[i].position = position;
            particles[i].velocity = Vector2Scale(RandomDirection(), 2 + rand() % 3);
            particles[i].lifetime = PARTICLE_LIFETIME;
            particles[i].active = true;
            particles[i].color = color;
            spawned++;
        }
    }
}

void UpdateParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].active) {
            particles[i].position = Vector2Add(particles[i].position, particles[i].velocity);
            if (--particles[i].lifetime <= 0) particles[i].active = false;
        }
    }
}

void DrawParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].active) {
            float alpha = (float)particles[i].lifetime / PARTICLE_LIFETIME;
            DrawCircleV(particles[i].position, 2.5f, Fade(particles[i].color, alpha));
        }
    }
}

void DrawUI(Player player, int score, bool gameOver, bool gameStarted, int selectedMenu, const char** menuItems, int menuCount) {
    if (!gameStarted) {
        DrawText("Meteor Dodge Game", 405, 200, 40, WHITE);
        DrawText("with Shooting", 460, 240, 40, WHITE);
        for (int i = 0; i < menuCount; i++) {
            Color color = (i == selectedMenu) ? ORANGE : WHITE;
            DrawText(menuItems[i], 540, 350 + i * 40, 30, color);
        }
    }
    else {
        DrawText(TextFormat("Lives: %d", player.lives), 10, 10, 20, WHITE);
        DrawText(TextFormat("Score: %d", score), 10, 35, 20, YELLOW);

        if (gameOver) {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.75f));
            DrawText("GAME OVER", 460, 360, 40, RED);
            DrawText("Press ENTER to restart", 450, 410, 20, LIGHTGRAY);
            DrawText("Press BACKSPACE to Main", 445, 440, 20, LIGHTGRAY);
        }
    }
}

