#include "raylib.h"
#include "game.h"
#include "player.h"
#include "meteor.h"
#include "bullet.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Meteor Dodge Game With Shooting");
    SetTargetFPS(60);

    Player player;
    InitPlayer(&player);

    Meteor meteors[MAX_METEORS];
    InitMeteors(meteors);

    Bullet bullets[MAX_BULLETS] = { 0 };

    bool gameStarted = false;
    bool gameOver = false;
    int selectedMenu = 0;
    const char* menuItems[] = { "Start", "Score", "Credits", "Exit" };
    const int menuCount = 4;

    int score = 0;
    //int highScore = 0;  // 전역변수로 관리 필요, meteor.c에서부터 정의를 넣는 게 좋을듯

    while (!WindowShouldClose())
    {
        if (gameStarted && IsKeyPressed(KEY_BACKSPACE)) {
            gameStarted = false;
            continue;
        }
        //게임 시작 전
        if (!gameStarted) {     
            BeginDrawing();
            ClearBackground(BLACK);
            DrawUI(player, score, gameOver, gameStarted, selectedMenu, menuItems, menuCount);
            EndDrawing();

            if (IsKeyPressed(KEY_DOWN)) selectedMenu = (selectedMenu + 1) % menuCount;
            else if (IsKeyPressed(KEY_UP)) selectedMenu = (selectedMenu - 1 + menuCount) % menuCount;
            // 메뉴 중 하나를 고른 경우
            else if (IsKeyPressed(KEY_ENTER)) {
                // Start 버튼 Enter
                if (selectedMenu == 0) {
                    // 게임 시작 상황
                    gameStarted = true;
                    // 플레이어 초기화
                    InitPlayer(&player);
                    // 운석 초기화
                    InitMeteors(meteors);
                    // 총알 전부 비활성화
                    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = false;
                    // 총알 쿨타임, 점수, 점수에 따른 운석 속도 초기화 (=0) 필요
                    score = 0;
                    gameOver = false;
                }
                // Score 버튼 엔터
                else if (selectedMenu == 1) {
                    while (!WindowShouldClose()) {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        // 최고점수 보여주기
                        DrawText(TextFormat("High Score: %d", highScore), 450, 360, 30, YELLOW);
                        DrawText("Press ENTER to return", 430, 420, 20, LIGHTGRAY);
                        EndDrawing();
                        // 엔터 치면 이전 메뉴로 돌아가기
                        if (IsKeyPressed(KEY_ENTER)) break;
                    }
                }
                // Credits 버튼 엔터
                else if (selectedMenu == 2) {
                    while (!WindowShouldClose()) {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        DrawText("Created by Team", 430, 300, 30, YELLOW);
                        DrawText("22011848 Shin Hyewon", 430, 350, 20, WHITE);
                        DrawText("21011777 Im Wookyun", 430, 370, 20, WHITE);
                        DrawText("22011796 Woo Jiwon", 430, 390, 20, WHITE);
                        DrawText("22011813 Cha Seoyeung", 430, 410, 20, WHITE);
                        DrawText("Press ENTER to return", 430, 460, 20, LIGHTGRAY);
                        EndDrawing();
                        if (IsKeyPressed(KEY_ENTER)) break;
                    }
                }
                //Exit 버튼 엔터
                else if (selectedMenu == 3) {
                    CloseWindow();
                    return 0;
                }
            }
            continue;
        }
        // 게임은 시작이 됐고, game over 는 아닐 경우
        if (!gameOver) {
            // 반복문 안에서 Update 함수 계속 호출
            UpdatePlayer(&player);
            UpdateBullets(bullets);
            UpdateMeteors(meteors, &player, bullets, &score);
            UpdateParticles();

            if (IsKeyDown(KEY_SPACE)) {
                FireBullet(bullets, &player);
            }
            if (IsKeyPressed(KEY_A)) {
                gameOver = true;
            }

        }
        // gameStarted = true, gameOver = true 게임오버 화면 상태에서 엔터키로 바로 재시작
        else if (IsKeyPressed(KEY_ENTER)) {
            InitPlayer(&player);
            InitMeteors(meteors);
            // 총알 전부 비활성화
            for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = false;
            // score 초기화
            score = 0;
            gameOver = false;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawPlayer(&player);
        DrawMeteors(meteors);
        DrawBullets(bullets);
        DrawParticles();
        DrawUI(player, score, gameOver, gameStarted, selectedMenu, menuItems, menuCount);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
