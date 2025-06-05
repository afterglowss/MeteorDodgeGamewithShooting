#include "raylib.h"
#include "game.h"
#include "player.h"
#include "meteor.h"
#include "bullet.h"
#include "item.h"
int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Meteor Dodge Game With Shooting");
    SetTargetFPS(60);

    // 오디오 초기화
    InitAudioDevice();

    // 메인 화면 bgm
    Music mainSceneMusic = LoadMusicStream("resources/mainSceneMusic.wav");
    SetMusicVolume(mainSceneMusic, 1.0f);
    // 게임 화면 bgm
    Music gameSceneMusic = LoadMusicStream("resources/gameSceneMusic.wav");
    SetMusicVolume(gameSceneMusic, 1.0f);
    // 총알 발사 sound
    Sound fireSound = LoadSound("resources/fire.wav");
    SetSoundVolume(fireSound, 0.1f);
    // 게임 오버 sound
    Sound gameOverSound = LoadSound("resources/gameOver.wav");
    SetSoundVolume(gameOverSound, 1.0f);
    // 메뉴 이동 sound
    Sound menuSound = LoadSound("resources/menu.wav");
    SetSoundVolume(menuSound, 0.3f);
    // 운석-플레이어 충돌 sound
    Sound collisionPlayerSound = LoadSound("resources/collisionPlayer.wav");
    SetSoundVolume(collisionPlayerSound, 0.2f);
    // 운석-총알 충돌 sound
    Sound collisionBulletSound = LoadSound("resources/collisionBullet.wav");
    SetSoundVolume(collisionBulletSound, 0.2f);
    // 레이저
    Sound laserSound = LoadSound("resources/laser.wav");
    SetSoundVolume(laserSound, 0.1f);
    // 무적
    Sound invincibleSound = LoadSound("resources/invincible.wav");
    SetSoundVolume(invincibleSound, 0.5f);
    // 아이템 획득 (운석 정지, 레이저 아이템 획득 시 적용)
    Sound getItemSound = LoadSound("resources/getItem.wav");
    SetSoundVolume(getItemSound, 0.5f);

    // 플레이어 초기화
    Player player;
    InitPlayer(&player);

    // 운석 초기화
    Meteor meteors[MAX_METEORS];
    InitMeteors(meteors);

    // 총알 배열 초기화
    Bullet bullets[MAX_BULLETS] = { 0 };

    // 아이템 초기화
    Item item;
    InitItem(&item);

    // 아이템 변수 초기화
    bool meteorFreeze = false;
    double freezeStartTime = 0.0;

    // 사운드 관련 flag
    bool gameOverSoundPlayed = false;

    // 게임 상태 관리 변수 초기화
    bool gameStarted = false;
    bool gameOver = false;

    // 메뉴
    int selectedMenu = 0;
    const char* menuItems[] = { "Start", "Score", "Credits", "Exit" };
    const int menuCount = 4;

    // 현재 점수 초기화
    int score = 0;

    // 프로그램 실행 반복문 (esc 버튼 누르기 전까지 계속 반복)
    while (!WindowShouldClose())
    {
        // 게임이 시작된 상태에서 BackSpace를 눌렀을 경우
        if (gameStarted && IsKeyPressed(KEY_BACKSPACE)) {
            // 게임 종료 (메뉴로 돌아가기)
            gameStarted = false;
            // 재생되고 있을 수 있는 효과음 전부 종료
            if (IsSoundPlaying(gameOverSound)) StopSound(gameOverSound);
            if (IsSoundPlaying(getItemSound)) StopSound(getItemSound);
            if (IsSoundPlaying(invincibleSound)) StopSound(invincibleSound);

            continue;
        }
        // 게임 시작 전 메인화면
        if (!gameStarted) {
            // 프레임 시작 raylib 함수
            BeginDrawing();
            ClearBackground(BLACK);
            // UI 그리기
            DrawUI(player, score, gameOver, gameStarted, selectedMenu, menuItems,
                menuCount, gameOverSound, &gameOverSoundPlayed);
            EndDrawing();

            //메인 화면 bgm 스트리밍
            if (!IsMusicStreamPlaying(mainSceneMusic)) {
                PlayMusicStream(mainSceneMusic);
            }
            // 메인 화면 bgm 지속해서 스트리밍
            UpdateMusicStream(mainSceneMusic);

            // 메뉴 이동
            if (IsKeyPressed(KEY_DOWN)) {
                PlaySound(menuSound);
                selectedMenu = (selectedMenu + 1) % menuCount;
            }
            else if (IsKeyPressed(KEY_UP)) {
                PlaySound(menuSound);
                selectedMenu = (selectedMenu - 1 + menuCount) % menuCount;
            }

            // 메뉴 중 하나를 고른 경우
            else if (IsKeyPressed(KEY_ENTER)) {
                // Start 버튼 Enter
                if (selectedMenu == 0) {
                    // 게임 시작 상태 표시
                    gameStarted = true;
                    // 필요 구조체 전부 초기화
                    InitPlayer(&player);
                    InitMeteors(meteors);
                    InitItem(&item);

                    // 총알 전부 비활성화
                    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = false;
                    // 충돌 파티클 비활성화
                    for (int i = 0; i < MAX_PARTICLES; i++) particles[i].active = false;
                    // 현재 점수 초기화
                    score = 0;
                    //게임 상태 변경
                    gameOver = false;
                    // 게임 오버 사운드 재생 여부 판단에 필요한 flag false
                    gameOverSoundPlayed = false;

                }
                // Score 버튼 엔터
                else if (selectedMenu == 1) {
                    while (!WindowShouldClose()) {
                        BeginDrawing();
                        ClearBackground(BLACK);

                        if (!IsMusicStreamPlaying(mainSceneMusic)) {
                            PlayMusicStream(mainSceneMusic);
                        }
                        UpdateMusicStream(mainSceneMusic);

                        // 최고점수 보여주기
                        DrawText(TextFormat("High Score: %d", highScore), 450, 360, 30, YELLOW);
                        DrawText("Press ENTER to return", 430, 420, 20, LIGHTGRAY);
                        EndDrawing();
                        // 엔터 치면 메뉴로 돌아가기
                        if (IsKeyPressed(KEY_ENTER)) break;
                    }
                }
                // Credits 버튼 엔터
                else if (selectedMenu == 2) {
                    while (!WindowShouldClose()) {
                        BeginDrawing();
                        ClearBackground(BLACK);

                        if (!IsMusicStreamPlaying(mainSceneMusic)) {
                            PlayMusicStream(mainSceneMusic);
                        }
                        UpdateMusicStream(mainSceneMusic);

                        DrawText("Created by Team", 430, 300, 30, YELLOW);
                        DrawText("22011848 Shin Hyewon", 430, 350, 20, WHITE);
                        DrawText("21011777 Lim Woogyun", 430, 370, 20, WHITE);
                        DrawText("22011796 Woo Jiwon", 430, 390, 20, WHITE);
                        DrawText("22011813 Cha Seoyeong", 430, 410, 20, WHITE);
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
            // 반복문 안에서 각 객체 Update 함수 계속 호출
            UpdatePlayer(&player, &item);
            UpdateBullets(bullets);
            UpdateMeteors(meteors, &player, bullets, &score, &gameOver,
                &item, collisionBulletSound, collisionPlayerSound);
            UpdateParticles();

            // 아이템 업데이트
            UpdateItem(&item, &player, invincibleSound, getItemSound, gameSceneMusic);

            // bgm 재생 및 스트리밍 (단, 무적 아이템 획득 시 잠깐 멈추기)
            if (!IsMusicStreamPlaying(gameSceneMusic) && (!item.isItem || item.type != INVINCIBLE_PLAYER)) {
                PlayMusicStream(gameSceneMusic);
            }
            UpdateMusicStream(gameSceneMusic);

            if (IsKeyDown(KEY_SPACE)) {
                // if (!IsSoundPlaying(fire)) PlaySound(fire);
                FireBulletOrLaser(bullets, &player, &item, fireSound);
            }
        }

        // gameStarted = true, gameOver = true 게임오버 화면 상태에서 엔터키로 바로 재시작
        else if (IsKeyPressed(KEY_ENTER)) {
            InitPlayer(&player);
            InitMeteors(meteors);
            InitItem(&item);
            // 총알 전부 비활성화
            for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = false;
            // 충돌 파티클 비활성화
            for (int i = 0; i < MAX_PARTICLES; i++) particles[i].active = false;
            // score 초기화
            score = 0;
            gameOver = false;
            gameOverSoundPlayed = false;

            // 재생되고 있을 수 있는 효과음 전부 종료
            if (IsSoundPlaying(gameOverSound)) StopSound(gameOverSound);
            if (IsSoundPlaying(getItemSound)) StopSound(getItemSound);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // 지속적으로 화면에 그리기
        DrawPlayer(&player,&item);
        DrawMeteors(meteors);
        DrawBullets(bullets, &item);
        DrawParticles();

        // 아이템 그리기
        DrawItem(&item);

        DrawUI(player, score, gameOver, gameStarted, selectedMenu, menuItems,
            menuCount, gameOverSound, &gameOverSoundPlayed);
        EndDrawing();
    }

    // 효과음 할당 해제
    UnloadMusicStream(mainSceneMusic);
    UnloadMusicStream(gameSceneMusic);
    UnloadSound(fireSound);
    UnloadSound(menuSound);
    UnloadSound(collisionBulletSound);
    UnloadSound(collisionPlayerSound);
    UnloadSound(laserSound);
    UnloadSound(invincibleSound);
    UnloadSound(getItemSound);


    CloseAudioDevice();
    CloseWindow();
    return 0;
}