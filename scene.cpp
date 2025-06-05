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

		//ポーズ画面開始効果音
		PlaySoundMem(startPauseSound, DX_PLAYTYPE_BACK, TRUE);
		startPauseFlag = false;
	}

	//点滅カウンターの数値を増やす
	BrinkCounter++;

	if (BrinkCounter == 60)
	{
		BrinkCounter = 0;
	}

	//コントローラーの入力状態を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // 半透明モード
	DrawGraph(0, 0, pauseScreenHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 通常描画に戻す

	// ポーズ文字表示
	if (BrinkCounter < 40)
	{
		DrawStringToHandle(initialWIDTH / 2 - 150, HEIGHT / 3, "PAUSED", GetColor(255, 255, 255), FontSize100);
	}

	//Bボタンでタイトルに戻る
	/*DrawStringToHandle(initialWIDTH / 2 - 125, HEIGHT / 2 + 50, "Bでタイトルへ", GetColor(255, 255, 255), FontSize50);*/
	DrawStringToHandle(initialWIDTH / 2 - 125, HEIGHT / 2 + 50, "Aでタイトルへ", GetColor(255, 255, 255), FontSize50);
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B || CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		StopSoundMem(bgm); //bgmを止める
		startVideoCount = 0;
		PlayMovie("video/finishuzumaki0.7.mp4", 1, DX_MOVIEPLAYTYPE_NORMAL);
		selectscene = TITLE;
	}

	//Xボタンでプレイ画面へ戻る
	/*DrawStringToHandle(initialWIDTH / 2 - 150, HEIGHT / 2, "Xでプレイ画面へ", GetColor(255, 255, 255), FontSize50);*/
	DrawStringToHandle(initialWIDTH / 2 - 150, HEIGHT / 2, "Yでプレイ画面へ", GetColor(255, 255, 255), FontSize50);
	if (input.Buttons[2] > 0)
	{
		//ポーズ画面終了フラグをtrueにする
		finishPauseFlag = true;

		selectscene = PLAY;
	}
}

