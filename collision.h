#pragma once

//定数
const int overDamage = 4;
const int hyakunizyuugo = 100;
const int nizyuugo = 50;
const int hyakugozyuu = 125;
const int hyakunanazyuugo = 150;

//構造体のプロトタイプ宣言
struct Enemy;

void hitPlayerBullet(Bullet PlayerBullet[], int PlayerShotNumber, Player& blackPlayer, Enemy zigzagEnemy[], int& score, Enemy straightEnemy[], Enemy shootingEnemy[], Enemy backEnemy[], Enemy raidEnemy[], int blockHP[], bool blockFlag[], int blockX1[], int blockX2[], int blockY1[], int blockY2[],int explosionSound);
void gameOver(Bullet zigzagEnemyBullet[], Player& whitePlayer, int bgm, int suctionSound, int succeedSuctionSound, Enemy backEnemy[], Player blackPlayer, int playerDeathSound, int& selectscene, Enemy shootingEnemy[], Bullet shootingEnemyBullet[], Enemy straightEnemy[], Enemy zigzagEnemy[], Enemy raidEnemy[], int skullEffect[], int& damage, bool& invincibleFlag);