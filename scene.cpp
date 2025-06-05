#include"DxLib.h"
#include"scene.h"
#include"player.h"
#include"enemy.h"
#include"block.h"

void pauseScene(bool& startPauseFlag,int& BrinkCounter,int pauseScreenHandle,int FontSize100,int FontSize50,int bgm,int& startVideoCount,bool finishPauseFlag,int startPauseSound,int initialWIDTH,int HEIGHT,int& selectscene, DINPUT_JOYSTATE input,int warningSound)
{
	if (startPauseFlag)
	{
		StopSoundMem(warningSound);

		//�|�[�Y��ʊJ�n���ʉ�
		PlaySoundMem(startPauseSound, DX_PLAYTYPE_BACK, TRUE);
		startPauseFlag = false;
	}

	//�_�ŃJ�E���^�[�̐��l�𑝂₷
	BrinkCounter++;

	if (BrinkCounter == 60)
	{
		BrinkCounter = 0;
	}

	//�R���g���[���[�̓��͏�Ԃ��擾
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // ���������[�h
	DrawGraph(0, 0, pauseScreenHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �ʏ�`��ɖ߂�

	// �|�[�Y�����\��
	if (BrinkCounter < 40)
	{
		DrawStringToHandle(initialWIDTH / 2 - 150, HEIGHT / 3, "PAUSED", GetColor(255, 255, 255), FontSize100);
	}

	//B�{�^���Ń^�C�g���ɖ߂�
	/*DrawStringToHandle(initialWIDTH / 2 - 125, HEIGHT / 2 + 50, "B�Ń^�C�g����", GetColor(255, 255, 255), FontSize50);*/
	DrawStringToHandle(initialWIDTH / 2 - 125, HEIGHT / 2 + 50, "A�Ń^�C�g����", GetColor(255, 255, 255), FontSize50);
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B || CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		StopSoundMem(bgm); //bgm���~�߂�
		startVideoCount = 0;
		PlayMovie("video/finishuzumaki0.7.mp4", 1, DX_MOVIEPLAYTYPE_NORMAL);
		selectscene = TITLE;
	}

	//X�{�^���Ńv���C��ʂ֖߂�
	/*DrawStringToHandle(initialWIDTH / 2 - 150, HEIGHT / 2, "X�Ńv���C��ʂ�", GetColor(255, 255, 255), FontSize50);*/
	DrawStringToHandle(initialWIDTH / 2 - 150, HEIGHT / 2, "Y�Ńv���C��ʂ�", GetColor(255, 255, 255), FontSize50);
	if (input.Buttons[2] > 0)
	{
		//�|�[�Y��ʏI���t���O��true�ɂ���
		finishPauseFlag = true;

		selectscene = PLAY;
	}
}

void gameOverScene(bool& overSoundFlag,int overSound,int& BrinkCounter,int initialWIDTH,int HEIGHT,int FontSize50,int FontSize100,int& score,int& scoreMagnificatoin,int& startVideoCount,int FontSize300,int&selectscene)
{
	//�Q�[���I�[�o�[�����ʉ�
	if (overSoundFlag)
	{
		PlaySoundMem(overSound, DX_PLAYTYPE_BACK, TRUE);
		overSoundFlag = false;
	}

	//�_�ŃJ�E���^�[�̐��l�𑝂₷
	BrinkCounter++;

	if (BrinkCounter == 60)
	{
		BrinkCounter = 0;
	}

	//�Q�[���I�[�o�[
	DrawStringToHandle(initialWIDTH / 7, HEIGHT / 3, "GAME OVER", GetColor(255, 50, 50), FontSize300);

	//��ʑJ�ڂ̎w����`��
	if (BrinkCounter < 40)
	{
		/*DrawStringToHandle(initialWIDTH / 3 + 100, HEIGHT - 300, "B�{�^���Ń^�C�g���֖߂�", GetColor(255, 50, 50), FontSize50);*/
		DrawStringToHandle(initialWIDTH / 3 + 100, HEIGHT - 300, "A�{�^���Ń^�C�g���֖߂�", GetColor(255, 50, 50), FontSize50);
	}

	//�X�R�A�\��
	if (score * scoreMagnificatoin > 500000)
	{
		DrawFormatStringToHandle(1200, 40, GetColor(255, 255, 50), FontSize100, "SCORE:%d\nRANK:SSSSSSSSSSSS", score * scoreMagnificatoin);
	}
	else if (score * scoreMagnificatoin > 250000)
	{
		DrawFormatStringToHandle(1200, 40, GetColor(255, 255, 50), FontSize100, "SCORE:%d\nRANK:SSS", score * scoreMagnificatoin);
	}
	else if (score * scoreMagnificatoin > 100000)
	{
		DrawFormatStringToHandle(1200, 40, GetColor(255, 255, 50), FontSize100, "SCORE:%d\nRANK:S", score * scoreMagnificatoin);
	}
	else if (score * scoreMagnificatoin > 50000)
	{
		DrawFormatStringToHandle(1200, 40, GetColor(255, 255, 50), FontSize100, "SCORE:%d\nRANK:A", score * scoreMagnificatoin);
	}
	else if (score * scoreMagnificatoin > 25000)
	{
		DrawFormatStringToHandle(1200, 40, GetColor(255, 255, 50), FontSize100, "SCORE:%d\nRANK:B", score * scoreMagnificatoin);
	}
	else if (score * scoreMagnificatoin > 10000)
	{
		DrawFormatStringToHandle(1200, 40, GetColor(255, 255, 50), FontSize100, "SCORE:%d\nRANK:C", score * scoreMagnificatoin);
	}
	else
	{
		DrawFormatStringToHandle(1200, 40, GetColor(255, 255, 50), FontSize100, "SCORE:%d\nRANK:D", score * scoreMagnificatoin);
	}

	//B�{�^���Ń^�C�g���ɖ߂�
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B || CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		StopSoundMem(overSound);
		startVideoCount = 0;
		PlayMovie("video/finishuzumaki0.7.mp4", 1, DX_MOVIEPLAYTYPE_NORMAL);
		selectscene = TITLE;
	}
}

