#include "game.h"
#include "player.h"

void DrawUI(Player player, int score, bool gameOver, bool gameStarted, int selectedMenu, const char** menuItems, int menuCount) {
    if (!gameStarted) {
        DrawText("Meteor Dodge Game", 205, 100, 40, WHITE);
        DrawText("with Shooting", 260, 140, 40, WHITE);
        for (int i = 0; i < menuCount; i++) {
            Color color = (i == selectedMenu) ? ORANGE : WHITE;
            DrawText(menuItems[i], 340, 250 + i * 40, 30, color);
        }
    }
    else {
        DrawText(TextFormat("Lives: %d", player.lives), 10, 10, 20, WHITE);
        DrawText(TextFormat("Score: %d", score), 10, 35, 20, YELLOW);

        if (gameOver) {
            DrawRectangle(0, 0, 800, 600, Fade(BLACK, 0.75f));
            DrawText("GAME OVER", 260, 260, 40, RED);
            DrawText("Press ENTER to restart", 250, 310, 20, LIGHTGRAY);
            DrawText("Press BACKSPACE to Main", 245, 340, 20, LIGHTGRAY);
        }
    }
}

