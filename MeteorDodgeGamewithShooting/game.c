#include "game.h"
#include "player.h"

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
            DrawRectangle(0, 0, 800, 600, Fade(BLACK, 0.75f));
            DrawText("GAME OVER", 460, 360, 40, RED);
            DrawText("Press ENTER to restart", 450, 410, 20, LIGHTGRAY);
            DrawText("Press BACKSPACE to Main", 445, 440, 20, LIGHTGRAY);
        }
    }
}

