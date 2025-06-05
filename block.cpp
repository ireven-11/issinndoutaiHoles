#include"DxLib.h"
#include"block.h"

//�u���b�N������
void InitializeBlock(int blockHP[],int blockX1[],int initialWIDTH,int blockX2[], int blockY1[], int blockY2[],int blockGraph[],bool blockFlag[])
{
	//�u���b�N�̉摜�𕪊��ǂݍ���
	LoadDivGraph("img/core.png", 3, 1, 3, 97, 199, blockGraph); 

	for (int i = 0; i < blockNumber; i++)
	{
		//�u���b�N�̏������W��ݒ�
		if (i < 10)
		{
			blockX1[i] = initialWIDTH;
			blockX2[i] = blockX1[i] + 75;
			blockY1[i] = 0 + i * 100;
			blockY2[i] = blockY1[i] + 100;

			//�u���b�N��HP��ݒ�
			blockHP[i] = 3;
		}
		else
		{
			blockX1[i] = initialWIDTH;
			blockX2[i] = blockX1[i] + 150;
			blockY1[i] = 0;
			blockY2[i] = blockY1[i] + 1000;

			blockHP[i] = 30;
		}
		//�t���O��true�ɂ���
		blockFlag[i] = true;
	}
}

//�u���b�N���[�`��
void UpdateBlock(int blockX1[], int blockX2[], int blockY1[], int blockY2[] ,int& scroll,int wave3)
{
	//wave4�ɂȂ�����u���b�N������
	if (scroll > wave3)
	{
		for (int i = 0; i < blockNumber; i++)
		{
			if (i < 10)
			{
				blockX1[i] -= 1;
				blockX2[i] -= 1;
			}
			else if(scroll % 5 == 0)
			{
				//�X�N���[�������ɂȂ�ƈ�C�ɔ����Ă���
				if (scroll > 20000)
				{
					blockX1[i] -= 30;
					blockX2[i] -= 30;
				}
				else
				{

					blockX1[i] -= 1;
					blockX2[i] -= 1;
				}
			}
		}
	}
}

//�u���b�N�`��
void DrawBlock(int blockGraph[], int blockHP[], bool blockFlag[], int blockX1[], int blockX2[], int blockY1[], int blockY2[] ,int& scroll)
{
	for (int i = 0; i < blockNumber; i++)
	{
		//�t���O��true�̂Ƃ������`��
		if (blockFlag[i])
		{
			//�u���b�N��HP�ɂ���ĉ摜��ς���
			if (i < 10)
			{
				if (blockHP[i] == 3)
				{
					DrawExtendGraph(blockX1[i], blockY1[i], blockX2[i], blockY2[i], blockGraph[0], TRUE);
				}
				else if (blockHP[i] == 2)
				{
					DrawExtendGraph(blockX1[i], blockY1[i], blockX2[i], blockY2[i], blockGraph[1], TRUE);
				}
				else if (blockHP[i] == 1)
				{
					DrawExtendGraph(blockX1[i], blockY1[i], blockX2[i], blockY2[i], blockGraph[2], TRUE);
				}
			}
			else
			{
				if (blockHP[i] > 20)
				{
					DrawExtendGraph(blockX1[i], blockY1[i], blockX2[i], blockY2[i], blockGraph[0], TRUE);
				}
				else if (blockHP[i] > 10)
				{
					DrawExtendGraph(blockX1[i], blockY1[i], blockX2[i], blockY2[i], blockGraph[1], TRUE);
				}
				else
				{
					DrawExtendGraph(blockX1[i], blockY1[i], blockX2[i], blockY2[i], blockGraph[2], TRUE);
				}
			}
		}

		//�N���A��ʂɂȂ��������
		if (scroll > 21000)
		{
			blockFlag[i] = false;
		}
	}
}