#include"DxLib.h"
#include"UI.h"
#include"player.h"
#include"scene.h"

void DrawUI(int& scroll,int wave4,int& selectscene,int FontSize50,int& score,int& scoreMagnificatoin,Player& player1,int remainingBulletGraph,int& remainingBullet,int HPgraph[], int& damage,bool& tutorial1and2Flag,int initialWIDTH,int HEIGHT,bool& tutorial4Flag,int FontSize100,int& BrinkCounter,bool& tutorial3Flag,int& startVideoCount,int warningGraph[],int warningSound)
{
	switch (selectscene)
	{
	case TITLE:
		//��ʑJ�ڂ̎w����`��(�_��)
		if (startVideoCount > 400 && BrinkCounter < 30)
		{
			//DrawStringToHandle(initialWIDTH / 3 + 100, HEIGHT - 200, "B�{�^���Ń^�C�g���֖߂�", GetColor(255, 255, 50), FontSize50);
			DrawStringToHandle(initialWIDTH / 3 + 100, HEIGHT - 200, "A�{�^���Ń^�C�g���֖߂�", GetColor(255, 255, 50), FontSize50);
		}
		else if (BrinkCounter < 30)
		{
			//DrawStringToHandle(initialWIDTH / 3 + 150, HEIGHT - 200, "B�{�^���ŃX�^�[�g", GetColor(255, 255, 50), FontSize50);
			DrawStringToHandle(initialWIDTH / 3 + 150, HEIGHT - 200, "A�{�^���ŃX�^�[�g", GetColor(255, 255, 50), FontSize50);
		}

		break;
	case EXPLANE:
		//�E�ɗU������l�p��`��
		if (tutorial1and2Flag)
		{
			DrawBox(initialWIDTH / 2, 10, initialWIDTH - 10, HEIGHT - 20, GetColor(255, 50, 50), FALSE);
			DrawStringToHandle(initialWIDTH - 600, 400, "������\n �ړ�", GetColor(255, 50, 50), FontSize100);
		}

		if (tutorial4Flag)
		{
			DrawStringToHandle(initialWIDTH / 3 + 100, 75, "�`���[�g���A��", GetColor(255, 255, 255), FontSize100);
		}
		else
		{
			DrawStringToHandle(initialWIDTH / 3 + 125, 75, "���K���[�h", GetColor(255, 255, 255), FontSize100);
		}

		//������@��`��
		if (tutorial1and2Flag)
		{
			DrawStringToHandle(initialWIDTH / 4 + 125, 300, "2�FL�X�e�B�b�N�ō����E�Ɉړ����悤", GetColor(255, 255, 255), FontSize50);
			DrawStringToHandle(initialWIDTH / 4 + 125, 200, "1�FR�X�e�B�b�N�Ŕ����E�Ɉړ����悤", GetColor(255, 255, 255), FontSize50);
		}
		if (tutorial3Flag && !tutorial1and2Flag)
		{
			DrawStringToHandle(initialWIDTH / 4 + 50, 200, "3�FRB,RT�{�^���������Ĕ���5��ˌ����悤", GetColor(255, 255, 255), FontSize50);
		}
		if (tutorial4Flag && !tutorial3Flag)
		{
			DrawStringToHandle(initialWIDTH / 5 + 50, 200, "4�FLB,LT�{�^���������č��œG�̒e1�����z��������", GetColor(255, 255, 255), FontSize50);
		}

		if (BrinkCounter < 40)
		{
			/*DrawStringToHandle(initialWIDTH / 3 + 100, 800, "START�ŃQ�[���X�^�[�g", GetColor(255, 50, 50), FontSize50);*/
			DrawStringToHandle(initialWIDTH / 3 , 800, "�E�X�e�B�b�N�����݂ŃQ�[���X�^�[�g", GetColor(255, 50, 50), FontSize50);
		}

		//�c�e����\��
		if (player1.y < 40)
		{
			DrawExtendGraph(player1.x + 10, player1.y + 160, player1.x + 70, player1.y + 220, remainingBulletGraph, TRUE);
			DrawFormatStringToHandle(player1.x + 70, player1.y + 170, GetColor(255, 255, 50), FontSize50, "�~%d", remainingBullet);
		}
		else
		{
			DrawExtendGraph(player1.x + 10, player1.y - 60, player1.x + 70, player1.y, remainingBulletGraph, TRUE);
			DrawFormatStringToHandle(player1.x + 70, player1.y - 50, GetColor(255, 255, 50), FontSize50, "�~%d", remainingBullet);
		}

		//HP��\��
		DrawExtendGraph(20, 10, 520, 110, HPgraph[damage], TRUE);

		break;
	case PLAY:
		//�X�R�A�\��
		if (scroll < wave4)
		{
			DrawFormatStringToHandle(1400, 40, GetColor(255, 255, 50), FontSize50, "SCORE:%d �~ %d", score, scoreMagnificatoin);
		}

		//�c�e����\��
		if (player1.y < 40)
		{
			DrawExtendGraph(player1.x + 10, player1.y + 160, player1.x + 70, player1.y + 220, remainingBulletGraph, TRUE);
			DrawFormatStringToHandle(player1.x + 70, player1.y + 170, GetColor(255, 255, 50), FontSize50, "�~%d", remainingBullet);
		}
		else
		{
			DrawExtendGraph(player1.x + 10, player1.y - 60, player1.x + 70, player1.y, remainingBulletGraph, TRUE);
			DrawFormatStringToHandle(player1.x + 70, player1.y - 50, GetColor(255, 255, 50), FontSize50, "�~%d", remainingBullet);
		}

		//HP��\��
		DrawExtendGraph(20, 10, 520, 110, HPgraph[damage], TRUE);

		//�x�����𗬂�
		if (4000 == scroll || scroll == 6500 || scroll == 13500)
		{
			PlaySoundMem(warningSound, DX_PLAYTYPE_LOOP, TRUE);
		}

		if (4000 < scroll && scroll < 5000 && BrinkCounter < 30)
		{
			DrawExtendGraph(initialWIDTH / 3 + 175, HEIGHT / 3, initialWIDTH / 3 + 475, HEIGHT / 3 + 200, warningGraph[0], TRUE);
		}

		if (6500 < scroll && scroll < 7500 && BrinkCounter < 30)
		{
			DrawExtendGraph(initialWIDTH / 2 - 100, HEIGHT / 3, initialWIDTH / 2 + 100, HEIGHT / 3 + 100, warningGraph[1], TRUE);
			DrawExtendGraph(initialWIDTH / 2 - 110, HEIGHT / 3 + 100, initialWIDTH / 2 + 90, HEIGHT / 3 + 200, warningGraph[2], TRUE);
		}

		if (13500 < scroll && scroll < 14000 && BrinkCounter < 30)
		{
			DrawExtendGraph(initialWIDTH / 3 + 175, HEIGHT / 3, initialWIDTH / 3 + 475, HEIGHT / 3 + 200, warningGraph[0], TRUE);
		}

		if(scroll == 5000 || scroll == 7500 || scroll == 14000)
		{
			StopSoundMem(warningSound);
		}

		break;
	}
}