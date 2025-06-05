#include"Dxlib.h"
#include"enemy.h"
#include"shot.h"

//�`���[�g���A���G������
void InitializeTutorialEnemy(Enemy& TutorialEnemy,Bullet& TutorialBullet)
{
    //�摜�̓ǂݍ���
    TutorialEnemy.graph = LoadGraph("img/midori_teki.png"); 

    //�`���[�g���A���G�̏����ʒu
    TutorialEnemy.x1 = 1925 - 150;
    TutorialEnemy.y1 = 0;
    TutorialEnemy.x2 = 1900;
    TutorialEnemy.y2 = 100;
 
    //�`���[�g���A���G����Ɉړ����Ă��邩�̃t���O�����Z�b�g
    TutorialEnemy.changeMoveFlag = true;

    //�`���[�g���A���G�̒e��������
    InitializeTutorialBullet(TutorialBullet);
}

//�`���[�g���A���G���[�`��
void UpdateTutorialEnemy(Enemy& TutorialEnemy)
{
    //�t���O��TRUE�̂Ƃ��͏�Ɉړ�����
    if (TutorialEnemy.changeMoveFlag == true)
    {
        TutorialEnemy.y1 += TutorialEnemy.speed * 2;
        TutorialEnemy.y2 += TutorialEnemy.speed * 2;
    }
    else
    {
        TutorialEnemy.y1 -= TutorialEnemy.speed * 2;
        TutorialEnemy.y2 -= TutorialEnemy.speed * 2;
    }

    //�����߂菈���{�ړ������̔��]
    if (TutorialEnemy.y2 > 1000)
    {
        TutorialEnemy.y1 = 1000 - 100;
        TutorialEnemy.y2 = 1000;
        TutorialEnemy.changeMoveFlag = false;
    }
    else if (TutorialEnemy.y1 < 0)
    {
        TutorialEnemy.y1 = 0;
        TutorialEnemy.y2 = 100;
        TutorialEnemy.changeMoveFlag = true;
    }
}

//�`���[�g���A���G�̕`��
void DrawTutorialEnemy(Enemy& TutorialEnemy)
{
    DrawExtendGraph(TutorialEnemy.x2, TutorialEnemy.y1,TutorialEnemy.x1,TutorialEnemy.y2, TutorialEnemy.graph, TRUE);
}