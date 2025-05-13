#include "raylib.h"
#include "player.h"
#define SCREEN_WIDTH 1200  
#define SCREEN_HEIGHT 800

void DrawUI(Player player, int score, bool gameOver, bool gameStarted, int selectedMenu, const char** menuItems, int menuCount);