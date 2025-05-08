#include "game.h"

void DrawUI(int score, int lives) {
	 DrawText(TextFormat("score: %d",score), 10, 10, 20, WHITE);
	 DrawText(TextFormat("lives: %d", lives), 10, 30, 20, WHITE);
}

