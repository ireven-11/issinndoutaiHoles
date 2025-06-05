#include"Dxlib.h"
#include"changeVolume.h"

void changeVolume(int shotSound,int startPauseSound,int finishPauseSound,int countDownSound,int suctionSound,int clearSound,int overSound,int succeedSuctionSound,int playerDeathSound,int correctSound,int bgm,int explosionSound)
{
	//âπÇÃëÂÇ´Ç≥Çê›íË
	ChangeVolumeSoundMem(250, shotSound);
	ChangeVolumeSoundMem(200, startPauseSound);
	ChangeVolumeSoundMem(200, finishPauseSound);
	ChangeVolumeSoundMem(175, countDownSound);
	ChangeVolumeSoundMem(110, suctionSound);
	ChangeVolumeSoundMem(250, clearSound);
	ChangeVolumeSoundMem(250, overSound);
	ChangeVolumeSoundMem(225, succeedSuctionSound);
	ChangeVolumeSoundMem(250, playerDeathSound);
	ChangeVolumeSoundMem(200, correctSound);
	ChangeVolumeSoundMem(145, bgm);
	ChangeVolumeSoundMem(250, explosionSound);
}