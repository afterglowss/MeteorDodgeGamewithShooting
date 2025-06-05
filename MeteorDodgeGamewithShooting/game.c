#include "game.h"
#include "player.h"
#include "meteor.h"

Particle particles[MAX_PARTICLES] = { 0 };

Vector2 RandomDirection() {
    float angle = (float)(rand() % 360) * PI / 180.0f;
    return (Vector2) { cosf(angle), sinf(angle) };
}

void GenerateExplosion(Vector2 position, Color color) {
    // 충돌 시 최대 생성 파편 수만큼 파편 생성, 방향은 랜덤으로 색상은 정해서
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
// 파편 위치 업데이트
void UpdateParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].active) {
            particles[i].position = Vector2Add(particles[i].position, particles[i].velocity);
            if (--particles[i].lifetime <= 0) particles[i].active = false;
        }
    }
}
// 파편 화면에 그리기
void DrawParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].active) {
            float alpha = (float)particles[i].lifetime / PARTICLE_LIFETIME;
            DrawCircleV(particles[i].position, 2.5f, Fade(particles[i].color, alpha));
        }
    }
}
// 게임 상황에 맞춰 UI 그리기
void DrawUI(Player player, int score, bool gameOver, bool gameStarted, int selectedMenu, 
    const char** menuItems, int menuCount, Sound gameOverSound, bool *gameOverSoundPlayed) {
    
    // 시작 전 메인화면 그리기
    if (!gameStarted) {
        DrawText("Meteor Dodge Game", 405, 200, 40, WHITE);
        DrawText("with Shooting", 460, 240, 40, WHITE);
        for (int i = 0; i < menuCount; i++) {
            Color color = (i == selectedMenu) ? ORANGE : WHITE;
            DrawText(menuItems[i], 540, 350 + i * 40, 30, color);
        }
    }
    // 게임이 시작된 동안 필요한 UI 출력
    else {
        DrawText(TextFormat("Lives: %d", player.lives), 10, 10, 20, WHITE);
        DrawText(TextFormat("Score: %d", score), 10, 35, 20, YELLOW);
        // 게임오버 시 게임오버 화면 출력
        if (gameOver) {
            if (!(*gameOverSoundPlayed)) {
                PlaySound(gameOverSound);
                *gameOverSoundPlayed = true;
            }
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.75f));
            DrawText("GAME OVER", 460, 330, 40, RED);
            DrawText(TextFormat("HIGHSCORE: %d", highScore), 450, 375, 30, YELLOW);
            DrawText("Press ENTER to restart", 450, 410, 20, LIGHTGRAY);
            DrawText("Press BACKSPACE to Main", 445, 440, 20, LIGHTGRAY);
        }
    }
}

