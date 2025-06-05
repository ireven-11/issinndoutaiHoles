#include"Dxlib.h"
#include"shot.h"
#include"enemy.h"
#include"player.h"
#include<math.h>

//�`���[�g���A���e������
void InitializeTutorialBullet(Bullet& TutorialBullet)
{
    //�摜�ǂݍ���
    TutorialBullet.graph = LoadGraph("img/tama1.png");

    //�e�̑��݃t���O��false�ɂ���
    TutorialBullet.isInScreenFlag = false;
}

//�`���[�g���A���e���[�`��
void UpdateTutorialBullet(Bullet& TutorialBullet,Enemy& TutorialEnemy)
{
    //�e�̔���
    if (!TutorialBullet.isInScreenFlag)
    {
        TutorialBullet.isInScreenFlag = true;
        TutorialBullet.x1 = TutorialEnemy.x1 - 50;
        TutorialBullet.x2 = TutorialEnemy.x1;
        TutorialBullet.y1 = TutorialEnemy.y1 + 25;
        TutorialBullet.y2 = TutorialEnemy.y2 - 25;
    }

    //�e�̈ړ�
    if (TutorialBullet.isInScreenFlag)
    {
        TutorialBullet.x1 -= TutorialBullet.enemySpeed;
        TutorialBullet.x2 -= TutorialBullet.enemySpeed;
        //�e����ʊO�ɏo�������
        if (TutorialBullet.x1 < 0)
        {
            TutorialBullet.isInScreenFlag = false;
        }
    }
}

//�`���[�g���A���e�`��
void DrawTutorialBullet(Bullet& TutorialBullet)
{
    //�t���O��true�̂Ƃ��ɒe��`��
    if (TutorialBullet.isInScreenFlag)
    {
        DrawExtendGraph(TutorialBullet.x2, TutorialBullet.y1, TutorialBullet.x1, TutorialBullet.y2, TutorialBullet.graph, TRUE);
    }
}

//�v���C���[�e������
void InitializePlayerBullet(Bullet PlayerBullet[],int PlayerShotNumber, Player& player1)
{
    //1�񂾂��摜��ǂݍ���
    int tama2Graph = LoadGraph("img/tama2.png");

    for (int i = 0; i < PlayerShotNumber; i++)
    {
        //�摜����
        PlayerBullet[i].graph = tama2Graph;

        //�e�̃t���O��false(��ʓ��ɑ��݂��Ȃ����)�ɂ���
        PlayerBullet[i].isInScreenFlag = false;   
    }

    //�V���b�g�{�^�����O�t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ���false(������Ă��Ȃ����)����
    player1.PrevShotFlag = false;
}

//�v���C���[�e���[�`��
void UpdatePlayerBullet(Bullet PlayerBullet[], int PlayerShotNumber , Player& player1, DINPUT_JOYSTATE input, int shotSound,int& remainingBullet)
{
    //�R���g���[���[�̓��͏�Ԃ��擾
    GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

    //RB�{�^�����������Ƃ��Ɏˌ�����
    if (input.Buttons[5] > 0 && remainingBullet > 0 || input.Buttons[7] > 0 && remainingBullet > 0)
    {
        //�O�t���[���ŃV���b�g�{�^�������������̃t���O��false��������e�𔭎�
        if (player1.PrevShotFlag == false)
        {
            //��ʏ�ɏo�ĂȂ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
            for (int i = 0; i < PlayerShotNumber; i++)
            {
                //�ei����ʏ�ɂłĂȂ��ꍇ�͒e�𔭎˂���
                if (!PlayerBullet[i].isInScreenFlag)
                {
                    //�ˌ����ʉ�
                    PlaySoundMem(shotSound, DX_PLAYTYPE_BACK, TRUE);

                    //����
                    PlayerBullet[i].x1 = player1.x + 100;
                    PlayerBullet[i].y1 = player1.y + 95;
                    PlayerBullet[i].x2 = PlayerBullet[i].x1 + 25;
                    PlayerBullet[i].y2 = PlayerBullet[i].y1 + 15;
                    PlayerBullet[i].isInScreenFlag = true;

                    //�c�e�������炷
                    remainingBullet--;

                    //��̒e�𔭎˂����̂Ń��[�v���瓦����
                    break;
                }
            }
        }

        //�O�t���[���ŃV���b�g�{�^����������Ă������̃t���O��true����
        player1.PrevShotFlag = true;
    }
    else
    {
        //�V���b�g�{�^����������Ă��Ȃ������ꍇ��false����
        player1.PrevShotFlag = false;
    }

    for (int i = 0; i < PlayerShotNumber; i++)
    {
        //�e�̈ړ�
        PlayerBullet[i].x1 += PlayerBullet[i].playerSpeed;
        PlayerBullet[i].x2 += PlayerBullet[i].playerSpeed;
    }
}    

//�v���C���[�e�`��
void DrawPlayerBullet(Bullet PlayerBullet[],int PlayerShotNumber)
{
    for (int i = 0; i < PlayerShotNumber; i++)
    {
        if (PlayerBullet[i].isInScreenFlag)
        {
            //�`��
            DrawExtendGraph(PlayerBullet[i].x1, PlayerBullet[i].y1, PlayerBullet[i].x2, PlayerBullet[i].y2, PlayerBullet[i].graph, TRUE);
        }
    }
}

