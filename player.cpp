#include"Dxlib.h"
#include"player.h"
#include"shot.h"
#include"block.h"

//�v���C���[������
void InitializePlayer(Player& player1,Player& player2)
{
	//�v���C���[�̉摜�ǂݍ���
	player1.normalgraph = LoadGraph("img/siro.png");
	player2.normalgraph = LoadGraph("img/kuro.png");
	player1.actiongraph = LoadGraph("img/siro_hakidasi.png");
	player2.actiongraph = LoadGraph("img/kuro_suikomi.png");

	//�v���C���[�̏����l
	player1.x = 300;
	player1.y = 300;
	player2.x = 100;
	player2.y = 300;

	//���݃t���O��ture�ɂ���
	player1.isInScreenFlag = true;
	player2.isInScreenFlag = true;
}

//�v���C���[���[�`��
void UpdatePlayer(Player& player1, Player& player2, DINPUT_JOYSTATE input, Bullet zigzagEnemyBullet[], int& scoreMagnificatoin, int suctionSound, int succeedSuctionSound, int& remainingBullet, Bullet shootingEnemyBullet[], bool blockFlag[], int blockX1[], int blockX2[], int blockY1[], int blockY2[],int& scroll,int wave4, bool& suctionSucceedEffectFlag)
{
	//�R���g���[���[�̓��͏�Ԃ��擾
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	//�N���A����܂�
	if (scroll <= wave4)
	{
		//�L��������ʊO�ɏo���Ƃ��R���g���[���[�̃X�e�B�b�N���͂𖳌��ɂ���(�����o�O�H����B�]�T������ΏC��)
	    //���v���C���[�̓��͖���
		/*if (player1.x < 0)
		{
			input.Z = 0;
		}
		else if (player1.y < 0)
		{
			input.Rz = 0;
		}
		else if (player1.x + 176 > 1925)
		{
			input.Z = 0;
		}
		else if (player1.y + 185 > 1000)
		{
			input.Rz = 0;;
		}*/
		if (player1.x < 0)
		{
			input.Rx = 0;
		}
		else if (player1.y < 0)
		{
			input.Ry = 0;
		}
		else if (player1.x + 176 > 1925)
		{
			input.Rx = 0;
		}
		else if (player1.y + 185 > 1000)
		{
			input.Ry = 0;;
		}
		//���v���C���[�̓��͖���
		if (player2.x <= 0)
		{
			input.X = 0;
		}
		else if (player2.y <= 0)
		{
			input.Y = 0;
		}
		else if (player2.x + 183 > 1925)
		{
			input.X = 0;
		}
		else if (player2.y + 190 > 1000)
		{
			input.Y = 0;
		}

		//�ł����u���b�N�����v���C���[�ɂ߂荞��ł���Ƃ�
		//if (blockX1[10] < player1.x + 176 && player1.x + 176 < blockX2[10] && blockFlag[10])
		//{
		//	//���͂𖳌��ɂ���
		//	input.Z = 0;
		//}
		if (blockX1[10] < player1.x + 176 && player1.x + 176 < blockX2[10] && blockFlag[10])
		{
			//���͂𖳌��ɂ���
			input.Rx = 0;
		}
		//�ł����u���b�N�����v���C���[�ɂ߂荞��ł���Ƃ�
		if (blockX1[10] < player2.x + 176 && player2.x + 176 < blockX2[10] && blockFlag[10])
		{
			//���͂𖳌��ɂ���
			input.X = 0;
		}

		// �E�X�e�B�b�N��|���Ă����甒�v���C���[���ړ�������
		/*if (input.Rz < 0)
		{
			player1.y -= player1.speed;
		}
		if (input.Rz > 0)
		{
			player1.y += player1.speed;
		}
		if (input.Z < 0)
		{
			player1.x -= player1.speed;
		}
		if (input.Z > 0)
		{
			player1.x += player1.speed;
		}*/
		if (input.Ry < 0)
		{
			player1.y -= player1.speed;
		}
		if (input.Ry > 0)
		{
			player1.y += player1.speed;
		}
		if (input.Rx < 0)
		{
			player1.x -= player1.speed;
		}
		if (input.Rx > 0)
		{
			player1.x += player1.speed;
		}

		//���X�e�B�b�N��|�����獕�v���C���[���ړ�������
		if (input.Y < 0)
		{
			player2.y -= player2.speed + 3;
		}
		if (input.Y > 0)
		{
			player2.y += player2.speed + 3;
		}
		if (input.X < 0)
		{
			player2.x -= player2.speed + 3;
		}
		if (input.X > 0)
		{
			player2.x += player2.speed + 3;
		}

		//���v���C���[�����߂�����
		if (player1.x < 0)
		{
			player1.x += player1.speed;
		}
		else if (player1.y < 0)
		{
			player1.y += player1.speed;
		}
		else if (player1.x + 176 > 1925)
		{
			player1.x -= player1.speed;
		}
		else if (player1.y + 185 > 1000)
		{
			player1.y -= player1.speed;
		}
		//���v���C���[�����߂�����
		if (player2.x <= 0)
		{
			player2.x += player2.speed + 3;
		}
		else if (player2.y <= 0)
		{
			player2.y += player2.speed + 3;
		}
		else if (player2.x + 183 > 1925)
		{
			player2.x -= player2.speed + 3;
		}
		else if (player2.y + 190 > 1000)
		{
			player2.y -= player2.speed + 3;
		}

		//�u���b�N�Ƃ̉����߂菈��
		for (int i = 0; i < blockNumber; i++)
		{
			//�u���b�N������Ƃ�����
			if (blockFlag[i])
			{
				if (i < 10)
				{
					//�u���b�N�����v���C���[�ɂ߂荞��ł���Ƃ�
					if (player1.x < blockX1[i] && blockX1[i] < player1.x + 176 &&
						player1.y < blockY1[i] && blockY1[i] < player1.y + 185 ||
						player1.x < blockX1[i] && blockX1[i] < player1.x + 176 &&
						player1.y < blockY2[i] && blockY2[i] < player1.y + 185)
					{
						player1.x -= player1.speed;

						//���͂𖳌��ɂ���
						input.Z = 0;
					}
					else if (player1.x < blockX2[i] && blockX2[i] < player1.x + 176 &&
						player1.y < blockY1[i] && blockY1[i] < player1.y + 185 ||
						player1.x < blockX2[i] && blockX2[i] < player1.x + 176 &&
						player1.y < blockY2[i] && blockY2[i] < player1.y + 185)
					{
						player1.x += player1.speed;

						//���͂𖳌��ɂ���
						input.Z = 0;
					}

					//�u���b�N�����v���C���[�ɂ߂荞��ł���Ƃ�
					if (player2.x < blockX1[i] && blockX1[i] < player2.x + 176 &&
						player2.y < blockY1[i] && blockY1[i] < player2.y + 185 ||
						player2.x < blockX1[i] && blockX1[i] < player2.x + 176 &&
						player2.y < blockY2[i] && blockY2[i] < player2.y + 185)
					{
						player2.x -= player2.speed;

						//���͂𖳌��ɂ���
						input.X = 0;
					}
					else if (player2.x < blockX2[i] && blockX2[i] < player2.x + 176 &&
						player2.y < blockY1[i] && blockY1[i] < player2.y + 185 ||
						player2.x < blockX2[i] && blockX2[i] < player2.x + 176 &&
						player2.y < blockY2[i] && blockY2[i] < player2.y + 185)
					{
						player2.x += player2.speed;

						//���͂𖳌��ɂ���
						input.X = 0;
					}
				}
				else
				{
					//�u���b�N�����v���C���[�ɂ߂荞��ł���Ƃ�
					if (blockX1[i] < player1.x + 176 && player1.x + 176 < blockX2[i])
					{
						player1.x -= player1.speed;

						//���͂𖳌��ɂ���
						input.Z = 0;
					}
					//�u���b�N�����v���C���[�ɂ߂荞��ł���Ƃ�
					if (blockX1[i] < player2.x + 176 && player2.x + 176 < blockX2[i])
					{
						player2.x -= player2.speed;

						//���͂𖳌��ɂ���
						input.X = 0;
					}
				}
			}
		}

		//LB�{�^���������Ă�Ԃ����e���z��
		if (input.Buttons[4] > 0 || input.Buttons[6] > 0)
		{
			//�z�����݌��ʉ�
			PlaySoundMem(suctionSound, DX_PLAYTYPE_LOOP, FALSE);

			//�W�O�U�O�G�e�z�����ݏ���
			for (int i = 0; i < zigzagEnemyShotNumber; i++)
			{
				if (zigzagEnemyBullet[i].isInScreenFlag)
				{
					if (player2.x + 125 < zigzagEnemyBullet[i].x1 &&
						zigzagEnemyBullet[i].x1 < player2.x + 251 &&
						player2.y < zigzagEnemyBullet[i].y2 &&
						zigzagEnemyBullet[i].y2 < player2.y + 204 ||
						player2.x + 125 < zigzagEnemyBullet[i].x1 &&
						zigzagEnemyBullet[i].x1 < player2.x + 251 &&
						zigzagEnemyBullet[i].y1 < player2.y + 204 &&
						player2.y < zigzagEnemyBullet[i].y1)
					{
						//�z�����ݐ������ʉ�
						PlaySoundMem(succeedSuctionSound, DX_PLAYTYPE_BACK, TRUE);

						//�e������
						zigzagEnemyBullet[i].isInScreenFlag = false;

						//�e��
						remainingBullet += healBullet;

						//�e�̏����ݒ�
						if (remainingBullet > MaxremainingBullet)
						{
							remainingBullet = MaxremainingBullet;
						}

						//�X�R�A�{���𑝂₷
						scoreMagnificatoin++;

						//�z�����ݐ����G�t�F�N�g�t���O��true�ɂ���
						suctionSucceedEffectFlag = true;
					}
				}
			}

			//�����܂���G�e�z�����ݏ���
			for (int i = 0; i < shootingEnemyShotNumber; i++)
			{
				if (shootingEnemyBullet[i].isInScreenFlag)
				{
					if (player2.x + player2Widht <= shootingEnemyBullet[i].x1 &&
						shootingEnemyBullet[i].x1 <= player2.x + suctionWidht &&
						player2.y <= shootingEnemyBullet[i].y2 &&
						shootingEnemyBullet[i].y2 <= player2.y + suctionHeight ||
						player2.x + player2Widht <= shootingEnemyBullet[i].x1 &&
						shootingEnemyBullet[i].x1 <= player2.x + suctionWidht &&
						shootingEnemyBullet[i].y1 <= player2.y + suctionHeight &&
						player2.y <= shootingEnemyBullet[i].y1)
					{
						//�z�����ݐ������ʉ�
						PlaySoundMem(succeedSuctionSound, DX_PLAYTYPE_BACK, TRUE);

						//�e������
						shootingEnemyBullet[i].isInScreenFlag = false;

						//�e��
						remainingBullet += healBullet;

						//�e�̏����ݒ�
						if (remainingBullet > MaxremainingBullet)
						{
							remainingBullet = MaxremainingBullet;
						}

						//�X�R�A�{���𑝂₷
						scoreMagnificatoin++;

						//�z�����ݐ����G�t�F�N�g�t���O��true�ɂ���
						suctionSucceedEffectFlag = true;
					}
				}
			}
		}
		//RB�{�^���������ĂȂ��Ƃ��͋z�����݌��ʉ����~�߂�
		else
		{
			StopSoundMem(suctionSound);
		}
	}
	//�N���A��������
	else
	{
		player1.x += 10;
		player2.x += 10;
	}
	
}

