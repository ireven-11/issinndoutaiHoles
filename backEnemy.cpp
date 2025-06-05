#include"DxLib.h"
#include"enemy.h"
#include"player.h"

//��납��G������
void InitializeBackEnemy(Enemy backEnemy[])
{
    int tyairoteki = LoadGraph("img/tyairo_teki.png");
	int j = 0;
				
	for (int i = 0; i < backEnemyNumber	; i++)
	{
		//�摜�ǂݍ���
		backEnemy[i].graph = tyairoteki;

		//�����J�E���g��0�ɂ���
		backEnemy[i].explosionCount = 0;

		//�����t���O��ture�ɂ���
		backEnemy[i].explosionFlag = true;

		//�������W��ݒ�
		//�ŏ���2��
		if (i < 2)
		{
			if (i == 0)
			{
				backEnemy[0].x1 = IniBackEnemyX;
				backEnemy[0].y1 = IniBackEnemyY + i * fiveHundred;
				backEnemy[0].x2 = backEnemy[0].x1 + hundredfifteen;
				backEnemy[0].y2 = backEnemy[0].y1 + IniBackEnemyY;
			}
			else
			{
				backEnemy[i].x1 = IniBackEnemyX;
				backEnemy[i].y1 = IniBackEnemyY + i * fiveHundred;
				backEnemy[i].x2 = backEnemy[i].x1 + hundredfifteen;
				backEnemy[i].y2 = backEnemy[i].y1 + IniBackEnemyY;
			}
		}
		//�c��͕ǂƂ���wave�S�ł���
		else if(i < 12)
		{
			backEnemy[i].x1 = -150;
			backEnemy[i].y1 = 0 + j * 100;
			backEnemy[i].x2 = backEnemy[i].x1 + 150;
			backEnemy[i].y2 = backEnemy[i].y1 + 100;
			j++;
		}
		//�����ł������
		else
		{
			backEnemy[i].x1 = -1500;
			backEnemy[i].y1 = 0;
			backEnemy[i].x2 = backEnemy[i].x1 + 1400;
			backEnemy[i].y2 = backEnemy[i].y1 + 1000;
		}
		//���݃t���O��ture�ɂ���
		backEnemy[i].isInScreenFlag = true;

		//�����ω��t���O��false�ɂ���
		backEnemy[i].changeMoveFlag = false;
	}
}

//��납��G���[�`��
void UpdateBackEnemy(Enemy backEnemy[],int wave1,int& scroll,Player& player2, int wave3, int wave4)
{
	for (int i = 0; i < backEnemyNumber; i++)
	{
		//�ŏ���2�̂̂�����
		if (i < 2)
		{
			//���W��1000��菬����wave2�̂Ƃ��ɉE�Ɉړ�
			if (backEnemy[i].x1 < 1000 && scroll > wave1 && !backEnemy[i].changeMoveFlag)
			{
				backEnemy[i].x1 += backEnemy[i].speed * 2;
				backEnemy[i].x2 += backEnemy[i].speed * 2;
			}

			if (backEnemy[i].x1 == 1000)
			{
				//�����ω��t���O��true�ɂ���
				backEnemy[i].changeMoveFlag = true;
			}

			//�X�N���[�������ɂȂ����獶�Ɉړ����n�߂�
			if (backEnemy[i].changeMoveFlag)
			{
				backEnemy[i].x1 -= backEnemy[i].speed * 2;
				backEnemy[i].x2 -= backEnemy[i].speed * 2;

				//�v���C���[�ƓG��y�̋����ɂ���Ĉړ���ς���
				if (backEnemy[i].y1 - player2.y < 0)
				{
					backEnemy[i].y1 += backEnemy[i].speed;
					backEnemy[i].y2 += backEnemy[i].speed;
				}
				else if (backEnemy[i].y1 - player2.y > 0)
				{
					backEnemy[i].y1 -= backEnemy[i].speed;
					backEnemy[i].y2 -= backEnemy[i].speed;
				}
			}
		}
		//�G�ŕǂ����(�r������ړ����Ȃ��Ȃ�)
		else if (i > 1 && i < 12 && scroll > wave3 && scroll % 2 == 0)
		{
			backEnemy[i].x1 += backEnemy[i].speed;
			backEnemy[i].x2 += backEnemy[i].speed;
		}
		//�ł�����̈ړ�
		else if(scroll > wave3 && scroll % 5 == 0 && i == 12)
		{
			backEnemy[i].x1 += backEnemy[i].speed;
			backEnemy[i].x2 += backEnemy[i].speed;
		}

		//�N���A��ʂɂȂ����瑶�݃t���O��false�ɂ���
		if (scroll > wave4)
		{
			backEnemy[i].isInScreenFlag = false;
		}
	}
}

//��납��G�`��
void DrawBackEnemy(Enemy backEnemy[], int explosionEffect[])
{
	for (int i = 0; i < backEnemyNumber; i++)
	{
		//�t���O��ture�̂Ƃ�����
		if (backEnemy[i].isInScreenFlag)
		{
			if (i == 0)
			{
				if (!backEnemy[0].changeMoveFlag)
				{
					DrawExtendGraph(backEnemy[0].x1, backEnemy[0].y1, backEnemy[0].x2, backEnemy[0].y2, backEnemy[0].graph, TRUE);
				}
				else
				{
					DrawExtendGraph(backEnemy[0].x2, backEnemy[0].y1, backEnemy[0].x1, backEnemy[0].y2, backEnemy[0].graph, TRUE);
				}
			}
			else
			{
				if (!backEnemy[i].changeMoveFlag)
				{
					DrawExtendGraph(backEnemy[i].x1, backEnemy[i].y1, backEnemy[i].x2, backEnemy[i].y2, backEnemy[i].graph, TRUE);
				}
				else
				{
					DrawExtendGraph(backEnemy[i].x2, backEnemy[i].y1, backEnemy[i].x1, backEnemy[i].y2, backEnemy[i].graph, TRUE);
				}
			}
		}

		//�����G�t�F�N�g��`��
		if (!backEnemy[i].isInScreenFlag && backEnemy[i].explosionFlag)
		{
			if (i < 12)
			{
				DrawGraph(backEnemy[i].x1 + 10, backEnemy[i].y1 + 10, explosionEffect[backEnemy[i].explosionCount], TRUE);
			}
			else
			{
				DrawExtendGraph(backEnemy[i].x1 / 2, backEnemy[i].y1, backEnemy[i].x2, backEnemy[i].y2, explosionEffect[backEnemy[i].explosionCount], TRUE);
			}
			//�J�E���g�𑝂₷�Bcount++;
			backEnemy[i].explosionCount++;

			//�J�E���g���A�j���[�V�����̐���肨�������Ȃ�����O�ɖ߂�
			if (backEnemy[i].explosionCount > 11)
			{
				backEnemy[i].explosionFlag = false;
				backEnemy[i].explosionCount = 0;
			}
		}
	}
}