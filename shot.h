#pragma once

//定数
const int PlayerShotNumber = 5; //プレイヤーの画面内の弾数
const int zigzagEnemyShotNumber = 2; //ジグザグ敵の画面内の弾数
const int shootingEnemyShotNumber = 10; //うちまくる敵の弾数
const int width = 50;
const int height = 50;
const int IniShotPositionY = 35;
const int shootingEnemyBulletSpeed = 90;
const int senn = 1000;

//弾構造体
typedef struct Bullet
{
    int x1, x2;
    int y1, y2;
    int graph;
    const int enemySpeed = 7;
    const int playerSpeed = 20;
    float coordinateReferenceXSpeed; //x座標参照移動量
    float coordinateReferenceYSpeed; //y座標参照移動量
    bool isInScreenFlag; //存在フラグ
    double sb, sbx, sby; //座標参照弾の時に使う変数
}Bullet;

//構造体のプロトタイプ宣言
struct Enemy;
struct Player;

//関数のプロトタイプ宣言
void InitializeTutorialBullet(Bullet& TutorialBullet);
void UpdateTutorialBullet(Bullet& TutorialBullet,Enemy& TutorialEnemy);
void DrawTutorialBullet(Bullet& TutorialBullet);

void InitializePlayerBullet(Bullet PlayerBullet[],int PlayerShotNumber,Player& player1);
void UpdatePlayerBullet(Bullet PlayerBullet[], int PlayerShotNumber,Player& player1, DINPUT_JOYSTATE input, int shotSound, int& remainingBullet);
void DrawPlayerBullet(Bullet PlayerBullet[], int PlayerShotNumber);

void AwakeZigzagEnemyBullet(Bullet& zigzagEnemyBullet);
void InitializeZigzagEnemyBullet(Bullet& zigzagEnemyBullet, Enemy& zigzagEnemy);
void UpdateZigzagEnemyBullet(Bullet& zigzagEnemyBullet);
void DrawZigzagEnemyBullet(Bullet& zigzagEnemyBullet);

void AwakeShootingEnemyBullet(Bullet& shootingEnemyBullet);
void InitializeShootingEnemyBullet(Bullet& shootingEnemyBullet, Enemy& shootingEnemy, Player& player1);
void UpdateShootingEnemyBullet(Bullet& shootingEnemyBullet);
void DrawShootingEnemyBullet(Bullet& shootingEnemyBullet);