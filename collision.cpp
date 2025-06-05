#include"DxLib.h"
#include"player.h"
#include"enemy.h"
#include"shot.h"
#include"collision.h"
#include"block.h"
#include"scene.h"

//�v���C���[�̒e�̓����蔻��֐�
void hitPlayerBullet(Bullet PlayerBullet[], int PlayerShotNumber, Player& player2, Enemy zigzagEnemy[], int& score, Enemy straightEnemy[], Enemy shootingEnemy[], Enemy backEnemy[],Enemy raidEnemy[], int blockHP[], bool blockFlag[], int blockX1[], int blockX2[], int blockY1[], int blockY2[],int explosionSound)
{
    for (int i = 0; i < PlayerShotNumber; i++)
    {
        if (PlayerBullet[i].isInScreenFlag)
        {
            //�e����ʊO�ɂł������(�t���O��false�ɂ���)
            if (PlayerBullet[i].x1 > 1925)
            {
                PlayerBullet[i].isInScreenFlag = false;
            }

            //���ɒe����������������i�t�����h���[�t�@�C�A�j
            if (player2.x < PlayerBullet[i].x2 && PlayerBullet[i].x2 < player2.x + 270 && player2.y < PlayerBullet[i].y1 && PlayerBullet[i].y1 < player2.y + 175)
            {
                PlayerBullet[i].isInScreenFlag = false;
            }

            //�v���C���[�̒e����ʓ��ɂ���Ƃ�����
            if (PlayerBullet[i].x2 < 1925)
            {
                for (int j = 0; j  < zigzagEnemyNumber; j ++)
                {
                //�W�O�U�O�G����������(���ł�)�W�O�U�O�G�ƒe������
                    if (zigzagEnemy[j].isInScreenFlag)
                    {
                        if (zigzagEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < zigzagEnemy[j].x2 && zigzagEnemy[j].y1 < PlayerBullet[i].y2 && PlayerBullet[i].y2 < zigzagEnemy[j].y2 || zigzagEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < zigzagEnemy[j].x2 && zigzagEnemy[j].y1 < PlayerBullet[i].y1 && PlayerBullet[i].y1 < zigzagEnemy[j].y2)
                        {
							//�G��|�����Ƃ��̌��ʉ��𗬂�
							PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK, TRUE);

                            PlayerBullet[i].isInScreenFlag = false;
                            zigzagEnemy[j].isInScreenFlag = false;

                            //�X�R�A�𑝂₷
                            score += 10;
                        }
                    }
                }

                for (int j = 0; j < straightEnemyNumber; j++)
                {
                //�^�������G����������(���ł�)�^�������G�ƒe������
                    if (straightEnemy[j].isInScreenFlag)
                    {
                        if (straightEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < straightEnemy[j].x2 && straightEnemy[j].y1 < PlayerBullet[i].y2 && PlayerBullet[i].y2 < straightEnemy[j].y2 || straightEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < straightEnemy[j].x2 && straightEnemy[j].y1 < PlayerBullet[i].y1 && PlayerBullet[i].y1 < straightEnemy[j].y2)
                        {
							//�G��|�����Ƃ��̌��ʉ��𗬂�
							PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK, TRUE);

                            PlayerBullet[i].isInScreenFlag = false;
                            straightEnemy[j].isInScreenFlag = false;

                            //�X�R�A�𑝂₷
                            score += 10;
                        }
                    }
                }

                for (int j = 0; j < shootingEnemyNumber; j++)
                {
                //�����܂���G����������(���ł�)�����܂���G�ƒe������
                    if (shootingEnemy[j].isInScreenFlag)
                    {
                        if (shootingEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < shootingEnemy[j].x2 && shootingEnemy[j].y1 < PlayerBullet[i].y2 && PlayerBullet[i].y2 < shootingEnemy[j].y2 || shootingEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < shootingEnemy[j].x2 && shootingEnemy[j].y1 < PlayerBullet[i].y1 && PlayerBullet[i].y1 < shootingEnemy[j].y2)
                        {
							//�G��|�����Ƃ��̌��ʉ��𗬂�
							PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK, TRUE);

                            PlayerBullet[i].isInScreenFlag = false;
                            shootingEnemy[j].isInScreenFlag = false;

                            //�X�R�A�𑝂₷
                            score += 100;
                        }
                    }
                }
                
                for (int j = 0; j < backEnemyNumber; j++)
                {
                    //��납��G�ɓ���������e�ƓG������
                    if (backEnemy[j].isInScreenFlag)
                    {
                        if (backEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < backEnemy[j].x2 && backEnemy[j].y1 < PlayerBullet[i].y2 && PlayerBullet[i].y2 < backEnemy[j].y2 || backEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < backEnemy[j].x2 && backEnemy[j].y1 < PlayerBullet[i].y1 && PlayerBullet[i].y1 < backEnemy[j].y2 && j < 12)
                        {
							//�G��|�����Ƃ��̌��ʉ��𗬂�
							PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK, TRUE);

                            PlayerBullet[i].isInScreenFlag = false;
                            backEnemy[j].isInScreenFlag = false;

                            //�X�R�A�𑝂₷
                            score += 50;
                        }
                    }
                }

				for (int j = 0; j < raidEnemyNumber; j++)
				{
					//��P�G����������(���ł�)��P�G�ƒe������
					if (raidEnemy[j].isInScreenFlag)
					{
						if (raidEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < raidEnemy[j].x2 && raidEnemy[j].y1 < PlayerBullet[i].y2 && PlayerBullet[i].y2 < raidEnemy[j].y2 || raidEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < raidEnemy[j].x2 && raidEnemy[j].y1 < PlayerBullet[i].y1 && PlayerBullet[i].y1 < raidEnemy[j].y2)
						{
							//�G��|�����Ƃ��̌��ʉ��𗬂�
							PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK, TRUE);

							PlayerBullet[i].isInScreenFlag = false;
							raidEnemy[j].isInScreenFlag = false;

							//�X�R�A�𑝂₷
							score += 10;
						}
					}
				}

				for (int j = 0; j < blockNumber; j++)
				{
					//�u���b�N�ɓ���������e�������{�u���b�NHP�����炷
					if (blockFlag[j])
					{
						if (blockX1[j] < PlayerBullet[i].x2 && PlayerBullet[i].x2 < blockX2[j] && blockY1[j] < PlayerBullet[i].y2 && PlayerBullet[i].y2 < blockY2[j] || blockX1[j] < PlayerBullet[i].x2 && PlayerBullet[i].x2 < blockX2[j] && blockY1[j] < PlayerBullet[i].y1 && PlayerBullet[i].y1 < blockY2[j])
						{
							PlayerBullet[i].isInScreenFlag = false;
							//HP�����炷
							blockHP[j]--;

							//HP���O�ɂȂ�����t���O��false�ɂ��ĕǂ̓G�ƃu���b�N������
							if (blockHP[j] == 0)
							{
								//�G��|�����Ƃ��̌��ʉ��𗬂�
								PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK, TRUE);

								blockFlag[j] = false;
								backEnemy[2 + j].isInScreenFlag = false;

								//�X�R�A�𑝂₷
								score += 50;
							}
						}
					}
				}
            }
        }
    }
}

