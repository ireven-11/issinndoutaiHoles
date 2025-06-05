#pragma once

//�萔
const int PlayerShotNumber = 5; //�v���C���[�̉�ʓ��̒e��
const int zigzagEnemyShotNumber = 2; //�W�O�U�O�G�̉�ʓ��̒e��
const int shootingEnemyShotNumber = 10; //�����܂���G�̒e��
const int width = 50;
const int height = 50;
const int IniShotPositionY = 35;
const int shootingEnemyBulletSpeed = 90;
const int senn = 1000;

//�e�\����
typedef struct Bullet
{
    int x1, x2;
    int y1, y2;
    int graph;
    const int enemySpeed = 7;
    const int playerSpeed = 20;
    float coordinateReferenceXSpeed; //x���W�Q�ƈړ���
    float coordinateReferenceYSpeed; //y���W�Q�ƈړ���
    bool isInScreenFlag; //���݃t���O
    double sb, sbx, sby; //���W�Q�ƒe�̎��Ɏg���ϐ�
}Bullet;

//�\���̂̃v���g�^�C�v�錾
struct Enemy;
struct Player;

//�֐��̃v���g�^�C�v�錾
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