void clearScene(Player& player1, int initialWIDTH, Player& player2, int& BrinkCounter, int shotSound, int HEIGHT, int FontSize300, int FontSize30, bool& clearSoundFlag, int& score, int FontSize100, int& scoreMagnificatoin, int& damage, int& startVideoCount, int& selectscene, int suctionSound, int bgm, int clearSound, int FontSize50)
{
	if (player1.x > initialWIDTH && player2.x > initialWIDTH)
	{
		//�_�ŃJ�E���^�[�̐��l�𑝂₷
		BrinkCounter++;

		if (BrinkCounter == 60)
		{
			BrinkCounter = 0;
		}

		StopSoundMem(shotSound);
		StopSoundMem(suctionSound);

		//�Q�[���N���A�\��
		DrawStringToHandle(initialWIDTH / 10 - 50, HEIGHT / 3, "GAME CLEAR!!", GetColor(255, 255, 50), FontSize300);

		//�N���A�{�[�i�X�\��
		DrawStringToHandle(initialWIDTH / 3 + 150, HEIGHT - 350, "�N���A�{�[�i�X +10000", GetColor(255, 255, 50), FontSize30);

		//HP�{�[�i�X�\��
		DrawFormatStringToHandle(initialWIDTH / 3 + 200, HEIGHT - 300, GetColor(255, 255, 50), FontSize30, "HP�{�[�i�X �~%d", damage * -1 + 4);

		//�N���A�����ʉ����Đ�
		if (clearSoundFlag)
		{
			StopSoundMem(bgm); //bgm���~�߂�

			PlaySoundMem(clearSound, DX_PLAYTYPE_BACK, TRUE);
			clearSoundFlag = false;
		}

		//�����X�R�A�\��
		if ((score * scoreMagnificatoin + 10000) * (damage * -1 + 4) > 500000)
		{
			DrawFormatStringToHandle(1200, 40, GetColor(255, 255, 50), FontSize100, "SCORE:%d\nRANK:SSSSSSSSSSSSSSSSSSSSSSS", (score * scoreMagnificatoin + 10000) * (damage * -1 + 4));
		}
		else if ((score * scoreMagnificatoin + 10000) * (damage * -1 + 4) > 250000)
		{
			DrawFormatStringToHandle(1200, 40, GetColor(255, 255, 50), FontSize100, "SCORE:%d\nRANK:SSS", (score * scoreMagnificatoin + 10000) * (damage * -1 + 4));
		}
		else if ((score * scoreMagnificatoin + 10000) * (damage * -1 + 4) > 100000)
		{
			DrawFormatStringToHandle(1200, 40, GetColor(255, 255, 50), FontSize100, "SCORE:%d\nRANK:S", (score * scoreMagnificatoin + 10000) * (damage * -1 + 4));
		}
		else if ((score * scoreMagnificatoin + 10000) * (damage * -1 + 4) > 50000)
		{
			DrawFormatStringToHandle(1200, 40, GetColor(255, 255, 50), FontSize100, "SCORE:%d\nRANK:A", (score * scoreMagnificatoin + 10000) * (damage * -1 + 4));
		}
		else if ((score * scoreMagnificatoin + 10000) * (damage * -1 + 4) > 25000)
		{
			DrawFormatStringToHandle(1200, 40, GetColor(255, 255, 50), FontSize100, "SCORE:%d\nRANK:B", (score * scoreMagnificatoin + 10000) * (damage * -1 + 4));
		}
		else
		{
			DrawFormatStringToHandle(1200, 40, GetColor(255, 255, 50), FontSize100, "SCORE:%d\nRANK:C", (score * scoreMagnificatoin + 10000) * (damage * -1 + 4));
		}

		//��ʑJ�ڂ̎w����`��
		if (BrinkCounter < 40)
		{
			/*DrawStringToHandle(initialWIDTH / 3 + 50, HEIGHT - 200, "B�{�^���Ń^�C�g���֖߂�", GetColor(255, 50, 50), FontSize50);*/
			DrawStringToHandle(initialWIDTH / 3 + 50, HEIGHT - 200, "A�{�^���Ń^�C�g���֖߂�", GetColor(255, 50, 50), FontSize50);
		}

		//B�{�^���Ń^�C�g���ɖ߂�
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)
		{
			startVideoCount = 0;
			PlayMovie("video/finishuzumaki0.7.mp4", 1, DX_MOVIEPLAYTYPE_NORMAL);
			selectscene = TITLE;
		}
	}
}

