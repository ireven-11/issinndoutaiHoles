#include"Dxlib.h"
#include"enemy.h"

//��P�G������
void InitializeRaidEnemy(Enemy raidEnemy[])
{
    int fukamidoriteki = LoadGraph("img/fukamidori_teki.png");
    int i = 0;
    int j = 0;

    

    while (true)
    {
        //�摜�ǂݍ���
        raidEnemy[i].graph = fukamidoriteki;

        //���݃t���O��true�ɂ���
        raidEnemy[i].isInScreenFlag = true;

        //�ړ��ω��t���O��false�ɂ���
        raidEnemy[i].changeMoveFlag = false;

        //�����J�E���g��0�ɂ���
        raidEnemy[i].explosionCount = 0;

        //�����t���O��ture�ɂ���
        raidEnemy[i].explosionFlag = true;

        //�ォ�炭��G�̏������W
        if (i % 2 == 0)
        {
            //��ꏬ��
            if (i < 16)
            {
                raidEnemy[i].x1 = 0 + i * 125;
                raidEnemy[i].x2 = raidEnemy[i].x1 + 125;
                raidEnemy[i].y1 = -400 - i * 200;
                raidEnemy[i].y2 = raidEnemy[i].y1 + 75;
            }
            //��񏬑�
            else
            {
                raidEnemy[i].x1 = 0 + j * 125;
                raidEnemy[i].x2 = raidEnemy[i].x1 + 125;
                raidEnemy[i].y1 = -100 - i * 150;
                raidEnemy[i].y2 = raidEnemy[i].y1 + 75;
                j++;
            }
        }
        //�����炭��G�̏������W
        else
        {
            //��ꏬ��
            if (i < 16)
            {
                raidEnemy[i].x1 = 1925 - i * 125;
                raidEnemy[i].x2 = raidEnemy[i].x1 + 125;
                raidEnemy[i].y1 = 1400 + i * 200;
                raidEnemy[i].y2 = raidEnemy[i].y1 + 75;
            }
            //��񏬑�
            else
            {
                raidEnemy[i].x1 = 1925 - j * 125;
                raidEnemy[i].x2 = raidEnemy[i].x1 + 125;
                raidEnemy[i].y1 = 1000 + i * 150;
                raidEnemy[i].y2 = raidEnemy[i].y1 + 75;
                j++;
            }
        }

        i++;

        if (i == raidEnemyNumber)
        {
            break;
        }
    }
}

