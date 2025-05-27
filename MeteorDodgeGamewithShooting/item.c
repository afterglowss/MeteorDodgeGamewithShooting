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
    itemActiveTime = 0;
    lastInactiveTime = GetTime();  // ������ �� ��Ȱ��ȭ�� ����
    for (int i = 0; i < 3; i++) item->itemStartTime[i] = 0;
}

void UpdateItem(Item* item, Player* player, Sound invincibleSound, Sound getItemSound) {
    double currentTime = GetTime();

    //� �Ͻ����� ������
    // �������� ��Ȱ�� ������ ��, ���� �ð��� ������ �ٽ� ����
    if (!item->active && (currentTime - lastInactiveTime >= ITEM_RESPAWN_DELAY)) {
        item->active = true;
        item->position = (Vector2){ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT };
        //������ ���� ����
        int itemIdx = rand() % 3;
        
        switch (itemIdx)
        {
        case 0:
            item->type = STOP_METEOR;
            break;
        case 1:
            item->type = LASER_GUN;
            break;
        case 2:
            item->type = INVINCIBLE_PLAYER;
            break;
        default:
            break;
        }
        
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
        lastInactiveTime = currentTime;

        // �÷��̾ �������� �Ծ����� Ȯ��
        if (CheckCollisionCircles(player->position, PLAYER_SIZE / 2.0f, item->position, ITEM_RADIUS)) {

            switch (item->type)
            {
            case STOP_METEOR:
                item->itemStartTime[0] = currentTime;
            case LASER_GUN:
                item->itemStartTime[1] = currentTime;
            case INVINCIBLE_PLAYER:
                item->itemStartTime[2] = currentTime;
            default:
                break;
            }
            PlaySound(getItemSound);
            item->isItem = true;
            item->active = false;
            lastInactiveTime = currentTime;
        }
    }
}

void DrawItem(Item* item) {
    if (!item->active) return;
    DrawCircleLines((int)item->position.x, (int)item->position.y, ITEM_RADIUS, RED);
}
