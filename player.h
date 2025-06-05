#pragma once

const int healBullet = 5; //�e�񕜗�
const int player2Widht = 125; //���̕�
const int suctionWidht = 250; //�z�����ݕ�
const int suctionHeight = 205; //�z�����ݍ���
const int MaxremainingBullet = 80; //�e���

//�\����
typedef struct Player
{
    int x;
    int y;
    const int speed = 9;
    int normalgraph;
    int actiongraph;
    bool PrevShotFlag;
    bool isInScreenFlag;
}Player;

//�\���̂̃v���g�^�C�v�錾
struct Bullet;

//�֐��̃v���g�^�C�v�錾
void UpdatePlayer(Player& player1,Player& player2, DINPUT_JOYSTATE input, Bullet zigzagEnemyBullet[], int& scoreMagnificatoin, int suctionSound, int succeedSuctionSound, int& remainingBullet, Bullet shootingEnemyBullet[], bool blockFlag[], int blockX1[], int blockX2[], int blockY1[], int blockY2[], int& scroll, int wave4, bool& suctionSucceedEffectFlag);
void InitializePlayer(Player& player1, Player& player2);
void DrawPlayer(Player& player1, Player& player2, DINPUT_JOYSTATE input, int suctionEffect[], int& suctionEffectCount, bool& invincibleFlag, int& invincibleTimeCount, bool& suctionSucceedEffectFlag, int& suctionSucceedEffectCount, int suctionSucceedEffect[], int Lstick, int Rstick);
void ProConOrXBoxCon(bool isPro);