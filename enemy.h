#pragma once

//�G�̐�
const int zigzagEnemyNumber = 25;
const int straightEnemyNumber = 9;
const int shootingEnemyNumber = 10;
const int backEnemyNumber = 13;
const int raidEnemyNumber = 32;
const int IniBackEnemyX = -2300;
const int IniBackEnemyY = 100;
const int fiveHundred = 500;
const int hundredfifteen = 150;
const int zero = 0;

//�\����
typedef struct Enemy
{
    int x1,x2;
    int y1,y2;
    int graph;
    int bullet;
    const int speed = 2;
    bool changeMoveFlag;
    bool isInScreenFlag;
    int explosionCount; //�����G�t�F�N�g�p�J�E���g
    bool explosionFlag; //�����G�t�F�N�g�p�t���O
    bool hitFlag; //�����������Ƃ��m�F����p�̃t���O
}Enemy;

//�\���̂̃v���g�^�C�v�錾
struct Bullet;
struct Player;

//�֐��̃v���g�^�C�v�錾
void DrawTutorialEnemy(Enemy& TutorialEnemy);
void InitializeTutorialEnemy(Enemy& TutorialEnemy,Bullet& TutorialBullet);
void UpdateTutorialEnemy(Enemy& TutorialEnemy);

void InitializeZigzagEnemy(Enemy zigzagEnemy[]);
void UpdateZigzagEnemy(Enemy zigzagEnemy[]);
void DrawZigzagEnemy(Enemy zigzagEnemy[], int explosionEffect[]);

void InitializeStraightEnemy(Enemy straightEnemy[]);
void UpdateStraightEnemy(Enemy straightEnemy[]);
void DrawStraightEnemy(Enemy straightEnemy[], int explosionEffect[]);

void InitializeShootingEnemy(Enemy shootingEemmy[]);
void UpdateShootingEnemy(Enemy shootingEemmy[],int& scroll);
void DrawShootingEnemy(Enemy shootingEnemy[], int explosionEffect[]);

void InitializeBackEnemy(Enemy backEnemy[]);
void UpdateBackEnemy(Enemy backEnemy[],int wave1, int& scroll, Player& player2, int wave3, int wave4);
void DrawBackEnemy(Enemy backEnemy[], int explosionEffect[]);

void InitializeRaidEnemy(Enemy raidEnemy[]);
void UpdateRaidEnemy(Enemy raidEnemy[], int& scroll, int wave2);
void DrawRaidEnemy(Enemy raidEnemy[], int explosionEffect[]);