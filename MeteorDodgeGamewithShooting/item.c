#include "item.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>

#define ITEM_RADIUS 15
#define ITEM_VISIBLE_DURATION 5.0     // �������� �����Ǵ� �ð� (��)
#define ITEM_RESPAWN_DELAY 10.0       // �������� ����� �� �ٽ� ��Ÿ�� �������� ��� �ð� (��)

static double itemActiveTime = 0.0;   // �������� ��Ÿ�� ����
static double lastInactiveTime = 0.0; // �������� ����� ����

void InitItem(Item* item) {
    item->active = false;
    item->position = (Vector2){ 0, 0 };
    //item->type = STOP_METEOR;
    item->type = LASER_GUN;
    itemActiveTime = 0;
    lastInactiveTime = GetTime();  // ������ �� ��Ȱ��ȭ�� ����
}

void UpdateItem(Item* item, Player* player, bool* meteorFreeze, double* freezeStartTime, 
    Sound invincibleSound, Sound getItemSound) {
    double currentTime = GetTime();

    //� �Ͻ����� ������
    // �������� ��Ȱ�� ������ ��, ���� �ð��� ������ �ٽ� ����
    if (!item->active && (currentTime - lastInactiveTime >= ITEM_RESPAWN_DELAY)) {
        item->active = true;
        item->position = (Vector2){ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT };
        //item->type = STOP_METEOR;
        item->type = LASER_GUN;
        itemActiveTime = currentTime;
    }

    // �������� Ȱ�� ������ ��
    if (item->active) {
        // �ð��� �� ������ �ڵ� ��Ȱ��ȭ
        if (currentTime - itemActiveTime >= ITEM_VISIBLE_DURATION) {
            item->active = false;
            lastInactiveTime = currentTime;
            return;
        }

        // �÷��̾ �������� �Ծ����� Ȯ��
        if (CheckCollisionCircles(player->position, PLAYER_SIZE / 2.0f, item->position, ITEM_RADIUS)) {
            switch (item->type)
            {
            //� ���� ������
            case STOP_METEOR:
                *meteorFreeze = true;
                *freezeStartTime = currentTime;

                // � ���� �������� �Ծ��� �� ȿ����
                PlaySound(getItemSound);
                break;

            //������ �� ������
            case LASER_GUN:
                player->laserMode = true;
                player->laserStartTime = currentTime;

                PlaySound(getItemSound);
                break;
            }
            
            item->active = false;
            lastInactiveTime = currentTime;
        }
    }
}

void DrawItem(Item* item) {
    if (!item->active) return;
    DrawCircleLines((int)item->position.x, (int)item->position.y, ITEM_RADIUS, RED);
}