//�W�O�U�O�G�e�A�E�F�C�N�i1�񂾂��Ăׂ΂��������������ɏ����j
void AwakeZigzagEnemyBullet(Bullet& zigzagEnemyBullet)
{
    //�摜�ǂݍ���
    zigzagEnemyBullet.graph = LoadGraph("img/tama1.png");
    //�e�̑��݃t���O��flase�ɂ���
    zigzagEnemyBullet.isInScreenFlag = false;
}

//�W�O�U�O�G�e������
void InitializeZigzagEnemyBullet(Bullet& zigzagEnemyBullet, Enemy& zigzagEnemy)
{
    //�W�O�U�O�G�������Ă�����e�𔭎�
    if (zigzagEnemy.isInScreenFlag)
    {
        //���݃t���O��true�ɂ���
        zigzagEnemyBullet.isInScreenFlag = true;

        if (zigzagEnemy.x1 == 1300 || zigzagEnemy.x1 == 1000 || zigzagEnemy.x1 == 700)
        {
            zigzagEnemyBullet.x1 = zigzagEnemy.x1 - 50;
            zigzagEnemyBullet.x2 = zigzagEnemyBullet.x1 + 50;
            zigzagEnemyBullet.y1 = zigzagEnemy.y1 + 35;
            zigzagEnemyBullet.y2 = zigzagEnemy.y1 + 60;
        }
    }
}

//�W�O�U�O�G�e���[�`��
void UpdateZigzagEnemyBullet(Bullet& zigzagEnemyBullet)
{  
    if (zigzagEnemyBullet.isInScreenFlag)
    {
        //�e�̈ړ�
        zigzagEnemyBullet.x1 -= zigzagEnemyBullet.enemySpeed;
        zigzagEnemyBullet.x2 -= zigzagEnemyBullet.enemySpeed;
    }

    //�e����ʊO�ɏo�������
    if (zigzagEnemyBullet.x1 < 0)
    {
        zigzagEnemyBullet.isInScreenFlag = false;
    }  
}

//�W�O�U�O�G�e�`��
void DrawZigzagEnemyBullet(Bullet& zigzagEnemyBullet)
{
    if (zigzagEnemyBullet.isInScreenFlag)
    {
        DrawExtendGraph(zigzagEnemyBullet.x2, zigzagEnemyBullet.y1, zigzagEnemyBullet.x1, zigzagEnemyBullet.y2, zigzagEnemyBullet.graph, TRUE);
    }
}

//�����܂���G�e�A�E�F�C�N
void AwakeShootingEnemyBullet(Bullet& shootingEnemyBullet)
{
    //�摜�ǂݍ���
    shootingEnemyBullet.graph = LoadGraph("img/tama3.png");

    //���݃t���O��false�ɂ���
    shootingEnemyBullet.isInScreenFlag = false;
}

//�����܂���G�e������
void InitializeShootingEnemyBullet(Bullet& shootingEnemyBullet, Enemy& shootingEnemy,Player& player1)
{
    //�����܂���G�������Ă�����
    if (shootingEnemy.isInScreenFlag)
    {
        //���݃t���O��true�ɂ���
        shootingEnemyBullet.isInScreenFlag = true;

        //���˂������̍��W
        shootingEnemyBullet.x1 = shootingEnemy.x1 - width;
        shootingEnemyBullet.x2 = shootingEnemyBullet.x1 + width;
        shootingEnemyBullet.y1 = shootingEnemy.y1 + IniShotPositionY;
        shootingEnemyBullet.y2 = shootingEnemyBullet.y1 + height;

        //���W�Q�ƒe�̌v�Z
        shootingEnemyBullet.sbx = player1.x - shootingEnemyBullet.x1;
        shootingEnemyBullet.sby = player1.y - shootingEnemyBullet.y1;

        // �����������߂�̂ɕW���֐��� sqrt ���g���A
        // ������g���ɂ� math.h ���C���N���[�h����K�v������
        shootingEnemyBullet.sb = sqrt(shootingEnemyBullet.sbx * shootingEnemyBullet.sbx + shootingEnemyBullet.sby * shootingEnemyBullet.sby);

        // �ړ����x
        shootingEnemyBullet.coordinateReferenceXSpeed = shootingEnemyBullet.sbx / shootingEnemyBulletSpeed;
        shootingEnemyBullet.coordinateReferenceYSpeed = shootingEnemyBullet.sby / shootingEnemyBulletSpeed;
    }
}

//�����܂���G�e���[�`��
void UpdateShootingEnemyBullet(Bullet& shootingEnemyBullet)
{
    //�ړ�
    if (shootingEnemyBullet.isInScreenFlag)
    {
        shootingEnemyBullet.x1 += shootingEnemyBullet.coordinateReferenceXSpeed;
        shootingEnemyBullet.x2 = shootingEnemyBullet.x1 + width;
        shootingEnemyBullet.y1 += shootingEnemyBullet.coordinateReferenceYSpeed;
        shootingEnemyBullet.y2 = shootingEnemyBullet.y1 + height;
    }

    //��ʊO�ɏo�������
    if (shootingEnemyBullet.x2 < zero || shootingEnemyBullet.y1 <= zero || shootingEnemyBullet.y1 > senn)
    {
        shootingEnemyBullet.isInScreenFlag = false;
    }
}

//�����܂���G�e�`��
void DrawShootingEnemyBullet(Bullet& shootingEnemyBullet)
{
    if (shootingEnemyBullet.isInScreenFlag)
    {
        DrawExtendGraph(shootingEnemyBullet.x2, shootingEnemyBullet.y1, shootingEnemyBullet.x1, shootingEnemyBullet.y2, shootingEnemyBullet.graph, TRUE);
    }
}