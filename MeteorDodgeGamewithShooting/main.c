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

    // ����� �ʱ�ȭ
    InitAudioDevice();

    //���� ȭ�� bgm
    Music mainSceneMusic = LoadMusicStream("resources/mainSceneMusic.wav");
    SetMusicVolume(mainSceneMusic, 1.0f);
    //���� ȭ�� bgm
    Music gameSceneMusic = LoadMusicStream("resources/gameSceneMusic.wav");
    SetMusicVolume(gameSceneMusic, 1.0f);
    //�Ѿ� �߻� sound
    Sound fireSound = LoadSound("resources/fire.wav");
    SetSoundVolume(fireSound, 0.1f);
    //���� ���� sound
    Sound gameOverSound = LoadSound("resources/gameOver.wav");
    SetSoundVolume(gameOverSound, 1.0f);
    //�޴� �̵� sound
    Sound menuSound = LoadSound("resources/menu.wav");
    SetSoundVolume(menuSound, 0.3f);
    //�-�÷��̾� �浹 sound
    Sound collisionPlayerSound = LoadSound("resources/collisionPlayer.wav");
    SetSoundVolume(collisionPlayerSound, 0.2f);
    //�-�Ѿ� �浹 sound
    Sound collisionBulletSound = LoadSound("resources/collisionBullet.wav");
    SetSoundVolume(collisionBulletSound, 0.2f);
    //������
    Sound laserSound = LoadSound("resources/laser.wav");
    SetSoundVolume(laserSound, 0.1f);
    //����
    Sound invincibleSound = LoadSound("resources/invincible.wav");
    SetSoundVolume(invincibleSound, 0.5f);
    //������ ȹ�� (� ����, ������ ������ ȹ�� �� ����)
    Sound getItemSound = LoadSound("resources/getItem.wav");
    SetSoundVolume(getItemSound, 0.5f);


    Player player;
    InitPlayer(&player);

    Meteor meteors[MAX_METEORS];
    InitMeteors(meteors);

    Bullet bullets[MAX_BULLETS] = { 0 };

    //������ �߰�
    Item item;
    InitItem(&item);
    bool meteorFreeze = false;
    double freezeStartTime = 0.0;

    //���� ���� flag
    bool gameOverSoundPlayed = false;

    bool gameStarted = false;
    bool gameOver = false;
    int selectedMenu = 0;
    const char* menuItems[] = { "Start", "Score", "Credits", "Exit" };
    const int menuCount = 4;

    int score = 0;

    while (!WindowShouldClose())
    {
        if (gameStarted && IsKeyPressed(KEY_BACKSPACE)) {
            gameStarted = false;
            continue;
        }

        //���� ���� ��
        if (!gameStarted) {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawUI(player, score, gameOver, gameStarted, selectedMenu, menuItems,
                menuCount, gameOverSound, &gameOverSoundPlayed);
            EndDrawing();

            if (!IsMusicStreamPlaying(mainSceneMusic)) {
                PlayMusicStream(mainSceneMusic);
            }
            //���� ȭ�� bgm �����ؼ� ��Ʈ����
            UpdateMusicStream(mainSceneMusic);

            if (IsKeyPressed(KEY_DOWN)) {
                PlaySound(menuSound);
                selectedMenu = (selectedMenu + 1) % menuCount;
            }
            else if (IsKeyPressed(KEY_UP)) {
                PlaySound(menuSound);
                selectedMenu = (selectedMenu - 1 + menuCount) % menuCount;
            }
            // �޴� �� �ϳ��� �� ���
            else if (IsKeyPressed(KEY_ENTER)) {
                // Start ��ư Enter
                if (selectedMenu == 0) {
                    // ���� ���� ��Ȳ
                    gameStarted = true;
                    // �÷��̾� �ʱ�ȭ
                    InitPlayer(&player);
                    // � �ʱ�ȭ
                    InitMeteors(meteors);

                    //������ �ʱ�ȭ
                    InitItem(&item);

                    // �Ѿ� ���� ��Ȱ��ȭ
                    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = false;
                    // �浹 ��ƼŬ ��Ȱ��ȭ
                    for (int i = 0; i < MAX_PARTICLES; i++) particles[i].active = false;
                    // �Ѿ� ��Ÿ��, ����, ������ ���� � �ӵ� �ʱ�ȭ (=0) �ʿ�
                    score = 0;
                    gameOver = false;
                    //���� ���� ���� ��� ���� �Ǵܿ� �ʿ��� flag false
                    gameOverSoundPlayed = false;

                }
                // Score ��ư ����
                else if (selectedMenu == 1) {
                    while (!WindowShouldClose()) {
                        BeginDrawing();
                        ClearBackground(BLACK);

                        if (!IsMusicStreamPlaying(mainSceneMusic)) {
                            PlayMusicStream(mainSceneMusic);
                        }
                        UpdateMusicStream(mainSceneMusic);

                        // �ְ����� �����ֱ�
                        DrawText(TextFormat("High Score: %d", highScore), 450, 360, 30, YELLOW);
                        DrawText("Press ENTER to return", 430, 420, 20, LIGHTGRAY);
                        EndDrawing();
                        // ���� ġ�� ���� �޴��� ���ư���
                        if (IsKeyPressed(KEY_ENTER)) break;
                    }
                }
                // Credits ��ư ����
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
                //Exit ��ư ����
                else if (selectedMenu == 3) {
                    CloseWindow();
                    return 0;
                }
            }
            continue;
        }
        // ������ ������ �ư�, game over �� �ƴ� ���
        if (!gameOver) {
            // �ݺ��� �ȿ��� Update �Լ� ��� ȣ��
            UpdatePlayer(&player, &item);
            UpdateBullets(bullets);
            UpdateMeteors(meteors, &player, bullets, &score, &gameOver,
                &item, collisionBulletSound, collisionPlayerSound);
            UpdateParticles();


            //������ ������Ʈ
            UpdateItem(&item, &player, invincibleSound, getItemSound);

            //bgm ��� �� ��Ʈ����
            if (!IsMusicStreamPlaying(gameSceneMusic)) {
                StopMusicStream(gameSceneMusic);
                PlayMusicStream(gameSceneMusic);
            }
            UpdateMusicStream(gameSceneMusic);

            if (IsKeyDown(KEY_SPACE)) {
                //if (!IsSoundPlaying(fire)) PlaySound(fire);
                FireBulletOrLaser(bullets, &player, &item, fireSound);
            }
        }

        // gameStarted = true, gameOver = true ���ӿ��� ȭ�� ���¿��� ����Ű�� �ٷ� �����
        else if (IsKeyPressed(KEY_ENTER)) {
            InitPlayer(&player);
            InitMeteors(meteors);
            // �Ѿ� ���� ��Ȱ��ȭ
            for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = false;
            // �浹 ��ƼŬ ��Ȱ��ȭ
            for (int i = 0; i < MAX_PARTICLES; i++) particles[i].active = false;
            // score �ʱ�ȭ
            score = 0;
            gameOver = false;
            gameOverSoundPlayed = false;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawPlayer(&player,&item);
        DrawMeteors(meteors);
        DrawBullets(bullets, &item);

        //������ �׸���
        DrawItem(&item);

        DrawParticles();
        DrawUI(player, score, gameOver, gameStarted, selectedMenu, menuItems,
            menuCount, gameOverSound, &gameOverSoundPlayed);
        EndDrawing();
    }

    // ȿ���� �Ҵ� ����
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