//void proceedPause(int pauseScreenHandle,int& scroll,int wave4,int WIDTH,int HEIGHT,int backGraph,bool& blockFlag,int& blockHP,int& blockX1,int& blockX2,int& blockY1,int& blockY2,Player& player1,Player& player2,int blockGraph, DINPUT_JOYSTATE input, int suctionEffect, int& suctionEffectCount, bool& invincibleFlag, int& invincibleTimeCount, bool& suctionSucceedEffectFlag, int& suctionSucceedEffectCount, int suctionSucceedEffect, int Lstick, int Rstick, int wave1, Enemy& zigzagEnemy, int explosionEffect, Enemy& straightEnemy)
//{
//	//Y�{�^���Ń|�[�Y��ʂֈڍs(�����I�ɂ�X)
//	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_X)
//	{
//		// �Q�[����ʂ��o�b�t�@�ɕۑ�
//		SetDrawScreen(pauseScreenHandle); // �o�b�t�@�ɐ؂�ւ�
//		ClearDrawScreen(); // �o�b�t�@���N���A
//		// ���݂̃Q�[����ʂ�`��(�����f��j
//		//�w�i�`��
//		if (scroll < wave4)
//		{
//			DrawExtendGraph(0 - scroll, 0, WIDTH - scroll, HEIGHT, backGraph, TRUE);
//			DrawExtendGraph(10000 - scroll, 0, 10000 + WIDTH - scroll, HEIGHT, backGraph, TRUE);
//		}
//		//�u���b�N��`��
//		DrawBlock(blockGraph, blockHP, blockFlag, blockX1, blockX2, blockY1, blockY2, scroll);
//		//�v���C���[�̉摜��`��
//		DrawPlayer(player1, player2, input, suctionEffect, suctionEffectCount, invincibleFlag, invincibleTimeCount, suctionSucceedEffectFlag, suctionSucceedEffectCount, suctionSucceedEffect, Lstick, Rstick);
//		//�W�O�U�O�G�̕`��
//		if (scroll > wave1)
//		{
//			DrawZigzagEnemy(zigzagEnemy, explosionEffect);
//		}
//		if (scroll < wave1)
//		{
//			//�^�������G�̕`��
//			DrawStraightEnemy(straightEnemy, explosionEffect);
//		}
//		//�����܂���G�`��
//		DrawShootingEnemy(shootingEnemy, explosionEffect);
//		//��납��G�`��
//		DrawBackEnemy(backEnemy, explosionEffect);
//		//��P�G�`��
//		DrawRaidEnemy(raidEnemy, explosionEffect);
//		//�v���C���[�e�`��
//		DrawPlayerBullet(PlayerBullet, PlayerShotNumber);
//		for (int i = 0; i < zigzagEnemyShotNumber; i++)
//		{
//			//�W�O�U�O�G�e�`��
//			DrawZigzagEnemyBullet(zigzagEnemyBullet[i]);
//		}
//		for (int i = 0; i < shootingEnemyShotNumber; i++)
//		{
//			for (int j = 0; j < shootingEnemyNumber; j++)
//			{
//				//�����܂���G�e�`��
//				DrawShootingEnemyBullet(shootingEnemyBullet[i]);
//			}
//		}
//		DrawUI(scroll, wave4, selectscene, FontSize50, score, scoreMagnificatoin, player1, remainingBulletGraph, remainingBullet, HPgraph, damage, tutorial1and2Flag, initialWIDTH, HEIGHT, tutorial4Flag, FontSize100, BrinkCounter, tutorial3Flag);
//
//		SetDrawScreen(DX_SCREEN_FRONT); // �`����߂�
//
//		//�|�[�Y��ʊJ�n�t���O��ture�ɂ���
//		startPauseFlag = true;
//
//		//�|�[�Y��ʂ�
//		selectscene = PAUSE;
//	}
//}