//��P�G���[�`��
void UpdateRaidEnemy(Enemy raidEnemy[],int& scroll, int wave2)
{
    int j = 0;

    if (scroll > wave2)
    {
        for (int i = 0; i < raidEnemyNumber; i++)
        {
            //�ォ�炭��G�̈ړ�
            if (i % 2 == 0)
            {
                //��ꏬ���̈ړ�
                if (i < 16)
                {
                    //�Ō�ɍ��Ɉړ�
                    if (raidEnemy[i].y1 < 0 + i * 50 && raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].x1 -= raidEnemy[i].speed * 8;
                        raidEnemy[i].x2 -= raidEnemy[i].speed * 8;
                    }
                    //��ʊO�����܂ł������Ɉړ�
                    else if (raidEnemy[i].x1 > 1925)
                    {
                        raidEnemy[i].y1 -= raidEnemy[i].speed * 3;
                        raidEnemy[i].y2 -= raidEnemy[i].speed * 3;
                    }
                    //��ʉ��O�܂ňړ�������E�Ɉړ�
                    else if (1925 > raidEnemy[i].x1 && raidEnemy[i].y1 > 1000 && !raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].x1 += raidEnemy[i].speed * 3;
                        raidEnemy[i].x2 += raidEnemy[i].speed * 3;
                    }
                    //�ŏ��ɉ��Ɉړ�
                    else if (!raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].y1 += raidEnemy[i].speed * 3;
                        raidEnemy[i].y2 += raidEnemy[i].speed * 3;
                    }
                }
                //��񏬑��̈ړ�
                else
                {
                    //�Ō�ɍ��Ɉړ�
                    if (raidEnemy[i].y1 < 0 + j * 50 && raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].x1 -= raidEnemy[i].speed * 5;
                        raidEnemy[i].x2 -= raidEnemy[i].speed * 5;
                    }
                    //��ʊO�����܂ł������Ɉړ�
                    else if (raidEnemy[i].x1 > 1925)
                    {
                        raidEnemy[i].y1 -= raidEnemy[i].speed * 3;
                        raidEnemy[i].y2 -= raidEnemy[i].speed * 3;
                    }
                    //��ʉ��O�܂ňړ�������E�Ɉړ�
                    else if (1925 > raidEnemy[i].x1 && raidEnemy[i].y1 > 1000 && !raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].x1 += raidEnemy[i].speed * 3;
                        raidEnemy[i].x2 += raidEnemy[i].speed * 3;
                    }
                    //�ŏ��ɉ��Ɉړ�
                    else if (!raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].y1 += raidEnemy[i].speed * 2;
                        raidEnemy[i].y2 += raidEnemy[i].speed * 2;
                    }
                    j++;
                }
            }
            //�����炭��G�̈ړ�
            else
            {
                //��ꏬ���̈ړ�
                if (i < 16)
                {
                    //�Ō�ɍ��Ɉړ�
                    if (raidEnemy[i].y1 > 950 - i * 50 && raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].x1 -= raidEnemy[i].speed * 8;
                        raidEnemy[i].x2 -= raidEnemy[i].speed * 8;
                    }
                    //��ʊO�E�܂ł����牺�Ɉړ�
                    else if (raidEnemy[i].x1 > 1925 && raidEnemy[i - 1].x1 > 1925)
                    {
                        raidEnemy[i].y1 += raidEnemy[i].speed * 3;
                        raidEnemy[i].y2 += raidEnemy[i].speed * 3;
                    }
                    //��ʏ�O�܂ňړ�������E�Ɉړ�
                    else if (1925 > raidEnemy[i].x1 && raidEnemy[i].y2 < 0 && !raidEnemy[i].changeMoveFlag)
                    {
                        if (i > 7)
                        {
                            raidEnemy[i].x1 = 1926;
                            raidEnemy[i].x2 = raidEnemy[i].x1 + 125;
                        }
                        else
                        {
                            raidEnemy[i].x1 += raidEnemy[i].speed * 3;
                            raidEnemy[i].x2 += raidEnemy[i].speed * 3;
                        }
                    }
                    //�ŏ��ɏ�Ɉړ�
                    else if (!raidEnemy[i].changeMoveFlag && raidEnemy[i].x1 < 1925)
                    {
                        raidEnemy[i].y1 -= raidEnemy[i].speed * 3;
                        raidEnemy[i].y2 -= raidEnemy[i].speed * 3;
                    }
                }
                //��񏬑��̈ړ�
                else
                {
                    //�Ō�ɍ��Ɉړ�
                    if (raidEnemy[i].y1 > 950 - j * 50 && raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].x1 -= raidEnemy[i].speed * 5;
                        raidEnemy[i].x2 -= raidEnemy[i].speed * 5;
                    }
                    //��ʊO�E�܂ł����牺�Ɉړ�
                    else if (raidEnemy[i].x1 > 1925 && raidEnemy[i - 1].x1 > 1925)
                    {
                        raidEnemy[i].y1 += raidEnemy[i].speed * 3;
                        raidEnemy[i].y2 += raidEnemy[i].speed * 3;
                    }
                    //��ʏ�O�܂ňړ�������E�Ɉړ�
                    else if (1925 > raidEnemy[i].x1 && raidEnemy[i].y2 < 0 && !raidEnemy[i].changeMoveFlag)
                    {
                        if (i > 7)
                        {
                            raidEnemy[i].x1 = 1926;
                            raidEnemy[i].x2 = raidEnemy[i].x1 + 125;
                        }
                        else
                        {
                            raidEnemy[i].x1 += raidEnemy[i].speed * 3;
                            raidEnemy[i].x2 += raidEnemy[i].speed * 3;
                        }
                    }
                    //�ŏ��ɏ�Ɉړ�
                    else if (!raidEnemy[i].changeMoveFlag && raidEnemy[i].x1 < 1925)
                    {
                        raidEnemy[i].y1 -= raidEnemy[i].speed * 2;
                        raidEnemy[i].y2 -= raidEnemy[i].speed * 2;
                    }
                    j++;
                }
            }

            //�����ω��t���O��ture�ɂ���
            if (raidEnemy[i].x1 > 1925)
            {
                raidEnemy[i].changeMoveFlag = true;
            }
        }
    }
}

//��P�G�`��
void DrawRaidEnemy(Enemy raidEnemy[], int explosionEffect[])
{ 
    for (int i = 0; i < raidEnemyNumber; i++)
    {
        //�t���O��ture�̂Ƃ�����
        if (raidEnemy[i].isInScreenFlag)
        {
            DrawExtendGraph(raidEnemy[i].x2, raidEnemy[i].y1, raidEnemy[i].x1, raidEnemy[i].y2, raidEnemy[i].graph, TRUE);
        }

        //�����G�t�F�N�g��`��
        if (!raidEnemy[i].isInScreenFlag && raidEnemy[i].explosionFlag)
        {
            DrawGraph(raidEnemy[i].x1 + 10, raidEnemy[i].y1 + 10, explosionEffect[raidEnemy[i].explosionCount], TRUE);

            //�J�E���g�𑝂₷�Bcount++;
            raidEnemy[i].explosionCount++;

            //�J�E���g���A�j���[�V�����̐���肨�������Ȃ�����O�ɖ߂�
            if (raidEnemy[i].explosionCount > 11)
            {
                raidEnemy[i].explosionFlag = false;
                raidEnemy[i].explosionCount = 0;
            }
        }
    }
}