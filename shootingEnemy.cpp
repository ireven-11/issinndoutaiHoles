#include"Dxlib.h"
#include"enemy.h"

//�����܂���G������
void InitializeShootingEnemy(Enemy shootingEnemy[])
{
	//�摜��ۑ�
    int murasaki_teki = LoadGraph("img/murasaki_teki.png");
	int j = 0;

	for (int i = 0; i < shootingEnemyNumber; i++)
	{
		//�摜�ǂݍ���
		shootingEnemy[i].graph = murasaki_teki;

		//�t���O��true�ɂ���
		shootingEnemy[i].isInScreenFlag = true;

		//�ړ��ω��t���O��false�ɂ���
		shootingEnemy[i].changeMoveFlag = false;

		//�����J�E���g��0�ɂ���
		shootingEnemy[i].explosionCount = 0;

		//�����t���O��ture�ɂ���
		shootingEnemy[i].explosionFlag = true;

		//�������W
		if (i <= 4)
		{
			shootingEnemy[i].y1 = 10 + i * 200;
			shootingEnemy[i].x1 = 2000;
		}
		else
		{
			shootingEnemy[i].x1 = i * 700 + j * 750;
			shootingEnemy[i].y1 = i * 150 - 300;
			j++;
		}
		shootingEnemy[i].x2 = shootingEnemy[i].x1 + 150;
		shootingEnemy[i].y2 = shootingEnemy[i].y1 + 100;

		//�����ω��t���O��ture�ɂ���
		shootingEnemy[i].changeMoveFlag = true;
	}
}

