#pragma once

//�萔
const int blockNumber = 11; //�u���b�N�̐�

//�v���g�^�C�v�錾
void InitializeBlock(int blockHP[], int blockX1[], int initialWIDTH, int blockX2[], int blockY1[], int blockY2[], int blockGraph[], bool blockFlag[]);
void UpdateBlock(int blockX1[], int blockX2[], int blockY1[], int blockY2[], int& scroll, int wave3);
void DrawBlock(int blockGraph[], int blockHP[], bool blockFlag[], int blockX1[], int blockX2[], int blockY1[], int blockY2[], int& scroll);