void gameOverScene(bool& overSoundFlag,int overSound,int& BrinkCounter,int initialWIDTH,int HEIGHT,int FontSize50,int FontSize100,int& score,int& scoreMagnificatoin,int& startVideoCount,int FontSize300,int&selectscene)
{
	//ゲームオーバー時効果音
	if (overSoundFlag)
	{
		PlaySoundMem(overSound, DX_PLAYTYPE_BACK, TRUE);
		overSoundFlag = false;
	}

	//点滅カウンターの数値を増やす
	BrinkCounter++;

	if (BrinkCounter == 60)
	{
		BrinkCounter = 0;
	}

	//ゲームオーバー
	DrawStringToHandle(initialWIDTH / 7, HEIGHT / 3, "GAME OVER", GetColor(255, 50, 50), FontSize300);

	//画面遷移の指示を描画
	if (BrinkCounter < 40)
	{
		/*DrawStringToHandle(initialWIDTH / 3 + 100, HEIGHT - 300, "Bボタンでタイトルへ戻る", GetColor(255, 50, 50), FontSize50);*/
		DrawStringToHandle(initialWIDTH / 3 + 100, HEIGHT - 300, "Aボタンでタイトルへ戻る", GetColor(255, 50, 50), FontSize50);
	}

	//スコア表示
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

	//Bボタンでタイトルに戻る
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
		//点滅カウンターの数値を増やす
		BrinkCounter++;

		if (BrinkCounter == 60)
		{
			BrinkCounter = 0;
		}

		StopSoundMem(shotSound);
		StopSoundMem(suctionSound);

		//ゲームクリア表示
		DrawStringToHandle(initialWIDTH / 10 - 50, HEIGHT / 3, "GAME CLEAR!!", GetColor(255, 255, 50), FontSize300);

		//クリアボーナス表示
		DrawStringToHandle(initialWIDTH / 3 + 150, HEIGHT - 350, "クリアボーナス +10000", GetColor(255, 255, 50), FontSize30);

		//HPボーナス表示
		DrawFormatStringToHandle(initialWIDTH / 3 + 200, HEIGHT - 300, GetColor(255, 255, 50), FontSize30, "HPボーナス ×%d", damage * -1 + 4);

		//クリア時効果音を再生
		if (clearSoundFlag)
		{
			StopSoundMem(bgm); //bgmを止める

			PlaySoundMem(clearSound, DX_PLAYTYPE_BACK, TRUE);
			clearSoundFlag = false;
		}

		//総合スコア表示
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

		//画面遷移の指示を描画
		if (BrinkCounter < 40)
		{
			/*DrawStringToHandle(initialWIDTH / 3 + 50, HEIGHT - 200, "Bボタンでタイトルへ戻る", GetColor(255, 50, 50), FontSize50);*/
			DrawStringToHandle(initialWIDTH / 3 + 50, HEIGHT - 200, "Aボタンでタイトルへ戻る", GetColor(255, 50, 50), FontSize50);
		}

		//Bボタンでタイトルに戻る
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
//	//Yボタンでポーズ画面へ移行(内部的にはX)
//	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_X)
//	{
//		// ゲーム画面をバッファに保存
//		SetDrawScreen(pauseScreenHandle); // バッファに切り替え
//		ClearDrawScreen(); // バッファをクリア
//		// 現在のゲーム画面を描画(薄く映る）
//		//背景描画
//		if (scroll < wave4)
//		{
//			DrawExtendGraph(0 - scroll, 0, WIDTH - scroll, HEIGHT, backGraph, TRUE);
//			DrawExtendGraph(10000 - scroll, 0, 10000 + WIDTH - scroll, HEIGHT, backGraph, TRUE);
//		}
//		//ブロックを描画
//		DrawBlock(blockGraph, blockHP, blockFlag, blockX1, blockX2, blockY1, blockY2, scroll);
//		//プレイヤーの画像を描画
//		DrawPlayer(player1, player2, input, suctionEffect, suctionEffectCount, invincibleFlag, invincibleTimeCount, suctionSucceedEffectFlag, suctionSucceedEffectCount, suctionSucceedEffect, Lstick, Rstick);
//		//ジグザグ敵の描画
//		if (scroll > wave1)
//		{
//			DrawZigzagEnemy(zigzagEnemy, explosionEffect);
//		}
//		if (scroll < wave1)
//		{
//			//真っ直ぐ敵の描画
//			DrawStraightEnemy(straightEnemy, explosionEffect);
//		}
//		//うちまくり敵描画
//		DrawShootingEnemy(shootingEnemy, explosionEffect);
//		//後ろから敵描画
//		DrawBackEnemy(backEnemy, explosionEffect);
//		//奇襲敵描画
//		DrawRaidEnemy(raidEnemy, explosionEffect);
//		//プレイヤー弾描画
//		DrawPlayerBullet(PlayerBullet, PlayerShotNumber);
//		for (int i = 0; i < zigzagEnemyShotNumber; i++)
//		{
//			//ジグザグ敵弾描画
//			DrawZigzagEnemyBullet(zigzagEnemyBullet[i]);
//		}
//		for (int i = 0; i < shootingEnemyShotNumber; i++)
//		{
//			for (int j = 0; j < shootingEnemyNumber; j++)
//			{
//				//うちまくる敵弾描画
//				DrawShootingEnemyBullet(shootingEnemyBullet[i]);
//			}
//		}
//		DrawUI(scroll, wave4, selectscene, FontSize50, score, scoreMagnificatoin, player1, remainingBulletGraph, remainingBullet, HPgraph, damage, tutorial1and2Flag, initialWIDTH, HEIGHT, tutorial4Flag, FontSize100, BrinkCounter, tutorial3Flag);
//
//		SetDrawScreen(DX_SCREEN_FRONT); // 描画先を戻す
//
//		//ポーズ画面開始フラグをtureにする
//		startPauseFlag = true;
//
//		//ポーズ画面へ
//		selectscene = PAUSE;
//	}
//}