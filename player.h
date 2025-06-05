#pragma once

const int healBullet = 5; //弾回復量
const int player2Widht = 125; //黒の幅
const int suctionWidht = 250; //吸い込み幅
const int suctionHeight = 205; //吸い込み高さ
const int MaxremainingBullet = 80; //弾上限

//構造体
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

//構造体のプロトタイプ宣言
struct Bullet;

//関数のプロトタイプ宣言
void UpdatePlayer(Player& player1,Player& player2, DINPUT_JOYSTATE input, Bullet zigzagEnemyBullet[], int& scoreMagnificatoin, int suctionSound, int succeedSuctionSound, int& remainingBullet, Bullet shootingEnemyBullet[], bool blockFlag[], int blockX1[], int blockX2[], int blockY1[], int blockY2[], int& scroll, int wave4, bool& suctionSucceedEffectFlag);
void InitializePlayer(Player& player1, Player& player2);
void DrawPlayer(Player& player1, Player& player2, DINPUT_JOYSTATE input, int suctionEffect[], int& suctionEffectCount, bool& invincibleFlag, int& invincibleTimeCount, bool& suctionSucceedEffectFlag, int& suctionSucceedEffectCount, int suctionSucceedEffect[], int Lstick, int Rstick);
void ProConOrXBoxCon(bool isPro);