//�v���C���[�`��
void DrawPlayer(Player& player1, Player& player2, DINPUT_JOYSTATE input,int suctionEffect[],int& suctionEffectCount,bool& invincibleFlag,int& invincibleTimeCount, bool& suctionSucceedEffectFlag, int& suctionSucceedEffectCount, int suctionSucceedEffect[], int Lstick,int Rstick)
{
	//�R���g���[���[�̓��͏�Ԃ��擾
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	if (player1.isInScreenFlag && player2.isInScreenFlag)
	{
		if (input.Buttons[4] > 0 && input.Buttons[5] > 0 || input.Buttons[6] > 0 && input.Buttons[7] > 0)
		{
			//�v���C���[��`��
			if (invincibleFlag && invincibleTimeCount % 2 == 0)//�_�ŕ`��
			{
				
			}
			else //�ʏ�`��
			{
				DrawExtendGraph(player1.x - 75, player1.y - 25, player1.x + 50, player1.y + 50, Rstick, TRUE);
				DrawGraph(player1.x, player1.y, player1.actiongraph, TRUE);
				DrawExtendGraph(player2.x - 75, player2.y - 25, player2.x + 50, player2.y + 50, Lstick, TRUE);
				DrawGraph(player2.x, player2.y, player2.normalgraph, TRUE);
			}

			//�z�����݃J�E���g��0�ɂȂ�����7�ɖ߂�
			if (suctionEffectCount < 0)
			{
				suctionEffectCount = 7;
			}

			//�z�����݃G�t�F�N�g��`��
			DrawExtendGraph(player2.x + 300, player2.y - 50, player2.x + 50, player2.y + 275, suctionEffect[suctionEffectCount], TRUE);
			suctionEffectCount--;

		}
		else if (input.Buttons[5] > 0 || input.Buttons[7] > 0)
		{
			//�v���C���[��`��
			if (invincibleFlag && invincibleTimeCount % 2 == 0)//�_�ŕ`��
			{
				
			}
			else //�ʏ�`��
			{
				DrawExtendGraph(player1.x - 75, player1.y - 25, player1.x + 50, player1.y + 50, Rstick, TRUE);
				DrawGraph(player1.x, player1.y, player1.actiongraph, TRUE);
				DrawExtendGraph(player2.x - 75, player2.y - 25, player2.x + 50, player2.y + 50, Lstick, TRUE);
				DrawGraph(player2.x, player2.y, player2.normalgraph, TRUE);
			}
		}
		else if (input.Buttons[4] > 0 || input.Buttons[6] > 0)
		{
			//�v���C���[��`��
			if (invincibleFlag && invincibleTimeCount % 2 == 0)//�_�ŕ`��
			{
				
			}
			else //�ʏ�`��
			{
				DrawExtendGraph(player1.x - 75, player1.y - 25, player1.x + 50, player1.y + 50, Rstick, TRUE);
				DrawGraph(player1.x, player1.y, player1.normalgraph, TRUE);
				DrawExtendGraph(player2.x - 75, player2.y - 25, player2.x + 50, player2.y + 50, Lstick, TRUE);
				DrawGraph(player2.x, player2.y, player2.normalgraph, TRUE);
			}

			//�z�����݃J�E���g��0�ɂȂ�����8�ɖ߂�
			if (suctionEffectCount < 0)
			{
				suctionEffectCount = 7;
			}

			//�z�����݃G�t�F�N�g��`��
			DrawExtendGraph(player2.x + 300, player2.y - 50, player2.x + 50, player2.y + 275, suctionEffect[suctionEffectCount], TRUE);
			suctionEffectCount--;
		}
		else
		{
			//�v���C���[��`��
			if (invincibleFlag && invincibleTimeCount % 2 == 0)//�_�ŕ`��
			{

			}
			else //�ʏ�`��
			{
				DrawExtendGraph(player1.x - 75, player1.y - 25, player1.x + 50, player1.y + 50, Rstick, TRUE);
				DrawGraph(player1.x, player1.y, player1.normalgraph, TRUE);
				DrawExtendGraph(player2.x - 75, player2.y - 25, player2.x + 50, player2.y + 50, Lstick, TRUE);
				DrawGraph(player2.x, player2.y, player2.normalgraph, TRUE);
			}
		}
	}

	//�z�����ݐ����G�t�F�N�g��`��
	if (suctionSucceedEffectFlag)
	{
		if (player1.y < 40)
		{
			DrawExtendGraph(player1.x + 90, player1.y + 140, player1.x + 215, player1.y + 265, suctionSucceedEffect[suctionSucceedEffectCount], TRUE);
		}
		else
		{
			DrawExtendGraph(player1.x + 90, player1.y - 90, player1.x + 215, player1.y + 35, suctionSucceedEffect[suctionSucceedEffectCount], TRUE);
		}
		
		//�z�����ݐ����G�t�F�N�g�J�E���g�𑝂₷
		suctionSucceedEffectCount++;

		if (suctionSucceedEffectCount == 10)
		{
			suctionSucceedEffectCount = 0;
			suctionSucceedEffectFlag = false;
		}
	}
}