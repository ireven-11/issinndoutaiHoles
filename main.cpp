#include"DxLib.h"
#include"player.h"
#include"enemy.h"
#include"shot.h"
#include"collision.h"
#include"block.h"
#include"changeVolume.h"
#include"scene.h"
#include"UI.h"
#include"common.h"

//�R���g���[���[���g���Ƃ��̓R���g���[���[�̗��̐ݒ��D�ɂ���
//�R���g���[���[�̃{�^�����͂�ǂݎ��\���̕ϐ�
DINPUT_JOYSTATE input;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//----��{�ݒ�----

	//��ʑ傫���ύX�ϐ�
	int DesktopW, DesktopH;
	int WindowW, WindowH;

	//�萔�錾
	const int HEIGHT = 1000;       //��ʂ̍���
	const int initialWIDTH = 1925; //������ʂ̕�
	const int WIDTH = 11000;       //�w�i1���̕�
	const int scrollspeed = 4;	   //�X�N���[���X�s�[�h
	const int wave1 = 3000;	       //�E�F�[�u�P�̏I���
	const int wave2 = 7000;	       //�E�F�[�u�Q�̏I���
	const int wave3 = 14000;	   //�E�F�[�u3�̏I���
	const int wave4 = 21000;	   //�E�F�[�u4�̏I���
	const int IniBulletNumber = 30;//�����e��
	const int hyaku = 100;
	const int sannbyaku = 300;

	ChangeWindowMode(TRUE);				   //�E�B���h�E���[�h�ɂ���
	SetWindowStyleMode(7);				   //�ő剻�{�^�������݂���E�C���h�E���[�h�ɕύX

	// ��ʃT�C�Y���f�X�N�g�b�v�̃T�C�Y�Ɠ����ɂ���
	GetDefaultState(&DesktopW, &DesktopH, NULL);
	SetGraphMode(DesktopW, DesktopH, 32);

	// �T�C�Y�ύX���\�ɂ���
	SetWindowSizeChangeEnableFlag(TRUE, FALSE);

	// �E�C���h�E�T�C�Y�̓Q�[����ʂƈ�v������
	SetWindowSize(WIDTH, HEIGHT);

	// �E�C���h�E�̈ʒu�͉�ʒ��S�t�߂ɂ���
	SetWindowPosition((DesktopW - WIDTH) / 2, (DesktopH - HEIGHT) / 2);

	//���C�u������������
	DxLib_Init();

	// �E�C���h�E�T�C�Y���̏�����
	GetWindowSize(&WindowW, &WindowH);

	SetMainWindowText("�C�b�V���h�E�^�C�z�[���Y");
	SetDrawScreen(DX_SCREEN_BACK);		   //�w�i���Z�b�g����
	SetGraphMode(initialWIDTH, HEIGHT, 32);//�E�B���h�E�̃T�C�Y�ƃJ���[���[�h�����߂�
	//���C�u�����������ŃG���[�N������I��
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	//---------------

	//�ϐ��錾
	int	   selectscene;     			                //�V�[���ω�
	Player player1;										//�v���C���[1�̍\���̕ϐ�
	Player player2;										//�v���C���[�Q�̍\���̕ϐ�
	Enemy  TutorialEnemy;								//�`���[�g���A���G�̍\���̕ϐ�
	Bullet TutorialBullet;								//�`���[�g���A���e�̍\���̕ϐ�
	Bullet PlayerBullet[PlayerShotNumber];				//�v���C���[�̒e�̍\���̕ϐ��z��i�e�͉�ʂ�[]���̐����܂ł����łȂ��j
	bool   countDown;       				            //�J�E���g�_�E���t���O
	int	   scroll;				                        //�X�N���[���ϐ�
	Enemy  zigzagEnemy[zigzagEnemyNumber];				//�W�O�U�O�G�̍\���̕ϐ� ()�͓G�̐�
	Bullet zigzagEnemyBullet[zigzagEnemyShotNumber];	//�W�O�U�O�G�e�̍\���̕ϐ�
	int    score;										//�X�R�A
	int    scoreMagnificatoin;							//�X�R�A�{��
	int    FontSize125;                                 //�t�H���g�T�C�Y125
	int    FontSize50;                                  //�t�H���g�T�C�Y50
	int    FontSize100;                                 //�t�H���g�T�C�Y100
	int    FontSize300;                                 //�t�H���g�T�C�Y300
	int    FontSize30;                                  //�t�H���g�T�C�Y30
	int    pauseScreenHandle;							//�|�[�Y��ʗp�X�N���[���o�b�t�@
	bool   startPauseFlag;      				        //�|�[�Y��ʊJ�n�t���O
	bool   finishPauseFlag;     			            //�|�[�Y��ʏI���t���O
	bool   clearSoundFlag;      				        //�Q�[���N���A�T�E���h�t���O
	bool   overSoundFlag;       				        //�Q�[���I�[�o�[�T�E���h�t���O
	bool   tutorial1and2Flag;							//tutorial1and2�t���O
	int    BrinkCounter;    				            //�_�ŃJ�E���^�[
	bool   tutorial3Flag;								//tutorial3�t���O
	bool   tutorial4Flag;								//tutorial4�t���O
	bool   shotFlag;									//�V���b�g�t���O
	int    shotCount;									//�V���b�g�J�E���g
	bool   bgmFlag;										//bgm�t���O
	int    remainingBullet;								//�c�e
	Enemy  straightEnemy[straightEnemyNumber];			//�^�������G�̍\���̕ϐ�
	Enemy  shootingEnemy[shootingEnemyNumber];			//�����܂���G�̍\���̕ϐ�
	Bullet shootingEnemyBullet[shootingEnemyShotNumber];//�����܂���G�̒e�̍\���̕ϐ�
	Enemy  backEnemy[backEnemyNumber];					//��납��G�̍\���̕ϐ�
	Enemy  raidEnemy[raidEnemyNumber];					//��P�G�̍\���̕ϐ�
	int    blockGraph[3];								//�u���b�N�̉摜
	int    blockHP[blockNumber];						//�u���b�N��HP
	int    blockX1[blockNumber];						//�u���b�N�̍��WX1
	int    blockX2[blockNumber];						//�u���b�N�̍��WX2
	int	   blockY1[blockNumber];						//�u���b�N�̍��WY1
	int    blockY2[blockNumber];						//�u���b�N�̍��WY2
	bool   blockFlag[blockNumber];						//�u���b�N�̃t���O
	int    explosionEffect[11];							//�����G�t�F�N�g�摜
	int	   suctionEffect[8];							//�z�����݃G�t�F�N�g
	int    suctionEffectCount;							//�z�����݃J�E���g
	int    skullEffect[15];								//�ǂ���G�t�F�N�g
	int    PrevBbuttonFlag;     			            //B�{�^���������t���O
	int    HPgraph[5];									//hp�摜
	int    damage;										//�_���[�W
	int    invincibleTimeCount;							//���G���ԃJ�E���g
	bool   invincibleFlag;								//���G�t���O
	int    startVideoCount = 0;				            //���悪�n�܂�܂ł̃J�E���g
	int    suctionSucceedEffect[11];					//�z�����ݐ����G�t�F�N�g
	bool   suctionSucceedEffectFlag;        			//�z�����ݐ����G�t�F�N�g�t���O
	int    suctionSucceedEffectCount;					//�z�����ݐ����G�t�F�N�g�J�E���g
	int    backGraph;				                    //�v���C�w�i
	int    shotSound;			                        //�ˌ������ʉ�
	int    startPauseSound;	                            //�|�[�Y��ʊJ�n���ʉ�
	int    finishPauseSound;	                        //�|�[�Y��ʏI�����ʉ�
	int    countDownSound;		                        //�J�E���g�_�E�����ʉ�
	int    suctionSound;	                            //�z�����݌��ʉ�
	int    clearSound;			                        //�N���A�����ʉ�
	int    overSound;			                        //�I�[�o�[�����ʉ�
	int    succeedSuctionSound;                         //�z�����ݐ������ʉ�
	int    playerDeathSound;	                        //�G���G�̍U���ɓ��������u��
	int    hanamaruGraph;			                    //�Ԋ�
	int    correctSound;		                        //������
	int    bgm;		                                    //bgm
	int    remainingBulletGraph;			            //�e���G
	int    explosionSound;                              //�������ǂݍ���
	int    tutorialBack;				                //�`���[�g���A���w�i
	int    rogo;                                        //���S�摜��ǂݍ���
	int    Lstick;                                      //L�X�e�B�b�N�摜�ǂݍ���
	int    Rstick;		                                //R�X�e�B�b�N�摜�ǂݍ���
	int    DemoMovie;	                                //�f�����[�r�[�ǂݍ���
	int	   warningGraph[3];								//�x���摜
	int    warningSound;								//�x����

	//�ǂݍ���+������
	backGraph			 = LoadGraph("img/utyuu.png");				
	shotSound			 = LoadSoundMem("sound/shot.mp3");			
	startPauseSound		 = LoadSoundMem("sound/startpause.mp3");	
	finishPauseSound	 = LoadSoundMem("sound/finishpause.mp3");	
	countDownSound		 = LoadSoundMem("sound/countdown.mp3");		
	suctionSound		 = LoadSoundMem("sound/suction.wav");		
	clearSound			 = LoadSoundMem("sound/clear.mp3");			
	overSound			 = LoadSoundMem("sound/over.mp3");			
	succeedSuctionSound	 = LoadSoundMem("sound/succeedsuction.mp3");
	playerDeathSound	 = LoadSoundMem("sound/playerdeath.mp3");	
	hanamaruGraph		 = LoadGraph("img/hanamaru.png");			
	correctSound		 = LoadSoundMem("sound/correct.mp3");		
	bgm                  = LoadSoundMem("sound/pikopiko.mp3");	
	warningSound		 = LoadSoundMem("sound/warning.mp3");
	remainingBulletGraph = LoadGraph("img/tamakazu.png");			
	LoadDivGraph("img/effect/Part 17/847.png", 11, 11, 1, 64, 60, explosionEffect);
	explosionSound		 = LoadSoundMem("sound/explosion.mp3");     
	LoadDivGraph("img/wind.png", 8,8, 1, 240, 240, suctionEffect);	
	LoadDivGraph("img/born.png", 15, 15, 1, 64, 64, skullEffect);	
	tutorialBack		 = LoadGraph("img/utyuu.jpg");				
	LoadDivGraph("img/Heart.siro.png", 5, 1, 5, 264, 66, HPgraph);	
	rogo				 = LoadGraph("img/Pica-enhance-20250125103808.png");
	LoadDivGraph("img/effect/Part 27/1339.png", 11, 11, 1, 64, 60, suctionSucceedEffect);
	Lstick				 = LoadGraph("img/L�X�e�B�b�N.png");        
	Rstick				 = LoadGraph("img/R�X�e�B�b�N.png");		
	DemoMovie			 = LoadGraph("video/PlayMovie.mp4");
	LoadDivGraph("img/!.png", 3, 3, 1, 167, 99, warningGraph);
	selectscene			 = TITLE;
	countDown			 = true;
	scroll				 = 0;
	startPauseFlag		 = true;
	finishPauseFlag		 = false;
	clearSoundFlag		 = true;				      
	overSoundFlag		 = true;
	BrinkCounter		 = 0;
	PrevBbuttonFlag		 = false;
	startVideoCount		 = 0;
	suctionSucceedEffectFlag = false;

	//�t�H���g���g����悤�ɂ���
	AddFontResourceEx("font/BugMaruUI.ttc", FR_PRIVATE, NULL);
	FontSize125			 = CreateFontToHandle("BugMaru UI", 125, 10, DX_FONTTYPE_EDGE);
	FontSize50			 = CreateFontToHandle("BugMaru UI", 50, 10, DX_FONTTYPE_EDGE);
	FontSize100			 = CreateFontToHandle("BugMaru UI", 100, 10, DX_FONTTYPE_EDGE);
	FontSize300			 = CreateFontToHandle("BugMaru UI", 300, 10, DX_FONTTYPE_EDGE);
	FontSize30			 = CreateFontToHandle("BugMaru UI", 30, 10, DX_FONTTYPE_EDGE);

	// �X�N���[���o�b�t�@���쐬
	pauseScreenHandle = MakeScreen(initialWIDTH, HEIGHT, TRUE);
	if (pauseScreenHandle == -1) 
	{
		DxLib_End();
		return -1;
	}

	//���̑傫���𒲐�
	changeVolume(shotSound, startPauseSound, finishPauseSound, countDownSound, suctionSound, clearSound, overSound, succeedSuctionSound,  playerDeathSound, correctSound, bgm, explosionSound);

	//�Q�[�����[�v
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 )
	{
		ClearDrawScreen();

		// �E�C���h�E�̃N���C�A���g�̈���擾����
		GetWindowSize(&WindowW, &WindowH);

		//�V�[���؂�ւ�
		switch (selectscene)
		{
		case TITLE:
			//���S�摜��`��
			DrawExtendGraph(0, 0, initialWIDTH, HEIGHT, rogo, TRUE);

			//�_�ŃJ�E���^�[�̐��l�𑝂₷
			BrinkCounter++;

			//����̃J�E���g�𑝂₷
			startVideoCount++;

			if (BrinkCounter == 60)
			{
				BrinkCounter = 0;
			}

			//B�{�^���Ő�����ʂ�
			if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B || CheckHitKey(KEY_INPUT_RETURN) == 1)
			{
				if (!PrevBbuttonFlag)
				{
					//������
					InitializePlayer(player1, player2);
					InitializeTutorialEnemy(TutorialEnemy, TutorialBullet);
					InitializePlayerBullet(PlayerBullet, PlayerShotNumber, player1);
					InitializeZigzagEnemy(zigzagEnemy);
					for (int i = 0; i < zigzagEnemyShotNumber; i++)
					{
						AwakeZigzagEnemyBullet(zigzagEnemyBullet[i]);
					}
					countDown = true;
					scroll = 0;
					score = 0;
					scoreMagnificatoin = 0;
					clearSoundFlag = true;
					overSoundFlag = true;
					tutorial1and2Flag = true;
					tutorial3Flag = true;
					tutorial4Flag = true;
					shotFlag = false;
					shotCount = 0;
					bgmFlag = true;
					remainingBullet = IniBulletNumber;
					InitializeStraightEnemy(straightEnemy);
					InitializeShootingEnemy(shootingEnemy);
					for (int i = 0; i < shootingEnemyShotNumber; i++)
					{
						AwakeShootingEnemyBullet(shootingEnemyBullet[i]);
					}
					InitializeBackEnemy(backEnemy);
					InitializeRaidEnemy(raidEnemy);
					InitializeBlock(blockHP, blockX1, initialWIDTH, blockX2, blockY1, blockY2, blockGraph, blockFlag);
					suctionEffectCount = 7;
					damage = 0;
					invincibleFlag = false;
					invincibleTimeCount = 0;
					startVideoCount = 0;
					suctionSucceedEffectCount = 0;
					selectscene = EXPLANE;
					PlayMovie("video/startuzumaki0.7.mp4", 1, DX_MOVIEPLAYTYPE_NORMAL);
				}
				PrevBbuttonFlag = true;
			}
			else
			{
				PrevBbuttonFlag = false;
			}

			//�J�E���g�����ɂȂ����瓮��𗬂�
			if (startVideoCount > 400)
			{
				PlayMovieToGraph(DemoMovie);

				DrawGraph(0, 0, DemoMovie, FALSE);

				//B�{�^������������^�C�g���֖߂�
				if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B || startVideoCount > 3000)
				{
					startVideoCount = 0;
					PauseMovieToGraph(DemoMovie);
					SeekMovieToGraph(DemoMovie, 0);
				}

				PrevBbuttonFlag = true;
			}

			//Ui��`��
			DrawUI(scroll, wave4, selectscene, FontSize50, score, scoreMagnificatoin, player1, remainingBulletGraph, remainingBullet, HPgraph, damage, tutorial1and2Flag, initialWIDTH, HEIGHT, tutorial4Flag, FontSize100, BrinkCounter, tutorial3Flag, startVideoCount, warningGraph, warningSound);
			
			break;

		case EXPLANE:
			//�R���g���[���[�̓��͏�Ԃ��擾
			GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

			//�w�i�`��
			DrawExtendGraph(0, 0, initialWIDTH, HEIGHT, backGraph,TRUE);

			//�L�����̉摜��`��
			DrawPlayer(player1, player2, input,suctionEffect, suctionEffectCount, invincibleFlag, invincibleTimeCount, suctionSucceedEffectFlag, suctionSucceedEffectCount, suctionSucceedEffect, Lstick, Rstick);

			//�`���[�g���A���G��`��
			DrawTutorialEnemy(TutorialEnemy);

			//Ui��`��
			DrawUI(scroll, wave4, selectscene, FontSize50, score, scoreMagnificatoin, player1, remainingBulletGraph, remainingBullet, HPgraph, damage, tutorial1and2Flag, initialWIDTH, HEIGHT, tutorial4Flag, FontSize100, BrinkCounter, tutorial3Flag, startVideoCount, warningGraph, warningSound);

			//�_�ŃJ�E���^�[�̐��l�𑝂₷
			BrinkCounter++;

			if (BrinkCounter == 60)
			{
				BrinkCounter = 0;
			}
			
			//�v���C���[���[�`��
			UpdatePlayer(player1, player2, input, zigzagEnemyBullet, scoreMagnificatoin, suctionSound, succeedSuctionSound, remainingBullet, shootingEnemyBullet, blockFlag, blockX1, blockX2, blockY1, blockY2, scroll, wave4, suctionSucceedEffectFlag);

			//�v���C���[�L�����������E���ɂ�������tutorial1and2�t���O��false�ɂ��ĉ��o��������
			if (player1.x > initialWIDTH / 2 && player2.x > initialWIDTH / 2)
			{
				if (tutorial1and2Flag)
				{
					DrawExtendGraph(initialWIDTH / 3, 100, initialWIDTH / 3 + 500, 600, hanamaruGraph, TRUE);
					PlaySoundMem(correctSound, DX_PLAYTYPE_BACK);
					WaitTimer(500);
				}
				tutorial1and2Flag = false;

				//�e���Ȃ��Ȃ�����
				if (remainingBullet == 0)
				{
					remainingBullet += 5;
				}
			}

			//�`���[�g���A���G�l�~�[���[�`��
			UpdateTutorialEnemy(TutorialEnemy);

			//�v���C���[�e���[�`��
			UpdatePlayerBullet(PlayerBullet, PlayerShotNumber, player1, input, shotSound, remainingBullet);

			//�v���C���[���e�����������ɃV���b�g�J�E���g�𑝂₷
			if (input.Buttons[5] > 0 && !tutorial1and2Flag || input.Buttons[7] > 0 && !tutorial1and2Flag)
			{
				if (!shotFlag)
				{
					shotCount++;
					shotFlag = true;
				}
			}
			else
			{
				shotFlag = false;
			}

			//�v���C���[�e�̕`��
			DrawPlayerBullet(PlayerBullet, PlayerShotNumber);

			//�V���b�g�J�E���g�����ɂȂ����牉�o������
			if (shotCount == 5 && !tutorial1and2Flag)
			{
				if (tutorial3Flag)
				{
					DrawExtendGraph(initialWIDTH / 3, 100, initialWIDTH / 3 + 500, 600, hanamaruGraph, TRUE);
					PlaySoundMem(correctSound, DX_PLAYTYPE_BACK);
					WaitTimer(500);
				}
				tutorial3Flag = false;
			}

			if (!tutorial3Flag)
			{
				//�`���[�g���A���G�e���[�`��
				UpdateTutorialBullet(TutorialBullet, TutorialEnemy);

				//�`���[�g���A���G�e�`��
				DrawTutorialBullet(TutorialBullet);

				if (input.Buttons[4] > 0 || input.Buttons[6] > 0)
				{
					//���܂��z�����񂾎��ɉ��o��������
					if (player2.x + 125 < TutorialBullet.x1 &&	//xmin�����蔻��
						TutorialBullet.x1 < player2.x + 251 &&	//xmax�����蔻��
						player2.y < TutorialBullet.y2 &&		//ymin�����蔻��
						TutorialBullet.y2 < player2.y + 204		//ymax�����蔻��
						|| player2.x + 125 < TutorialBullet.x1 &&
						TutorialBullet.x1 < player2.x + 251 &&
						TutorialBullet.y1 < player2.y + 204 &&
						player2.y < TutorialBullet.y1)
					{
						//�z�����ݐ������ʉ�
						PlaySoundMem(succeedSuctionSound, DX_PLAYTYPE_BACK, TRUE);

						//�e������
						TutorialBullet.isInScreenFlag = false;

						//�c�e���𑝂₷
						remainingBullet += healBullet;

						//�z�����ݐ����G�t�F�N�g�t���O��true�ɂ���
						suctionSucceedEffectFlag = true;

						//�e�̏����ݒ�
						if (remainingBullet > 80)
						{
							remainingBullet = 80;
						}

						//���o��������
						if (tutorial4Flag)
						{
							DrawExtendGraph(initialWIDTH / 3, 100, initialWIDTH / 3 + 500, 600, hanamaruGraph, TRUE);
							PlaySoundMem(correctSound, DX_PLAYTYPE_BACK);
							WaitTimer(500);
						}
						tutorial4Flag = false;
					}
				}
			}

			//�v���C���[�e�̃t���O�Ǘ��i�����蔻��)
			hitPlayerBullet(PlayerBullet, PlayerShotNumber, player2, zigzagEnemy, score, straightEnemy, shootingEnemy, backEnemy, raidEnemy, blockHP, blockFlag, blockX1, blockX2, blockY1, blockY2, explosionSound);

			//�X�^�[�g�{�^���Ńv���C��ʂ�
			if (input.Buttons[11] > 0 || CheckHitKey(KEY_INPUT_SPACE) == 1)
			{
				selectscene = PLAY;

				//�J�E���g�_�E��
				if (countDown)
				{
					StopSoundMem(suctionSound); // �J�E���g�_�E�����͋z�����݌��ʉ����~�߂�
					StopSoundMem(succeedSuctionSound); //�J�E���g�_�E�����͋z�����ݐ������ʉ����~�߂�
					PlaySoundMem(countDownSound, DX_PLAYTYPE_BACK, TRUE); //�J�E���g�_�E����
					DrawBox(0, 0, initialWIDTH, HEIGHT, GetColor(0, 0, 0), TRUE); //�O��ʂ��B��
					DrawStringToHandle(initialWIDTH / 2 - 100, HEIGHT / 3, "3", GetColor(255, 255, 50), FontSize300);
					WaitTimer(1000);
					DrawBox(0, 0, initialWIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);
					DrawStringToHandle(initialWIDTH / 2 - 100, HEIGHT / 3, "2", GetColor(255, 255, 50), FontSize300);
					WaitTimer(1000);
					DrawBox(0, 0, initialWIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);
					DrawStringToHandle(initialWIDTH / 2 - 100, HEIGHT / 3, "1", GetColor(255, 255, 50), FontSize300);
					WaitTimer(1000);
					DrawBox(0, 0, initialWIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);
					DrawStringToHandle(initialWIDTH / 4, HEIGHT / 3, "START!", GetColor(255, 255, 50), FontSize300);
					WaitTimer(500);
					remainingBullet = IniBulletNumber; //�c�e����߂�
					//�v���C���[���������W�ɖ߂�
					player1.x = sannbyaku;
					player1.y = sannbyaku;
					player2.x = hyaku;
					player2.y = sannbyaku;
					for ( int i = 0; i < PlayerShotNumber; i++)
					{
						PlayerBullet[i].isInScreenFlag = false;
					}
					countDown = false;
				}
			}

			break;
		case PLAY:
			//�|�[�Y��ʏI�����ʉ�
			if (finishPauseFlag)
			{
				PlaySoundMem(finishPauseSound, DX_PLAYTYPE_BACK, TRUE);
				finishPauseFlag = false;
			}

			//�_�ŃJ�E���^�[�̐��l�𑝂₷
			BrinkCounter++;

			if (BrinkCounter == 60)
			{
				BrinkCounter = 0;
			}

			//�X�N���[��������
			scroll += scrollspeed;

			//���G�t���O��ture�̂Ƃ��ɖ��G���Ԃ��v�Z
			if (invincibleFlag)
			{
				invincibleTimeCount++;

				//���G���Ԃ���莞�Ԃ������疳�G�t���O��true�ɂ���
				if (invincibleTimeCount > 125)
				{
					invincibleFlag = false;
					invincibleTimeCount = 0;
				}
			}

			//�N���A���
			clearScene(player1, initialWIDTH, player2, BrinkCounter, shotSound, HEIGHT, FontSize300, FontSize30, clearSoundFlag, score,  FontSize100, scoreMagnificatoin, damage, startVideoCount, selectscene, suctionSound, bgm, clearSound, FontSize50);

			//bgm�t���O��true�̂Ƃ�����bgm���Ȃ���
			if (bgmFlag)
			{
				PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
				bgmFlag = false;
			}

			//�w�i�`��
			if (scroll < wave4)
			{
				DrawExtendGraph(0 - scroll, 0, WIDTH - scroll, HEIGHT, backGraph, TRUE);
				DrawExtendGraph(10000 - scroll, 0, 10000 + WIDTH - scroll, HEIGHT, backGraph, TRUE);
			}

			//�u���b�N���[�`��
			UpdateBlock(blockX1, blockX2, blockY1, blockY2, scroll, wave3);

			//�u���b�N��`��
			DrawBlock(blockGraph, blockHP, blockFlag, blockX1, blockX2, blockY1, blockY2, scroll);

			//�v���C���[���[�`��
			UpdatePlayer(player1, player2, input, zigzagEnemyBullet, scoreMagnificatoin, suctionSound, succeedSuctionSound, remainingBullet, shootingEnemyBullet, blockFlag, blockX1, blockX2, blockY1, blockY2, scroll, wave4, suctionSucceedEffectFlag);

			//�v���C���[�̉摜��`��
			DrawPlayer(player1, player2, input, suctionEffect, suctionEffectCount, invincibleFlag, invincibleTimeCount, suctionSucceedEffectFlag, suctionSucceedEffectCount, suctionSucceedEffect, Lstick, Rstick);
			
			//�v���C���[�e���[�`��
			UpdatePlayerBullet(PlayerBullet, PlayerShotNumber, player1, input, shotSound, remainingBullet);

			//�X�N���[�������ɒB����ƓG���o��
			if (scroll > wave1)
			{
				//�W�O�U�O�G�l�~�[���[�`��
				UpdateZigzagEnemy(zigzagEnemy);

				//�W�O�U�O�G�̕`��
				DrawZigzagEnemy(zigzagEnemy, explosionEffect);
			}

			if (scroll < wave1)
			{
				//�^�������G���[�`��
				UpdateStraightEnemy(straightEnemy);

				//�^�������G�̕`��
				DrawStraightEnemy(straightEnemy, explosionEffect);
			}

			//�����܂���G���[�`��
			UpdateShootingEnemy(shootingEnemy, scroll);

			//�����܂���G�`��
			DrawShootingEnemy(shootingEnemy, explosionEffect);

			//��납��G���[�`��
			UpdateBackEnemy(backEnemy, wave1, scroll, player2, wave3, wave4);

			//��납��G�`��
			DrawBackEnemy(backEnemy, explosionEffect);

			//��P�G���[�`��
			UpdateRaidEnemy(raidEnemy, scroll, wave2);

			//��P�G�`��
			DrawRaidEnemy(raidEnemy,explosionEffect);

			//�v���C���[�e�̃t���O�Ǘ��i�����蔻��)
			hitPlayerBullet(PlayerBullet, PlayerShotNumber, player2, zigzagEnemy, score, straightEnemy, shootingEnemy,backEnemy, raidEnemy, blockHP, blockFlag, blockX1, blockX2, blockY1, blockY2, explosionSound);

			//�v���C���[�e�`��
			DrawPlayerBullet(PlayerBullet, PlayerShotNumber);

			//�e�𔭎ˏo����G�����邩�T��
			for (int i = 0; i < zigzagEnemyNumber; i++)
			{
				if (zigzagEnemy[i].x1 == 1300 || zigzagEnemy[i].x1 == 1000 || zigzagEnemy[i].x1 == 700)
				{
					//�e���󂢂Ă��邩
					for (int j = 0; j < zigzagEnemyShotNumber; j++)
					{
						//���݂��Ă��邩
						if (!zigzagEnemyBullet[j].isInScreenFlag)
						{
							//�W�O�U�O�G�e����
							InitializeZigzagEnemyBullet(zigzagEnemyBullet[j], zigzagEnemy[i]);
							break;
						}
					}
				}
			}

			for (int i = 0; i < zigzagEnemyShotNumber; i++)
			{
				//�W�O�U�O�G�e���[�`��
				UpdateZigzagEnemyBullet(zigzagEnemyBullet[i]);
				//�W�O�U�O�G�e�`��
				DrawZigzagEnemyBullet(zigzagEnemyBullet[i]);
			}

			//�e�𔭎ˏo����G�����邩�T��
			for (int i = 0; i < shootingEnemyNumber; i++)
			{
				//�G����ʓ��ɂ��邩�������v���C���[���G��荶�ɂ��邩
				if (shootingEnemy[i].x1 < initialWIDTH && player1.x - shootingEnemy[i].x1 < 0)
				{
					//�ŏ���4��
					if (i <= 4)
					{
						//���̍��W�ɂ��邩
						if (shootingEnemy[i].y1 == 0 || shootingEnemy[i].y1 == 1000 || shootingEnemy[i].y1 == 250 || shootingEnemy[i].y1 == 750 || shootingEnemy[i].y1 == 500)
						{
							//�e���󂢂Ă��邩
							for (int j = 0; j < shootingEnemyShotNumber; j++)
							{
								//���݂��Ă��邩
								if (!shootingEnemyBullet[j].isInScreenFlag)
								{
									//�����܂���G�e����
									InitializeShootingEnemyBullet(shootingEnemyBullet[j], shootingEnemy[i], player1);
									break;
								}
							}
						}
					}
					else
					{
						if (scroll % 500 == 0)
						{
							//�e���󂢂Ă��邩
							for (int j = 0; j < shootingEnemyShotNumber; j++)
							{
								//���݂��Ă��邩
								if (!shootingEnemyBullet[j].isInScreenFlag)
								{
									//�����܂���G�e����
									InitializeShootingEnemyBullet(shootingEnemyBullet[j], shootingEnemy[i], player1);
									break;
								}
							}
						}
					}
				}
			}

			for (int i = 0; i < shootingEnemyShotNumber; i++)
			{
				//�����܂���G�e���[�`��
				UpdateShootingEnemyBullet(shootingEnemyBullet[i]);
				for (int j = 0; j < shootingEnemyNumber; j++)
				{
					//�����܂���G�e�`��
					DrawShootingEnemyBullet(shootingEnemyBullet[i]);
				}

				//�N���A������t���O��false�ɂ���
				if (scroll > wave4)
				{
					shootingEnemyBullet[i].isInScreenFlag = false;
				}
			}

			//Ui��`��
			DrawUI(scroll, wave4, selectscene, FontSize50, score, scoreMagnificatoin, player1, remainingBulletGraph, remainingBullet, HPgraph, damage, tutorial1and2Flag, initialWIDTH, HEIGHT, tutorial4Flag, FontSize100, BrinkCounter, tutorial3Flag, startVideoCount, warningGraph, warningSound);

			//Y�{�^���Ń|�[�Y��ʂֈڍs(�����I�ɂ�X)
			if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_X)
			{
				// �Q�[����ʂ��o�b�t�@�ɕۑ�
				SetDrawScreen(pauseScreenHandle); // �o�b�t�@�ɐ؂�ւ�
				ClearDrawScreen(); // �o�b�t�@���N���A
				// ���݂̃Q�[����ʂ�`��(�����f��j
				//�w�i�`��
				if (scroll < wave4)
				{
					DrawExtendGraph(0 - scroll, 0, WIDTH - scroll, HEIGHT, backGraph, TRUE);
					DrawExtendGraph(10000 - scroll, 0, 10000 + WIDTH - scroll, HEIGHT, backGraph, TRUE);
				}
				//�u���b�N��`��
				DrawBlock(blockGraph, blockHP, blockFlag, blockX1, blockX2, blockY1, blockY2, scroll);
				//�v���C���[�̉摜��`��
				DrawPlayer(player1, player2, input, suctionEffect, suctionEffectCount, invincibleFlag, invincibleTimeCount,suctionSucceedEffectFlag, suctionSucceedEffectCount, suctionSucceedEffect, Lstick, Rstick);
				//�W�O�U�O�G�̕`��
				if (scroll > wave1)
				{
					DrawZigzagEnemy(zigzagEnemy, explosionEffect);
				}
				if (scroll < wave1)
				{
					//�^�������G�̕`��
					DrawStraightEnemy(straightEnemy, explosionEffect);
				}
				//�����܂���G�`��
				DrawShootingEnemy(shootingEnemy, explosionEffect);
				//��납��G�`��
				DrawBackEnemy(backEnemy, explosionEffect);
				//��P�G�`��
				DrawRaidEnemy(raidEnemy, explosionEffect);
				//�v���C���[�e�`��
				DrawPlayerBullet(PlayerBullet, PlayerShotNumber);
				for (int i = 0; i < zigzagEnemyShotNumber; i++)
				{
					//�W�O�U�O�G�e�`��
					DrawZigzagEnemyBullet(zigzagEnemyBullet[i]);
				}
				for (int i = 0; i < shootingEnemyShotNumber; i++)
				{
					for (int j = 0; j < shootingEnemyNumber; j++)
					{
						//�����܂���G�e�`��
						DrawShootingEnemyBullet(shootingEnemyBullet[i]);
					}
				}
				DrawUI(scroll, wave4, selectscene, FontSize50, score, scoreMagnificatoin, player1, remainingBulletGraph, remainingBullet, HPgraph, damage, tutorial1and2Flag, initialWIDTH, HEIGHT, tutorial4Flag, FontSize100, BrinkCounter, tutorial3Flag, startVideoCount, warningGraph, warningSound);

				SetDrawScreen(DX_SCREEN_FRONT); // �`����߂�

				//�|�[�Y��ʊJ�n�t���O��ture�ɂ���
				startPauseFlag = true;

				//�|�[�Y��ʂ�
				selectscene = PAUSE;
			}

			//�Q�[���I�[�o�[�̔���
			if (scroll < wave4)
			{
				gameOver(zigzagEnemyBullet, player1, bgm, suctionSound, succeedSuctionSound, backEnemy, player2, playerDeathSound, selectscene, shootingEnemy, shootingEnemyBullet, straightEnemy, zigzagEnemy, raidEnemy, skullEffect, damage, invincibleFlag);
			}

			break;

		case PAUSE:
			pauseScene(startPauseFlag, BrinkCounter, pauseScreenHandle, FontSize100, FontSize50, bgm, startVideoCount, finishPauseFlag, startPauseSound, initialWIDTH, HEIGHT, selectscene, input, warningSound);

			break;

		case OVER:
			gameOverScene(overSoundFlag, overSound, BrinkCounter, initialWIDTH, HEIGHT, FontSize50, FontSize100, score, scoreMagnificatoin,  startVideoCount, FontSize300, selectscene);

			break;
		}

		//���t���b�V�����[�g�΍�
		int term;
		static int t = 0;
		term = GetNowCount() - t;
		if (16 - term > 0)
			Sleep(16 - term);
		t = GetNowCount();

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}