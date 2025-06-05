#include"DxLib.h"
#include"enemy.h"

//�W�O�U�O�G������
void InitializeZigzagEnemy(Enemy zigzagEnemy[])
{
    //�ǂݍ���
    int midori_teki = LoadGraph("img/midori_teki.png");
    int i = 0;
    int displaceY = zero; //���̂��炵��
    int displaceX = zero; //x�̂��炵��

    //�摜����
    zigzagEnemy[0].graph = midori_teki;

    //���݃t���O��true�ɂ��Ă���
    zigzagEnemy[0].isInScreenFlag = true;

    //�����J�E���g��0�ɂ���
    zigzagEnemy[0].explosionCount = 0;

    //�����t���O��ture�ɂ���
    zigzagEnemy[0].explosionFlag = true;

    //�������W
    zigzagEnemy[0].x1 = 2000 + i * 100 + displaceX * 100;
    zigzagEnemy[0].x2 = zigzagEnemy[0].x1 + 100;
    zigzagEnemy[0].y1 = 10000;
    zigzagEnemy[0].y2 = 20000;

    while (true)
    {
        //��ꏬ��
        if (i < zigzagEnemyNumber)
        {
            while (true)
            {
                if (i == 0)
                {
                    
                }
                else
                {
                    //�摜����
                    zigzagEnemy[i].graph = midori_teki;

                    //���݃t���O��true�ɂ��Ă���
                    zigzagEnemy[i].isInScreenFlag = true;

                    //�����J�E���g��0�ɂ���
                    zigzagEnemy[i].explosionCount = 0;

                    //�����t���O��ture�ɂ���
                    zigzagEnemy[i].explosionFlag = true;

                    //�������W
                    zigzagEnemy[i].x1 = 2000 + i * 100 + displaceX * 100;
                    zigzagEnemy[i].x2 = zigzagEnemy[i].x1 + 100;
                    zigzagEnemy[i].y1 = 100 + displaceY * 150;
                    zigzagEnemy[i].y2 = zigzagEnemy[i].y1 + 100;
                }
                

                i++;

                if (i % 5 == 0)
                {
                    displaceY++;
                    break;
                }
            }
        }
            
        //��񏬑�
        if (i < zigzagEnemyNumber)
        {
            while (true)
            {
                //�摜����
                zigzagEnemy[i].graph = midori_teki;

                //���݃t���O��true�ɂ��Ă���
                zigzagEnemy[i].isInScreenFlag = true;

                //�����J�E���g��0�ɂ���
                zigzagEnemy[i].explosionCount = 0;

                //�����t���O��ture�ɂ���
                zigzagEnemy[i].explosionFlag = true;

                //�������W
                zigzagEnemy[i].x1 = 2250 + i * 100 + displaceX * 100;
                zigzagEnemy[i].x2 = zigzagEnemy[i].x1 + 100;
                zigzagEnemy[i].y1 = 750 - displaceY * 150;
                zigzagEnemy[i].y2 = zigzagEnemy[i].y1 + 100;

                i++;

                if (i % 5 == 0)
                {
                    displaceX++;
                    break;
                }
            }
        }
            
        if (i == zigzagEnemyNumber)
        {
            break;
        }
    }
}

//�W�O�U�O�G���[�`��
void UpdateZigzagEnemy(Enemy zigzagEnemy[])
{
    //�ړ�
    for (int i = 0; i < zigzagEnemyNumber; i++)
    {
        if (i == 0)
        {
            //�O�̂�͈ړ������Ȃ�
        }
        else
        {
            if (zigzagEnemy[i].isInScreenFlag)
            {
                zigzagEnemy[i].x1 -= zigzagEnemy[i].speed * 2 + 1;
                zigzagEnemy[i].x2 -= zigzagEnemy[i].speed * 2 + 1;

                if (zigzagEnemy[i].x1 < 1300 && zigzagEnemy[i].x1 > 1000)
                {
                    zigzagEnemy[i].y1 += zigzagEnemy[i].speed * 3;
                    zigzagEnemy[i].y2 += zigzagEnemy[i].speed * 3;
                }
                else if (zigzagEnemy[i].x1 < 1000 && zigzagEnemy[i].x1 > 700)
                {
                    zigzagEnemy[i].y1 -= zigzagEnemy[i].speed * 3;
                    zigzagEnemy[i].y2 -= zigzagEnemy[i].speed * 3;
                }
                else if (zigzagEnemy[i].x1 < 700)
                {
                    zigzagEnemy[i].y1 += zigzagEnemy[i].speed * 3;
                    zigzagEnemy[i].y2 += zigzagEnemy[i].speed * 3;
                }
            }
        }
    }
}

//�W�O�U�O�G�`��
void DrawZigzagEnemy(Enemy zigzagEnemy[], int explosionEffect[])
{
    for (int i = 0; i < zigzagEnemyNumber; i++)
    {
        //�W�O�U�O�G�`��
        if (zigzagEnemy[i].x2 <= 2000 && zigzagEnemy[i].isInScreenFlag)
        {
            if (i == 0)
            {
                DrawExtendGraph(zigzagEnemy[0].x2, zigzagEnemy[0].y1, zigzagEnemy[0].x1, zigzagEnemy[0].y2, zigzagEnemy[0].graph, TRUE);
            }
            else
            {
                DrawExtendGraph(zigzagEnemy[i].x2, zigzagEnemy[i].y1, zigzagEnemy[i].x1, zigzagEnemy[i].y2, zigzagEnemy[i].graph, TRUE);
            }
        }
        
        //�����G�t�F�N�g��`��
        if (!zigzagEnemy[i].isInScreenFlag && zigzagEnemy[i].explosionFlag)
        {
            DrawGraph(zigzagEnemy[i].x1 + 10, zigzagEnemy[i].y1 + 10, explosionEffect[zigzagEnemy[i].explosionCount], TRUE);

            //�J�E���g�𑝂₷�Bcount++;
            zigzagEnemy[i].explosionCount++;

            //�J�E���g���A�j���[�V�����̐���肨�������Ȃ�����O�ɖ߂�
            if (zigzagEnemy[i].explosionCount > 11)
            {
                zigzagEnemy[i].explosionFlag = false;
                zigzagEnemy[i].explosionCount = 0;
            }
        }
    }
}