//�Q�[���I�[�o�[�֐�
void gameOver(Bullet zigzagEnemyBullet[],Player& player1,int bgm,int suctionSound,int succeedSuctionSound,Enemy backEnemy[],Player player2,int playerDeathSound,int& selectscene,Enemy shootingEnemy[],Bullet shootingEnemyBullet[],Enemy straightEnemy[],Enemy zigzagEnemy[],Enemy raidEnemy[],int skullEffect[],int& damage,bool& invincibleFlag)
{
	//���G���ԂłȂ���Γ����蔻��ɓ���
	if (!invincibleFlag && player1.x <= 1925 && player2.x <= 1925)
	{
		//�W�O�U�O�G�̒e�ɓ���������Q�[���I�[�o�[��ʂֈڍs
		for (int i = 0; i < zigzagEnemyShotNumber; i++)
		{
			if (zigzagEnemyBullet[i].isInScreenFlag)
			{
				//�����G�̃W�O�U�O�G�e�ɓ���������Q�[���I�[�o�[
				if (player1.x + nizyuugo < zigzagEnemyBullet[i].x1 && zigzagEnemyBullet[i].x1 < player1.x + hyakugozyuu && player1.y + nizyuugo < zigzagEnemyBullet[i].y1 && zigzagEnemyBullet[i].y1 < player1.y + hyakunanazyuugo
				 || player1.x + nizyuugo < zigzagEnemyBullet[i].x1 && zigzagEnemyBullet[i].x1 < player1.x + hyakugozyuu && player1.y + nizyuugo < zigzagEnemyBullet[i].y2 && zigzagEnemyBullet[i].y2 < player1.y + hyakunanazyuugo)
				{
					//�_���[�W���J�E���g����
					damage++;

					//���G�t���O��true�ɂ���
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE); //�_���[�W���ʉ��𗬂�

					//�_���[�W��4�ɂȂ�����Q�[���I�[�o�[
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
						StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[�͋z�����ݐ������ʉ����~�߂�
						StopSoundMem(bgm); //bgm���~�߂�

						//�ǂ���G�t�F�N�g������
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
				//�����G�̃W�O�U�O�G�e�ɓ���������Q�[���I�[�o�[
				if (player2.x + nizyuugo < zigzagEnemyBullet[i].x1 && zigzagEnemyBullet[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < zigzagEnemyBullet[i].y1 && zigzagEnemyBullet[i].y1 < player2.y + hyakunanazyuugo
				 || player2.x + nizyuugo < zigzagEnemyBullet[i].x1 && zigzagEnemyBullet[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < zigzagEnemyBullet[i].y2 && zigzagEnemyBullet[i].y2 < player2.y + hyakunanazyuugo)
				{
					//�_���[�W���J�E���g����
					damage++;

					//���G�t���O��true�ɂ���
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
						StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
						StopSoundMem(bgm); //bgm���~�߂�

						//�ǂ���G�t�F�N�g������
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
			}
		}

		//�����܂���G�̒e�ɂ���������Q�[���I�[�o�[��ʂ�
		for (int i = 0; i < shootingEnemyShotNumber; i++)
		{
			if (shootingEnemyBullet[i].isInScreenFlag)
			{
				//�����G�̂����܂���G�e�ɓ���������Q�[���I�[�o�[
				if (player1.x + nizyuugo < shootingEnemyBullet[i].x1 && shootingEnemyBullet[i].x1 < player1.x + hyakugozyuu && player1.y + nizyuugo < shootingEnemyBullet[i].y1 && shootingEnemyBullet[i].y1 < player1.y + hyakunanazyuugo
				 || player1.x + nizyuugo < shootingEnemyBullet[i].x1 && shootingEnemyBullet[i].x1 < player1.x + hyakugozyuu && player1.y + nizyuugo < shootingEnemyBullet[i].y2 && shootingEnemyBullet[i].y2 < player1.y + hyakunanazyuugo)
				{
					//�_���[�W���J�E���g����
					damage++;

					//���G�t���O��true�ɂ���
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
						StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
						StopSoundMem(bgm); //bgm���~�߂�
						
						//�ǂ���G�t�F�N�g������
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
				//�����G�̂����܂���G�e�ɓ���������Q�[���I�[�o�[
				if (player2.x + nizyuugo < shootingEnemyBullet[i].x1 && shootingEnemyBullet[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < shootingEnemyBullet[i].y1 && shootingEnemyBullet[i].y1 < player2.y + hyakunanazyuugo
				 || player2.x + nizyuugo < shootingEnemyBullet[i].x1 && shootingEnemyBullet[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < shootingEnemyBullet[i].y2 && shootingEnemyBullet[i].y2 < player2.y + hyakunanazyuugo)
				{
					//�_���[�W���J�E���g����
					damage++;

					//���G�t���O��true�ɂ���
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
						StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
						StopSoundMem(bgm); //bgm���~�߂�
						
						//�ǂ���G�t�F�N�g������
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
			}
		}

		//�W�O�U�O�G�ɓ���������Q�[���I�[�o�[��ʂֈڍs
		for (int i = 0; i < zigzagEnemyNumber; i++)
		{
			if (zigzagEnemy[i].isInScreenFlag)
			{
				//�����W�O�U�O�G�ɓ���������Q�[���I�[�o�[
				if (player1.x + nizyuugo < zigzagEnemy[i].x1 && zigzagEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < zigzagEnemy[i].y1 && zigzagEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < zigzagEnemy[i].x1 && zigzagEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < zigzagEnemy[i].y2 && zigzagEnemy[i].y2 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < zigzagEnemy[i].x2 && zigzagEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < zigzagEnemy[i].y1 && zigzagEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < zigzagEnemy[i].x2 && zigzagEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < zigzagEnemy[i].y2 && zigzagEnemy[i].y2 < player1.y + hyakugozyuu)
				{
					//�_���[�W���J�E���g����
					damage++;

					//���G�t���O��true�ɂ���
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
						StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
						StopSoundMem(bgm); //bgm���~�߂�
						
						//�ǂ���G�t�F�N�g������
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}

				//�����W�O�U�O�G�ɓ���������Q�[���I�[�o�[
				if (player2.x + nizyuugo < zigzagEnemy[i].x1 && zigzagEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < zigzagEnemy[i].y1 && zigzagEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < zigzagEnemy[i].x1 && zigzagEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < zigzagEnemy[i].y2 && zigzagEnemy[i].y2 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < zigzagEnemy[i].x2 && zigzagEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < zigzagEnemy[i].y1 && zigzagEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < zigzagEnemy[i].x2 && zigzagEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < zigzagEnemy[i].y2 && zigzagEnemy[i].y2 < player2.y + hyakugozyuu)
				{
					//�_���[�W���J�E���g����
					damage++;

					//���G�t���O��true�ɂ���
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
						StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
						StopSoundMem(bgm); //bgm���~�߂�

						//�ǂ���G�t�F�N�g������
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
			}

		}
		//�^�������G�ɂ���������Q�[���I�[�o�[��ʂ�
		for (int i = 0; i < straightEnemyNumber; i++)
		{
			if (straightEnemy[i].isInScreenFlag)
			{
				//�����^�������G�ɓ���������Q�[���I�[�o�[
				if (player1.x + nizyuugo < straightEnemy[i].x1 && straightEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < straightEnemy[i].y1 && straightEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < straightEnemy[i].x1 && straightEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < straightEnemy[i].y2 && straightEnemy[i].y2 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < straightEnemy[i].x2 && straightEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < straightEnemy[i].y1 && straightEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < straightEnemy[i].x2 && straightEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < straightEnemy[i].y2 && straightEnemy[i].y2 < player1.y + hyakugozyuu)
				{
					//�_���[�W���J�E���g����
					damage++;

					//���G�t���O��true�ɂ���
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
						StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
						StopSoundMem(bgm); //bgm���~�߂�

						//�ǂ���G�t�F�N�g������
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
				//�����^�������G�ɓ���������Q�[���I�[�o�[
				if (player2.x + nizyuugo < straightEnemy[i].x1 && straightEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < straightEnemy[i].y1 && straightEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < straightEnemy[i].x1 && straightEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < straightEnemy[i].y2 && straightEnemy[i].y2 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < straightEnemy[i].x2 && straightEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < straightEnemy[i].y1 && straightEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < straightEnemy[i].x2 && straightEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < straightEnemy[i].y2 && straightEnemy[i].y2 < player2.y + hyakugozyuu)
				{
					//�_���[�W���J�E���g����
					damage++;

					//���G�t���O��true�ɂ���
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
						StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
						StopSoundMem(bgm); //bgm���~�߂�

						//�ǂ���G�t�F�N�g������
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
			}
		}
		//�����܂���G�ɂ���������Q�[���I�[�o�[
		for (int i = 0; i < shootingEnemyNumber; i++)
		{
			if (shootingEnemy[i].isInScreenFlag)
			{
				//�����G�̂����܂���G�ɓ���������Q�[���I�[�o�[
				if (player1.x + nizyuugo < shootingEnemy[i].x1 && shootingEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < shootingEnemy[i].y1 && shootingEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < shootingEnemy[i].x1 && shootingEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < shootingEnemy[i].y2 && shootingEnemy[i].y2 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < shootingEnemy[i].x2 && shootingEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < shootingEnemy[i].y1 && shootingEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < shootingEnemy[i].x2 && shootingEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < shootingEnemy[i].y2 && shootingEnemy[i].y2 < player1.y + hyakugozyuu)
				{
					//�_���[�W���J�E���g����
					damage++;

					//���G�t���O��true�ɂ���
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
						StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
						StopSoundMem(bgm); //bgm���~�߂�

						//�ǂ���G�t�F�N�g������
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
				//���������܂���G�ɓ���������Q�[���I�[�o�[
				if (player2.x + nizyuugo < shootingEnemy[i].x1 && shootingEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < shootingEnemy[i].y1 && shootingEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < shootingEnemy[i].x1 && shootingEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < shootingEnemy[i].y2 && shootingEnemy[i].y2 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < shootingEnemy[i].x2 && shootingEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < shootingEnemy[i].y1 && shootingEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < shootingEnemy[i].x2 && shootingEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < shootingEnemy[i].y2 && shootingEnemy[i].y2 < player2.y + hyakugozyuu)
				{
					//�_���[�W���J�E���g����
					damage++;

					//���G�t���O��true�ɂ���
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
						StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
						StopSoundMem(bgm); //bgm���~�߂�
						

						//�ǂ���G�t�F�N�g������
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
			}
		}
		//��납��G�ɂ���������Q�[���I�[�o�[��ʂ�
		for (int i = 0; i < backEnemyNumber; i++)
		{
			if (backEnemy[i].isInScreenFlag)
			{
				//�ł����G�Ƃ̔���(����j
				if (i == 12 && backEnemy[12].x1 < player1.x && player1.x < backEnemy[12].x2 - 100 && backEnemy[12].y1 < player1.y && player1.y < backEnemy[12].y2)
				{
					//�_���[�W���J�E���g����
					damage++;

					//���G�t���O��true�ɂ���
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
						StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
						StopSoundMem(bgm); //bgm���~�߂�
						
						//�ǂ���G�t�F�N�g������
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
				//�ł����G�Ƃ̓����蔻��i��)
				else if (i == 12 && backEnemy[12].x1 < player2.x && player2.x < backEnemy[12].x2 - 100 && backEnemy[12].y1 < player2.y && player2.y < backEnemy[12].y2)
				{
					//�_���[�W���J�E���g����
					damage++;

					//���G�t���O��true�ɂ���
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
						StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
						StopSoundMem(bgm); //bgm���~�߂�
						
						//�ǂ���G�t�F�N�g������
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
				else
				{
					//�����G�̌�납��G�ɓ���������Q�[���I�[�o�[
					if (player1.x + nizyuugo < backEnemy[i].x1 && backEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < backEnemy[i].y1 && backEnemy[i].y1 < player1.y + hyakugozyuu
						|| player1.x + nizyuugo < backEnemy[i].x1 && backEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < backEnemy[i].y2 && backEnemy[i].y2 < player1.y + hyakugozyuu
						|| player1.x + nizyuugo < backEnemy[i].x2 && backEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < backEnemy[i].y1 && backEnemy[i].y1 < player1.y + hyakugozyuu
						|| player1.x + nizyuugo < backEnemy[i].x2 && backEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < backEnemy[i].y2 && backEnemy[i].y2 < player1.y + hyakugozyuu)
					{
						//�_���[�W���J�E���g����
						damage++;

						//���G�t���O��true�ɂ���
						invincibleFlag = true;

						PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

						//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
						if (damage >= overDamage)
						{
							StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
							StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
							StopSoundMem(bgm); //bgm���~�߂�
							
							//�ǂ���G�t�F�N�g������
							for (int i = 0; i < 15; i++)
							{
								DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
								WaitTimer(100);
							}

							selectscene = OVER;
							break;
						}
					}
					//������납��G�ɓ���������Q�[���I�[�o�[
					if (player2.x + nizyuugo < backEnemy[i].x1 && backEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < backEnemy[i].y1 && backEnemy[i].y1 < player2.y + hyakugozyuu
						|| player2.x + nizyuugo < backEnemy[i].x1 && backEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < backEnemy[i].y2 && backEnemy[i].y2 < player2.y + hyakugozyuu
						|| player2.x + nizyuugo < backEnemy[i].x2 && backEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < backEnemy[i].y1 && backEnemy[i].y1 < player2.y + hyakugozyuu
						|| player2.x + nizyuugo < backEnemy[i].x2 && backEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < backEnemy[i].y2 && backEnemy[i].y2 < player2.y + hyakugozyuu)
					{
						//�_���[�W���J�E���g����
						damage++;

						//���G�t���O��true�ɂ���
						invincibleFlag = true;

						PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

						//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
						if (damage >= overDamage)
						{
							StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
							StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
							StopSoundMem(bgm); //bgm���~�߂�
							

							//�ǂ���G�t�F�N�g������
							for (int i = 0; i < 15; i++)
							{
								DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
								WaitTimer(100);
							}

							selectscene = OVER;
							break;
						}
					}
				}
			}
		}
		//��P�G�ɂ���������Q�[���I�[�o�[��ʂ�
		for (int i = 0; i < raidEnemyNumber; i++)
		{
			if (raidEnemy[i].isInScreenFlag)
			{
				//������P�G�ɓ���������Q�[���I�[�o�[
				if (player1.x + nizyuugo < raidEnemy[i].x1 && raidEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < raidEnemy[i].y1 && raidEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < raidEnemy[i].x1 && raidEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < raidEnemy[i].y2 && raidEnemy[i].y2 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < raidEnemy[i].x2 && raidEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < raidEnemy[i].y1 && raidEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < raidEnemy[i].x2 && raidEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < raidEnemy[i].y2 && raidEnemy[i].y2 < player1.y + hyakugozyuu)
				{
					//�_���[�W���J�E���g����
					damage++;

					//���G�t���O��true�ɂ���
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
						StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
						StopSoundMem(bgm); //bgm���~�߂�
						
						//�ǂ���G�t�F�N�g������
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
				//������P�G�ɓ���������Q�[���I�[�o�[
				if (player2.x + nizyuugo < raidEnemy[i].x1 && raidEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < raidEnemy[i].y1 && raidEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < raidEnemy[i].x1 && raidEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < raidEnemy[i].y2 && raidEnemy[i].y2 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < raidEnemy[i].x2 && raidEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < raidEnemy[i].y1 && raidEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < raidEnemy[i].x2 && raidEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < raidEnemy[i].y2 && raidEnemy[i].y2 < player2.y + hyakugozyuu)
				{
					//�_���[�W���J�E���g����
					damage++;

					//���G�t���O��true�ɂ���
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//�_���[�W���S�ɂȂ�����Q�[���I�[�o�[
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // �Q�[���I�[�o�[�͋z�����݌��ʉ����~�߂�
						StopSoundMem(succeedSuctionSound); //�Q�[���I�[�o�[���͋z�����ݐ������ʉ����~�߂�
						StopSoundMem(bgm); //bgm���~�߂�
						
						//�ǂ���G�t�F�N�g������
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
			}
		}
	}
}