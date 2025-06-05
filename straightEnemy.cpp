#include"Dxlib.h"
#include"enemy.h"

//�^�������G������
void InitializeStraightEnemy(Enemy straightEnemy[])
{
    //�ǂݍ���
    int midori_teki = LoadGraph("img/midori_teki.png");
    int i = 0;

    

    while (true)
    {
        //��ꏬ��
        if (i <= straightEnemyNumber)
        {
            while (true)
            {
                //�摜����
                straightEnemy[i].graph = midori_teki;

                //���݃t���O��true�ɂ��Ă���
                straightEnemy[i].isInScreenFlag = true;

                //�����J�E���g��0�ɂ���
                straightEnemy[i].explosionCount = 0;

                //�����t���O��ture�ɂ���
                straightEnemy[i].explosionFlag = true;

                //�������W
                straightEnemy[i].x1 = 2000 + i * 100;
                straightEnemy[i].x2 = straightEnemy[i].x1 + 100;
                straightEnemy[i].y1 = 133;
                straightEnemy[i].y2 = straightEnemy[i].y1 + 100;

                i++;

                if (i % 3 == 0)
                {
                    break;
                }
            }
        }

        //��񏬑�
        if (i <= straightEnemyNumber)
        {
            while (true)
            {
                //�摜����
                straightEnemy[i].graph = midori_teki;

                //���݃t���O��true�ɂ��Ă���
                straightEnemy[i].isInScreenFlag = true;

                //�����J�E���g��0�ɂ���
                straightEnemy[i].explosionCount = 0;

                //�����t���O��ture�ɂ���
                straightEnemy[i].explosionFlag = true;

                //�������W
                straightEnemy[i].x1 = 2000 + i * 100;
                straightEnemy[i].x2 = straightEnemy[i].x1 + 100;
                straightEnemy[i].y1 = 799;
                straightEnemy[i].y2 = straightEnemy[i].y1 + 100;

                i++;

                if (i % 3 == 0)
                {
                    break;
                }
            }
        }

        //��O����
        if (i <= straightEnemyNumber)
        {
            while (true)
            {
                i++;

                //�摜����
                straightEnemy[i].graph = midori_teki;

                //���݃t���O��true�ɂ��Ă���
                straightEnemy[i].isInScreenFlag = true;

                //�����J�E���g��0�ɂ���
                straightEnemy[i].explosionCount = 0;

                //�����t���O��ture�ɂ���
                straightEnemy[i].explosionFlag = true;

                //�������W
                straightEnemy[i].x1 = 2000 + i * 100;
                straightEnemy[i].x2 = straightEnemy[i].x1 + 100;
                straightEnemy[i].y1 = 466;
                straightEnemy[i].y2 = straightEnemy[i].y1 + 100;

                if (i % 3 == 0)
                {
                    break;
                }
            }
        }

        if (i == straightEnemyNumber)
        {
            break;
        }
    }
}

//�^�������G���[�`��
void UpdateStraightEnemy(Enemy straightEnemy[])
{
    for (int i = 0; i < straightEnemyNumber; i++)
    {
        if (straightEnemy[i].isInScreenFlag)
        {
            //�㑤�Ɖ����̏����̈ړ�
            straightEnemy[i].x1 -= straightEnemy[i].speed * 3 - 1;
            straightEnemy[i].x2 -= straightEnemy[i].speed * 3 - 1;

            //�^�񒆂�2�̂�����P���d�|����
            if (i > 6)
            {
                straightEnemy[i].x1 -= straightEnemy[i].speed * 4 - 1;
                straightEnemy[i].x2 -= straightEnemy[i].speed * 4 - 1;
            }
        }
    }
}

//�^�������G�`��
void DrawStraightEnemy(Enemy straightEnemy[], int explosionEffect[])
{
    for (int i = 0; i < straightEnemyNumber; i++)
    {
        //�^�������G�`��
        if (straightEnemy[i].x2 <= 2000 && straightEnemy[i].isInScreenFlag)
        {
            DrawExtendGraph(straightEnemy[i].x2, straightEnemy[i].y1, straightEnemy[i].x1, straightEnemy[i].y2, straightEnemy[i].graph, TRUE);
        }

        //�����G�t�F�N�g��`��
        if (!straightEnemy[i].isInScreenFlag && straightEnemy[i].explosionFlag)
        {
            DrawGraph(straightEnemy[i].x1 + 10, straightEnemy[i].y1 + 10, explosionEffect[straightEnemy[i].explosionCount], TRUE);

            //�J�E���g�𑝂₷�Bcount++;
            straightEnemy[i].explosionCount++;

            //�J�E���g���A�j���[�V�����̐���肨�������Ȃ�����O�ɖ߂�
            if (straightEnemy[i].explosionCount > 11)
            {
                straightEnemy[i].explosionFlag = false;
                straightEnemy[i].explosionCount = 0;
            }
        }
    }
}