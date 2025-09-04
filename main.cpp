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

//コントローラーを使うときはコントローラーの裏の設定をDにする
//コントローラーのボタン入力を読み取る構造体変数
DINPUT_JOYSTATE input;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//----基本設定----

	//画面大きさ変更変数
	int DesktopW, DesktopH;
	int WindowW, WindowH;

	//定数宣言
	const int HEIGHT = 1000;       //画面の高さ
	const int initialWIDTH = 1925; //初期画面の幅
	const int WIDTH = 11000;       //背景1枚の幅
	const int scrollspeed = 4;	   //スクロールスピード
	const int wave1 = 3000;	       //ウェーブ１の終わり
	const int wave2 = 7000;	       //ウェーブ２の終わり
	const int wave3 = 14000;	   //ウェーブ3の終わり
	const int wave4 = 21000;	   //ウェーブ4の終わり
	const int IniBulletNumber = 30;//初級弾数
	const int hyaku = 100;
	const int sannbyaku = 300;

	ChangeWindowMode(TRUE);				   //ウィンドウモードにする
	SetWindowStyleMode(7);				   //最大化ボタンが存在するウインドウモードに変更

	// 画面サイズをデスクトップのサイズと同じにする
	GetDefaultState(&DesktopW, &DesktopH, NULL);
	SetGraphMode(DesktopW, DesktopH, 32);

	// サイズ変更を可能にする
	SetWindowSizeChangeEnableFlag(TRUE, FALSE);

	// ウインドウサイズはゲーム画面と一致させる
	SetWindowSize(WIDTH, HEIGHT);

	// ウインドウの位置は画面中心付近にする
	SetWindowPosition((DesktopW - WIDTH) / 2, (DesktopH - HEIGHT) / 2);

	//ライブラリを初期化
	DxLib_Init();

	// ウインドウサイズ情報の初期化
	GetWindowSize(&WindowW, &WindowH);

	SetMainWindowText("イッシンドウタイホールズ");
	SetDrawScreen(DX_SCREEN_BACK);		   //背景をセットする
	SetGraphMode(initialWIDTH, HEIGHT, 32);//ウィンドウのサイズとカラーモードを決める
	//ライブラリ初期化でエラー起きたら終了
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	//---------------

	//変数宣言
	int	   selectscene;     			                //シーン変化
	Player player1;										//プレイヤー1の構造体変数
	Player player2;										//プレイヤー２の構造体変数
	Enemy  TutorialEnemy;								//チュートリアル敵の構造体変数
	Bullet TutorialBullet;								//チュートリアル弾の構造体変数
	Bullet PlayerBullet[PlayerShotNumber];				//プレイヤーの弾の構造体変数配列（弾は画面に[]内の数字までしかでない）
	bool   countDown;       				            //カウントダウンフラグ
	int	   scroll;				                        //スクロール変数
	Enemy  zigzagEnemy[zigzagEnemyNumber];				//ジグザグ敵の構造体変数 ()は敵の数
	Bullet zigzagEnemyBullet[zigzagEnemyShotNumber];	//ジグザグ敵弾の構造体変数
	int    score;										//スコア
	int    scoreMagnificatoin;							//スコア倍率
	int    FontSize125;                                 //フォントサイズ125
	int    FontSize50;                                  //フォントサイズ50
	int    FontSize100;                                 //フォントサイズ100
	int    FontSize300;                                 //フォントサイズ300
	int    FontSize30;                                  //フォントサイズ30
	int    pauseScreenHandle;							//ポーズ画面用スクリーンバッファ
	bool   startPauseFlag;      				        //ポーズ画面開始フラグ
	bool   finishPauseFlag;     			            //ポーズ画面終了フラグ
	bool   clearSoundFlag;      				        //ゲームクリアサウンドフラグ
	bool   overSoundFlag;       				        //ゲームオーバーサウンドフラグ
	bool   tutorial1and2Flag;							//tutorial1and2フラグ
	int    BrinkCounter;    				            //点滅カウンター
	bool   tutorial3Flag;								//tutorial3フラグ
	bool   tutorial4Flag;								//tutorial4フラグ
	bool   shotFlag;									//ショットフラグ
	int    shotCount;									//ショットカウント
	bool   bgmFlag;										//bgmフラグ
	int    remainingBullet;								//残弾
	Enemy  straightEnemy[straightEnemyNumber];			//真っ直ぐ敵の構造体変数
	Enemy  shootingEnemy[shootingEnemyNumber];			//うちまくる敵の構造体変数
	Bullet shootingEnemyBullet[shootingEnemyShotNumber];//うちまくる敵の弾の構造体変数
	Enemy  backEnemy[backEnemyNumber];					//後ろから敵の構造体変数
	Enemy  raidEnemy[raidEnemyNumber];					//奇襲敵の構造体変数
	int    blockGraph[3];								//ブロックの画像
	int    blockHP[blockNumber];						//ブロックのHP
	int    blockX1[blockNumber];						//ブロックの座標X1
	int    blockX2[blockNumber];						//ブロックの座標X2
	int	   blockY1[blockNumber];						//ブロックの座標Y1
	int    blockY2[blockNumber];						//ブロックの座標Y2
	bool   blockFlag[blockNumber];						//ブロックのフラグ
	int    explosionEffect[11];							//爆発エフェクト画像
	int	   suctionEffect[8];							//吸い込みエフェクト
	int    suctionEffectCount;							//吸い込みカウント
	int    skullEffect[15];								//どくろエフェクト
	int    PrevBbuttonFlag;     			            //Bボタン押したフラグ
	int    HPgraph[5];									//hp画像
	int    damage;										//ダメージ
	int    invincibleTimeCount;							//無敵時間カウント
	bool   invincibleFlag;								//無敵フラグ
	int    startVideoCount = 0;				            //動画が始まるまでのカウント
	int    suctionSucceedEffect[11];					//吸い込み成功エフェクト
	bool   suctionSucceedEffectFlag;        			//吸い込み成功エフェクトフラグ
	int    suctionSucceedEffectCount;					//吸い込み成功エフェクトカウント
	int    backGraph;				                    //プレイ背景
	int    shotSound;			                        //射撃時効果音
	int    startPauseSound;	                            //ポーズ画面開始効果音
	int    finishPauseSound;	                        //ポーズ画面終了効果音
	int    countDownSound;		                        //カウントダウン効果音
	int    suctionSound;	                            //吸い込み効果音
	int    clearSound;			                        //クリア時効果音
	int    overSound;			                        //オーバー時効果音
	int    succeedSuctionSound;                         //吸い込み成功効果音
	int    playerDeathSound;	                        //敵か敵の攻撃に当たった瞬間
	int    hanamaruGraph;			                    //花丸
	int    correctSound;		                        //正解音
	int    bgm;		                                    //bgm
	int    remainingBulletGraph;			            //弾数絵
	int    explosionSound;                              //爆発音読み込み
	int    tutorialBack;				                //チュートリアル背景
	int    rogo;                                        //ロゴ画像を読み込み
	int    Lstick;                                      //Lスティック画像読み込み
	int    Rstick;		                                //Rスティック画像読み込み
	int    DemoMovie;	                                //デモムービー読み込み
	int	   warningGraph[3];								//警告画像
	int    warningSound;								//警告音

	//読み込み+初期化
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
	Lstick				 = LoadGraph("img/Lスティック.png");        
	Rstick				 = LoadGraph("img/Rスティック.png");		
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

	//フォントを使えるようにする
	AddFontResourceEx("font/BugMaruUI.ttc", FR_PRIVATE, NULL);
	FontSize125			 = CreateFontToHandle("BugMaru UI", 125, 10, DX_FONTTYPE_EDGE);
	FontSize50			 = CreateFontToHandle("BugMaru UI", 50, 10, DX_FONTTYPE_EDGE);
	FontSize100			 = CreateFontToHandle("BugMaru UI", 100, 10, DX_FONTTYPE_EDGE);
	FontSize300			 = CreateFontToHandle("BugMaru UI", 300, 10, DX_FONTTYPE_EDGE);
	FontSize30			 = CreateFontToHandle("BugMaru UI", 30, 10, DX_FONTTYPE_EDGE);

	// スクリーンバッファを作成
	pauseScreenHandle = MakeScreen(initialWIDTH, HEIGHT, TRUE);
	if (pauseScreenHandle == -1) 
	{
		DxLib_End();
		return -1;
	}

	//音の大きさを調整
	changeVolume(shotSound, startPauseSound, finishPauseSound, countDownSound, suctionSound, clearSound, overSound, succeedSuctionSound,  playerDeathSound, correctSound, bgm, explosionSound);

	//ゲームループ
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 )
	{
		ClearDrawScreen();

		// ウインドウのクライアント領域を取得する
		GetWindowSize(&WindowW, &WindowH);

		//シーン切り替え
		switch (selectscene)
		{
		case TITLE:
			//ロゴ画像を描画
			DrawExtendGraph(0, 0, initialWIDTH, HEIGHT, rogo, TRUE);

			//点滅カウンターの数値を増やす
			BrinkCounter++;

			//動画のカウントを増やす
			startVideoCount++;

			if (BrinkCounter == 60)
			{
				BrinkCounter = 0;
			}

			//Bボタンで説明画面へ
			if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B || CheckHitKey(KEY_INPUT_RETURN) == 1)
			{
				if (!PrevBbuttonFlag)
				{
					//初期化
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

			//カウントが一定になったら動画を流す
			if (startVideoCount > 400)
			{
				PlayMovieToGraph(DemoMovie);

				DrawGraph(0, 0, DemoMovie, FALSE);

				//Bボタンを押したらタイトルへ戻る
				if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B || startVideoCount > 3000)
				{
					startVideoCount = 0;
					PauseMovieToGraph(DemoMovie);
					SeekMovieToGraph(DemoMovie, 0);
				}

				PrevBbuttonFlag = true;
			}

			//Uiを描画
			DrawUI(scroll, wave4, selectscene, FontSize50, score, scoreMagnificatoin, player1, remainingBulletGraph, remainingBullet, HPgraph, damage, tutorial1and2Flag, initialWIDTH, HEIGHT, tutorial4Flag, FontSize100, BrinkCounter, tutorial3Flag, startVideoCount, warningGraph, warningSound);
			
			break;

		case EXPLANE:
			//コントローラーの入力状態を取得
			GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

			//背景描画
			DrawExtendGraph(0, 0, initialWIDTH, HEIGHT, backGraph,TRUE);

			//キャラの画像を描画
			DrawPlayer(player1, player2, input,suctionEffect, suctionEffectCount, invincibleFlag, invincibleTimeCount, suctionSucceedEffectFlag, suctionSucceedEffectCount, suctionSucceedEffect, Lstick, Rstick);

			//チュートリアル敵を描画
			DrawTutorialEnemy(TutorialEnemy);

			//Uiを描画
			DrawUI(scroll, wave4, selectscene, FontSize50, score, scoreMagnificatoin, player1, remainingBulletGraph, remainingBullet, HPgraph, damage, tutorial1and2Flag, initialWIDTH, HEIGHT, tutorial4Flag, FontSize100, BrinkCounter, tutorial3Flag, startVideoCount, warningGraph, warningSound);

			//点滅カウンターの数値を増やす
			BrinkCounter++;

			if (BrinkCounter == 60)
			{
				BrinkCounter = 0;
			}
			
			//プレイヤールーチン
			UpdatePlayer(player1, player2, input, zigzagEnemyBullet, scoreMagnificatoin, suctionSound, succeedSuctionSound, remainingBullet, shootingEnemyBullet, blockFlag, blockX1, blockX2, blockY1, blockY2, scroll, wave4, suctionSucceedEffectFlag);

			//プレイヤーキャラ両方が右側にいったらtutorial1and2フラグをfalseにして演出を加える
			if (player1.x > initialWIDTH / 2 && player2.x > initialWIDTH / 2)
			{
				if (tutorial1and2Flag)
				{
					DrawExtendGraph(initialWIDTH / 3, 100, initialWIDTH / 3 + 500, 600, hanamaruGraph, TRUE);
					PlaySoundMem(correctSound, DX_PLAYTYPE_BACK);
					WaitTimer(500);
				}
				tutorial1and2Flag = false;

				//弾がなくなったら
				if (remainingBullet == 0)
				{
					remainingBullet += 5;
				}
			}

			//チュートリアルエネミールーチン
			UpdateTutorialEnemy(TutorialEnemy);

			//プレイヤー弾ルーチン
			UpdatePlayerBullet(PlayerBullet, PlayerShotNumber, player1, input, shotSound, remainingBullet);

			//プレイヤーが弾をうった時にショットカウントを増やす
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

			//プレイヤー弾の描画
			DrawPlayerBullet(PlayerBullet, PlayerShotNumber);

			//ショットカウントが一定になったら演出を入れる
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
				//チュートリアル敵弾ルーチン
				UpdateTutorialBullet(TutorialBullet, TutorialEnemy);

				//チュートリアル敵弾描画
				DrawTutorialBullet(TutorialBullet);

				if (input.Buttons[4] > 0 || input.Buttons[6] > 0)
				{
					//たまを吸い込んだ時に演出を加える
					if (player2.x + 125 < TutorialBullet.x1 &&	//xmin当たり判定
						TutorialBullet.x1 < player2.x + 251 &&	//xmax当たり判定
						player2.y < TutorialBullet.y2 &&		//ymin当たり判定
						TutorialBullet.y2 < player2.y + 204		//ymax当たり判定
						|| player2.x + 125 < TutorialBullet.x1 &&
						TutorialBullet.x1 < player2.x + 251 &&
						TutorialBullet.y1 < player2.y + 204 &&
						player2.y < TutorialBullet.y1)
					{
						//吸い込み成功効果音
						PlaySoundMem(succeedSuctionSound, DX_PLAYTYPE_BACK, TRUE);

						//弾を消す
						TutorialBullet.isInScreenFlag = false;

						//残弾数を増やす
						remainingBullet += healBullet;

						//吸い込み成功エフェクトフラグをtrueにする
						suctionSucceedEffectFlag = true;

						//弾の上限を設定
						if (remainingBullet > 80)
						{
							remainingBullet = 80;
						}

						//演出を加える
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

			//プレイヤー弾のフラグ管理（当たり判定)
			hitPlayerBullet(PlayerBullet, PlayerShotNumber, player2, zigzagEnemy, score, straightEnemy, shootingEnemy, backEnemy, raidEnemy, blockHP, blockFlag, blockX1, blockX2, blockY1, blockY2, explosionSound);

			//スタートボタンでプレイ画面へ
			if (input.Buttons[11] > 0 || CheckHitKey(KEY_INPUT_SPACE) == 1)
			{
				selectscene = PLAY;

				//カウントダウン
				if (countDown)
				{
					StopSoundMem(suctionSound); // カウントダウン中は吸い込み効果音を止める
					StopSoundMem(succeedSuctionSound); //カウントダウン中は吸い込み成功効果音を止める
					PlaySoundMem(countDownSound, DX_PLAYTYPE_BACK, TRUE); //カウントダウン音
					DrawBox(0, 0, initialWIDTH, HEIGHT, GetColor(0, 0, 0), TRUE); //前画面を隠す
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
					remainingBullet = IniBulletNumber; //残弾数を戻す
					//プレイヤーを初期座標に戻す
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
			//ポーズ画面終了効果音
			if (finishPauseFlag)
			{
				PlaySoundMem(finishPauseSound, DX_PLAYTYPE_BACK, TRUE);
				finishPauseFlag = false;
			}

			//点滅カウンターの数値を増やす
			BrinkCounter++;

			if (BrinkCounter == 60)
			{
				BrinkCounter = 0;
			}

			//スクロールさせる
			scroll += scrollspeed;

			//無敵フラグがtureのときに無敵時間を計算
			if (invincibleFlag)
			{
				invincibleTimeCount++;

				//無敵時間が一定時間たったら無敵フラグをtrueにする
				if (invincibleTimeCount > 125)
				{
					invincibleFlag = false;
					invincibleTimeCount = 0;
				}
			}

			//クリア画面
			clearScene(player1, initialWIDTH, player2, BrinkCounter, shotSound, HEIGHT, FontSize300, FontSize30, clearSoundFlag, score,  FontSize100, scoreMagnificatoin, damage, startVideoCount, selectscene, suctionSound, bgm, clearSound, FontSize50);

			//bgmフラグがtrueのときだけbgmをながす
			if (bgmFlag)
			{
				PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
				bgmFlag = false;
			}

			//背景描画
			if (scroll < wave4)
			{
				DrawExtendGraph(0 - scroll, 0, WIDTH - scroll, HEIGHT, backGraph, TRUE);
				DrawExtendGraph(10000 - scroll, 0, 10000 + WIDTH - scroll, HEIGHT, backGraph, TRUE);
			}

			//ブロックルーチン
			UpdateBlock(blockX1, blockX2, blockY1, blockY2, scroll, wave3);

			//ブロックを描画
			DrawBlock(blockGraph, blockHP, blockFlag, blockX1, blockX2, blockY1, blockY2, scroll);

			//プレイヤールーチン
			UpdatePlayer(player1, player2, input, zigzagEnemyBullet, scoreMagnificatoin, suctionSound, succeedSuctionSound, remainingBullet, shootingEnemyBullet, blockFlag, blockX1, blockX2, blockY1, blockY2, scroll, wave4, suctionSucceedEffectFlag);

			//プレイヤーの画像を描画
			DrawPlayer(player1, player2, input, suctionEffect, suctionEffectCount, invincibleFlag, invincibleTimeCount, suctionSucceedEffectFlag, suctionSucceedEffectCount, suctionSucceedEffect, Lstick, Rstick);
			
			//プレイヤー弾ルーチン
			UpdatePlayerBullet(PlayerBullet, PlayerShotNumber, player1, input, shotSound, remainingBullet);

			//スクロールが一定に達すると敵が出現
			if (scroll > wave1)
			{
				//ジグザグエネミールーチン
				UpdateZigzagEnemy(zigzagEnemy);

				//ジグザグ敵の描画
				DrawZigzagEnemy(zigzagEnemy, explosionEffect);
			}

			if (scroll < wave1)
			{
				//真っ直ぐ敵ルーチン
				UpdateStraightEnemy(straightEnemy);

				//真っ直ぐ敵の描画
				DrawStraightEnemy(straightEnemy, explosionEffect);
			}

			//うちまくり敵ルーチン
			UpdateShootingEnemy(shootingEnemy, scroll);

			//うちまくり敵描画
			DrawShootingEnemy(shootingEnemy, explosionEffect);

			//後ろから敵ルーチン
			UpdateBackEnemy(backEnemy, wave1, scroll, player2, wave3, wave4);

			//後ろから敵描画
			DrawBackEnemy(backEnemy, explosionEffect);

			//奇襲敵ルーチン
			UpdateRaidEnemy(raidEnemy, scroll, wave2);

			//奇襲敵描画
			DrawRaidEnemy(raidEnemy,explosionEffect);

			//プレイヤー弾のフラグ管理（当たり判定)
			hitPlayerBullet(PlayerBullet, PlayerShotNumber, player2, zigzagEnemy, score, straightEnemy, shootingEnemy,backEnemy, raidEnemy, blockHP, blockFlag, blockX1, blockX2, blockY1, blockY2, explosionSound);

			//プレイヤー弾描画
			DrawPlayerBullet(PlayerBullet, PlayerShotNumber);

			//弾を発射出来る敵がいるか探す
			for (int i = 0; i < zigzagEnemyNumber; i++)
			{
				if (zigzagEnemy[i].x1 == 1300 || zigzagEnemy[i].x1 == 1000 || zigzagEnemy[i].x1 == 700)
				{
					//弾が空いているか
					for (int j = 0; j < zigzagEnemyShotNumber; j++)
					{
						//存在しているか
						if (!zigzagEnemyBullet[j].isInScreenFlag)
						{
							//ジグザグ敵弾発射
							InitializeZigzagEnemyBullet(zigzagEnemyBullet[j], zigzagEnemy[i]);
							break;
						}
					}
				}
			}

			for (int i = 0; i < zigzagEnemyShotNumber; i++)
			{
				//ジグザグ敵弾ルーチン
				UpdateZigzagEnemyBullet(zigzagEnemyBullet[i]);
				//ジグザグ敵弾描画
				DrawZigzagEnemyBullet(zigzagEnemyBullet[i]);
			}

			//弾を発射出来る敵がいるか探す
			for (int i = 0; i < shootingEnemyNumber; i++)
			{
				//敵が画面内にいるか＆＆白プレイヤーが敵より左にいるか
				if (shootingEnemy[i].x1 < initialWIDTH && player1.x - shootingEnemy[i].x1 < 0)
				{
					//最初の4体
					if (i <= 4)
					{
						//一定の座標にいるか
						if (shootingEnemy[i].y1 == 0 || shootingEnemy[i].y1 == 1000 || shootingEnemy[i].y1 == 250 || shootingEnemy[i].y1 == 750 || shootingEnemy[i].y1 == 500)
						{
							//弾が空いているか
							for (int j = 0; j < shootingEnemyShotNumber; j++)
							{
								//存在しているか
								if (!shootingEnemyBullet[j].isInScreenFlag)
								{
									//うちまくる敵弾発射
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
							//弾が空いているか
							for (int j = 0; j < shootingEnemyShotNumber; j++)
							{
								//存在しているか
								if (!shootingEnemyBullet[j].isInScreenFlag)
								{
									//うちまくる敵弾発射
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
				//うちまくる敵弾ルーチン
				UpdateShootingEnemyBullet(shootingEnemyBullet[i]);
				for (int j = 0; j < shootingEnemyNumber; j++)
				{
					//うちまくる敵弾描画
					DrawShootingEnemyBullet(shootingEnemyBullet[i]);
				}

				//クリアしたらフラグをfalseにする
				if (scroll > wave4)
				{
					shootingEnemyBullet[i].isInScreenFlag = false;
				}
			}

			//Uiを描画
			DrawUI(scroll, wave4, selectscene, FontSize50, score, scoreMagnificatoin, player1, remainingBulletGraph, remainingBullet, HPgraph, damage, tutorial1and2Flag, initialWIDTH, HEIGHT, tutorial4Flag, FontSize100, BrinkCounter, tutorial3Flag, startVideoCount, warningGraph, warningSound);

			//Yボタンでポーズ画面へ移行(内部的にはX)
			if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_X)
			{
				// ゲーム画面をバッファに保存
				SetDrawScreen(pauseScreenHandle); // バッファに切り替え
				ClearDrawScreen(); // バッファをクリア
				// 現在のゲーム画面を描画(薄く映る）
				//背景描画
				if (scroll < wave4)
				{
					DrawExtendGraph(0 - scroll, 0, WIDTH - scroll, HEIGHT, backGraph, TRUE);
					DrawExtendGraph(10000 - scroll, 0, 10000 + WIDTH - scroll, HEIGHT, backGraph, TRUE);
				}
				//ブロックを描画
				DrawBlock(blockGraph, blockHP, blockFlag, blockX1, blockX2, blockY1, blockY2, scroll);
				//プレイヤーの画像を描画
				DrawPlayer(player1, player2, input, suctionEffect, suctionEffectCount, invincibleFlag, invincibleTimeCount,suctionSucceedEffectFlag, suctionSucceedEffectCount, suctionSucceedEffect, Lstick, Rstick);
				//ジグザグ敵の描画
				if (scroll > wave1)
				{
					DrawZigzagEnemy(zigzagEnemy, explosionEffect);
				}
				if (scroll < wave1)
				{
					//真っ直ぐ敵の描画
					DrawStraightEnemy(straightEnemy, explosionEffect);
				}
				//うちまくり敵描画
				DrawShootingEnemy(shootingEnemy, explosionEffect);
				//後ろから敵描画
				DrawBackEnemy(backEnemy, explosionEffect);
				//奇襲敵描画
				DrawRaidEnemy(raidEnemy, explosionEffect);
				//プレイヤー弾描画
				DrawPlayerBullet(PlayerBullet, PlayerShotNumber);
				for (int i = 0; i < zigzagEnemyShotNumber; i++)
				{
					//ジグザグ敵弾描画
					DrawZigzagEnemyBullet(zigzagEnemyBullet[i]);
				}
				for (int i = 0; i < shootingEnemyShotNumber; i++)
				{
					for (int j = 0; j < shootingEnemyNumber; j++)
					{
						//うちまくる敵弾描画
						DrawShootingEnemyBullet(shootingEnemyBullet[i]);
					}
				}
				DrawUI(scroll, wave4, selectscene, FontSize50, score, scoreMagnificatoin, player1, remainingBulletGraph, remainingBullet, HPgraph, damage, tutorial1and2Flag, initialWIDTH, HEIGHT, tutorial4Flag, FontSize100, BrinkCounter, tutorial3Flag, startVideoCount, warningGraph, warningSound);

				SetDrawScreen(DX_SCREEN_FRONT); // 描画先を戻す

				//ポーズ画面開始フラグをtureにする
				startPauseFlag = true;

				//ポーズ画面へ
				selectscene = PAUSE;
			}

			//ゲームオーバーの判定
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

		//リフレッシュレート対策
		int term;
		static int t = 0;
		term = GetNowCount() - t;
		if (16 - term > 0)
			Sleep(16 - term);
		t = GetNowCount();

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}