//�����܂���G��-�`��
void UpdateShootingEnemy(Enemy shootingEnemy[],int& scroll)
{
	for (int i = 0; i < shootingEnemyNumber; i++)
	{
		//1,2�̖ڂ����ꂽ��3,4�̖ڂ��o��
		if (i < 4 && i > 1 && !shootingEnemy[0].isInScreenFlag && !shootingEnemy[1].isInScreenFlag)
		{
			//���i
			shootingEnemy[i].x1 -= shootingEnemy[i].speed * 3;
			shootingEnemy[i].x2 -= shootingEnemy[i].speed * 3;

			//3�̖ڏ�Ɉړ�
			if (shootingEnemy[2].changeMoveFlag)
			{
				shootingEnemy[2].y1 += shootingEnemy[2].speed * 5;
				shootingEnemy[2].y2 += shootingEnemy[2].speed * 5;
			}
			//3�̖ډ��Ɉړ�
			else if (!shootingEnemy[2].changeMoveFlag)
			{
				shootingEnemy[2].y1 -= shootingEnemy[2].speed * 2;
				shootingEnemy[2].y2 -= shootingEnemy[2].speed * 2;
			}

			//4�̖ڏ�Ɉړ�
			if (shootingEnemy[3].changeMoveFlag)
			{
				shootingEnemy[3].y1 += shootingEnemy[3].speed * 2;
				shootingEnemy[3].y2 += shootingEnemy[3].speed * 2;
			}
			//4�̖ډ��Ɉړ�
			else if (!shootingEnemy[3].changeMoveFlag)
			{
				shootingEnemy[3].y1 -= shootingEnemy[3].speed * 5;
				shootingEnemy[3].y2 -= shootingEnemy[3].speed * 5;
			}

			//�����߂菈���{�ړ������̔��]
			if (shootingEnemy[i].y2 > 1000)
			{
				shootingEnemy[i].y1 = 1000 - 100;
				shootingEnemy[i].y2 = 1000;
				shootingEnemy[i].changeMoveFlag = false;
			}
			else if (shootingEnemy[i].y1 < 0)
			{
				shootingEnemy[i].y1 = 0;
				shootingEnemy[i].y2 = 100;
				shootingEnemy[i].changeMoveFlag = true;
			}
		}
		//�ŏ���2�̂̓���
		else if(i < 2)
		{
			//�ŏ��������i
			if (scroll > 950 && scroll < 1100)
			{
				shootingEnemy[i].x1 -= shootingEnemy[i].speed * 3;
				shootingEnemy[i].x2 -= shootingEnemy[i].speed * 3;
			}

			if (scroll > 1100 && scroll < 2500)
			{
				//��Ɉړ�
				if (shootingEnemy[i].changeMoveFlag)
				{
					shootingEnemy[i].y1 += shootingEnemy[i].speed * 5;
					shootingEnemy[i].y2 += shootingEnemy[i].speed * 5;
				}
				//���Ɉړ�
				else if (!shootingEnemy[i].changeMoveFlag)
				{
					shootingEnemy[i].y1 -= shootingEnemy[i].speed * 5;
					shootingEnemy[i].y2 -= shootingEnemy[i].speed * 5;
				}

				//�����߂菈���{�ړ������̔��]
				if (shootingEnemy[i].y2 > 1000)
				{
					shootingEnemy[i].y1 = 1000 - 100;
					shootingEnemy[i].y2 = 1000;
					shootingEnemy[i].changeMoveFlag = false;
				}
				else if (shootingEnemy[i].y1 < 0)
				{
					shootingEnemy[i].y1 = 0;
					shootingEnemy[i].y2 = 100;
					shootingEnemy[i].changeMoveFlag = true;
				}
			}

			//�Ō�͒��i
			if (scroll > 2500)
			{
				shootingEnemy[i].x1 -= shootingEnemy[i].speed * 5;
				shootingEnemy[i].x2 -= shootingEnemy[i].speed * 5;
			}
		}
		//5�̖ڂ̓W�O�U�O�G�ɍ����ďo��
		else if(scroll > 5000 && i == 4)
		{
			if (shootingEnemy[4].x1 >= 1700)
			{
				shootingEnemy[4].x1 -= shootingEnemy[4].speed * 5;
				shootingEnemy[4].x2 -= shootingEnemy[4].speed * 5;
			}
			//��Ɉړ�
			else if (shootingEnemy[4].changeMoveFlag)
			{
				shootingEnemy[4].y1 += shootingEnemy[4].speed * 4;
				shootingEnemy[4].y2 += shootingEnemy[4].speed * 4;
			}
			//���Ɉړ�
			else if (!shootingEnemy[i].changeMoveFlag)
			{
				shootingEnemy[4].y1 -= shootingEnemy[4].speed * 4;
				shootingEnemy[4].y2 -= shootingEnemy[4].speed * 4;
			}

			//�����߂菈���{�ړ������̔��]
			if (shootingEnemy[4].y2 > 1000)
			{
				shootingEnemy[4].y1 = 1000 - 100;
				shootingEnemy[4].y2 = 1000;
				shootingEnemy[4].changeMoveFlag = false;
			}
			else if (shootingEnemy[4].y1 < 0)
			{
				shootingEnemy[4].y1 = 0;
				shootingEnemy[4].y2 = 100;
				shootingEnemy[4].changeMoveFlag = true;
			}

			if (scroll > 6750)
			{
				shootingEnemy[4].x1 -= shootingEnemy[4].speed * 8;
				shootingEnemy[4].x2 -= shootingEnemy[4].speed * 8;
			}
		}
		//6�̖ڈȍ~��wave4�ł���
		else if (scroll > 14000 && i > 4)
		{
			//��ʓ��ɂ��Ȃ��Ȃ����獶�ɒ��i
			if (shootingEnemy[i].x2 > 1500 && shootingEnemy[i].changeMoveFlag)
			{
				shootingEnemy[i].x1 -= shootingEnemy[i].speed * 3;
				shootingEnemy[i].x2 -= shootingEnemy[i].speed * 3;
			}
			//�O�p��`���l�ɓ���
			else if (shootingEnemy[i].x1 > 1300 && shootingEnemy[i].changeMoveFlag)
			{
				shootingEnemy[i].x1 -= shootingEnemy[i].speed * 3;
				shootingEnemy[i].x2 -= shootingEnemy[i].speed * 3;
				shootingEnemy[i].y1 -= shootingEnemy[i].speed * 3;
				shootingEnemy[i].y2 -= shootingEnemy[i].speed * 3;
			}
			else
			{
				if (shootingEnemy[i].y1 < 1100 - i * 100 && shootingEnemy[i].changeMoveFlag)
				{
					shootingEnemy[i].y1 += shootingEnemy[i].speed * 4;
					shootingEnemy[i].y2 += shootingEnemy[i].speed * 4;

					if (shootingEnemy[i].y1 > 1100 - i * 100)
					{
						shootingEnemy[i].changeMoveFlag = false;
					}
				}
				else
				{
					shootingEnemy[i].x1 += shootingEnemy[i].speed * 3;
					shootingEnemy[i].x2 += shootingEnemy[i].speed * 3;
					shootingEnemy[i].y1 -= shootingEnemy[i].speed * 3;
					shootingEnemy[i].y2 -= shootingEnemy[i].speed * 3;

					if (shootingEnemy[i].x1 > 1500)
					{
						shootingEnemy[i].changeMoveFlag = true;
					}
				}
			}
		}

		//�X�N���[�����I�������t���O��false�ɂ���
		if (scroll > 21000)
		{
			shootingEnemy[i].isInScreenFlag = false;
		}
	}
}

//�����܂���G�`��
void DrawShootingEnemy(Enemy shootingEnemy[], int explosionEffect[])
{
	for (int i = 0; i < shootingEnemyNumber; i++)
	{
		//�^�������G�`��
		if (shootingEnemy[i].x2 <= 2000 && shootingEnemy[i].isInScreenFlag)
		{
			DrawExtendGraph(shootingEnemy[i].x2, shootingEnemy[i].y1, shootingEnemy[i].x1, shootingEnemy[i].y2, shootingEnemy[i].graph, TRUE);
		}

		//�����G�t�F�N�g��`��
		if (!shootingEnemy[i].isInScreenFlag && shootingEnemy[i].explosionFlag)
		{
			DrawGraph(shootingEnemy[i].x1 + 10, shootingEnemy[i].y1 + 10, explosionEffect[shootingEnemy[i].explosionCount], TRUE);

			//�J�E���g�𑝂₷�Bcount++;
			shootingEnemy[i].explosionCount++;

			//�J�E���g���A�j���[�V�����̐���肨�������Ȃ�����O�ɖ߂�
			if (shootingEnemy[i].explosionCount > 11)
			{
				shootingEnemy[i].explosionFlag = false;
				shootingEnemy[i].explosionCount = 0;
			}
		}
	}
}