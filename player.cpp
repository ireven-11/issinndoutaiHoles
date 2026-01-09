#include"Dxlib.h"
#include"player.h"
#include"shot.h"
#include"block.h"

static XINPUT_STATE inputX;

//プレイヤー初期化
void InitializePlayer(Player& whitePlayer,Player& blackPlayer)
{
	//プレイヤーの画像読み込み
	whitePlayer.normalgraph = LoadGraph("img/siro.png");
	blackPlayer.normalgraph = LoadGraph("img/kuro.png");
	whitePlayer.actiongraph = LoadGraph("img/siro_hakidasi.png");
	blackPlayer.actiongraph = LoadGraph("img/kuro_suikomi.png");

	//プレイヤーの初期値
	whitePlayer.x = 300;
	whitePlayer.y = 300;
	blackPlayer.x = 100;
	blackPlayer.y = 300;

	//存在フラグをtureにする
	whitePlayer.isInScreenFlag = true;
	blackPlayer.isInScreenFlag = true;
}

//プレイヤールーチン
void UpdatePlayer(Player& whitePlayer, Player& blackPlayer, DINPUT_JOYSTATE input, Bullet zigzagEnemyBullet[], int& scoreMagnificatoin, int suctionSound, int succeedSuctionSound, int& remainingBullet, Bullet shootingEnemyBullet[], bool blockFlag[], int blockX1[], int blockX2[], int blockY1[], int blockY2[],int& scroll,int wave4, bool& suctionSucceedEffectFlag, bool isProcon)
{
	//インプット
	if (GetJoypadType(DX_INPUT_PAD1) == DX_PADTYPE_XBOX_360
		|| GetJoypadType(DX_INPUT_PAD1) == DX_PADTYPE_XBOX_ONE)
	{
		GetJoypadXInputState(DX_INPUT_PAD1, &inputX);
	}

	//クリアするまで
	if (scroll <= wave4)
	{
		//キャラが画面外に出たときコントローラーのスティック入力を無効にする(多少バグ？あり。余裕があれば修正)
	    //白プレイヤーの入力無効
		if (whitePlayer.x < 0)
		{
			inputX.ThumbRX = 0;
		}
		else if (whitePlayer.y < 0)
		{
			inputX.ThumbRY = 0;
		}
		else if (whitePlayer.x + 176 > 1925)
		{
			inputX.ThumbRX = 0;
		}
		else if (whitePlayer.y + 185 > 1000)
		{
			inputX.ThumbRY = 0;
		}
		//黒プレイヤーの入力無効
		if (blackPlayer.x <= 0)
		{
			inputX.ThumbLX = 0;
		}
		else if (blackPlayer.y <= 0)
		{
			inputX.ThumbLY = 0;
		}
		else if (blackPlayer.x + 183 > 1925)
		{
			inputX.ThumbLX = 0;
		}
		else if (blackPlayer.y + 190 > 1000)
		{
			inputX.ThumbLY = 0;
		}

		//でかいブロックが白プレイヤーにめり込んでいるとき
		if (blockX1[10] < whitePlayer.x + 176 && whitePlayer.x + 176 < blockX2[10] && blockFlag[10])
		{
			//入力を無効にする
			inputX.ThumbRX = 0;
		}
		//でかいブロックが黒プレイヤーにめり込んでいるとき
		if (blockX1[10] < blackPlayer.x + 176 && blackPlayer.x + 176 < blockX2[10] && blockFlag[10])
		{
			//入力を無効にする
			inputX.ThumbLY = 0;
		}

		// 右スティックを倒していたら白プレイヤーを移動させる
		if (inputX.ThumbRY > 0)
		{
			whitePlayer.y -= whitePlayer.speed;
		}
		if (inputX.ThumbRY < 0)
		{
			whitePlayer.y += whitePlayer.speed;
		}
		if (inputX.ThumbRX < 0)
		{
			whitePlayer.x -= whitePlayer.speed;
		}
		if (inputX.ThumbRX > 0)
		{
			whitePlayer.x += whitePlayer.speed;
		}

		//左スティックを倒したら黒プレイヤーを移動させる
		if (inputX.ThumbLY > 0)
		{
			blackPlayer.y -= blackPlayer.speed + 3;
		}
		if (inputX.ThumbLY < 0)
		{
			blackPlayer.y += blackPlayer.speed + 3;
		}
		if (inputX.ThumbLX < 0)
		{
			blackPlayer.x -= blackPlayer.speed + 3;
		}
		if (inputX.ThumbLX > 0)
		{
			blackPlayer.x += blackPlayer.speed + 3;
		}

		//白プレイヤー押し戻し処理
		if (whitePlayer.x < 0)
		{
			whitePlayer.x += whitePlayer.speed;
		}
		else if (whitePlayer.y < 0)
		{
			whitePlayer.y += whitePlayer.speed;
		}
		else if (whitePlayer.x + 176 > 1925)
		{
			whitePlayer.x -= whitePlayer.speed;
		}
		else if (whitePlayer.y + 185 > 1000)
		{
			whitePlayer.y -= whitePlayer.speed;
		}
		//黒プレイヤー押し戻し処理
		if (blackPlayer.x <= 0)
		{
			blackPlayer.x += blackPlayer.speed + 3;
		}
		else if (blackPlayer.y <= 0)
		{
			blackPlayer.y += blackPlayer.speed + 3;
		}
		else if (blackPlayer.x + 183 > 1925)
		{
			blackPlayer.x -= blackPlayer.speed + 3;
		}
		else if (blackPlayer.y + 190 > 1000)
		{
			blackPlayer.y -= blackPlayer.speed + 3;
		}

		//ブロックとの押し戻り処理
		for (int i = 0; i < blockNumber; i++)
		{
			//ブロックがあるときだけ
			if (blockFlag[i])
			{
				if (i < 10)
				{
					//ブロックが白プレイヤーにめり込んでいるとき
					if (whitePlayer.x < blockX1[i] && blockX1[i] < whitePlayer.x + 176 &&
						whitePlayer.y < blockY1[i] && blockY1[i] < whitePlayer.y + 185 ||
						whitePlayer.x < blockX1[i] && blockX1[i] < whitePlayer.x + 176 &&
						whitePlayer.y < blockY2[i] && blockY2[i] < whitePlayer.y + 185)
					{
						whitePlayer.x -= whitePlayer.speed;

						//入力を無効にする
						inputX.ThumbRX = 0;
					}
					else if (whitePlayer.x < blockX2[i] && blockX2[i] < whitePlayer.x + 176 &&
						whitePlayer.y < blockY1[i] && blockY1[i] < whitePlayer.y + 185 ||
						whitePlayer.x < blockX2[i] && blockX2[i] < whitePlayer.x + 176 &&
						whitePlayer.y < blockY2[i] && blockY2[i] < whitePlayer.y + 185)
					{
						whitePlayer.x += whitePlayer.speed;

						//入力を無効にする
						inputX.ThumbRX = 0;
					}

					//ブロックが黒プレイヤーにめり込んでいるとき
					if (blackPlayer.x < blockX1[i] && blockX1[i] < blackPlayer.x + 176 &&
						blackPlayer.y < blockY1[i] && blockY1[i] < blackPlayer.y + 185 ||
						blackPlayer.x < blockX1[i] && blockX1[i] < blackPlayer.x + 176 &&
						blackPlayer.y < blockY2[i] && blockY2[i] < blackPlayer.y + 185)
					{
						blackPlayer.x -= blackPlayer.speed;

						//入力を無効にする
						inputX.ThumbLX = 0;
					}
					else if (blackPlayer.x < blockX2[i] && blockX2[i] < blackPlayer.x + 176 &&
						blackPlayer.y < blockY1[i] && blockY1[i] < blackPlayer.y + 185 ||
						blackPlayer.x < blockX2[i] && blockX2[i] < blackPlayer.x + 176 &&
						blackPlayer.y < blockY2[i] && blockY2[i] < blackPlayer.y + 185)
					{
						blackPlayer.x += blackPlayer.speed;

						//入力を無効にする
						inputX.ThumbLX = 0;
					}
				}
				else
				{
					//ブロックが白プレイヤーにめり込んでいるとき
					if (blockX1[i] < whitePlayer.x + 176 && whitePlayer.x + 176 < blockX2[i])
					{
						whitePlayer.x -= whitePlayer.speed;

						//入力を無効にする
						inputX.ThumbRX = 0;
					}
					//ブロックが黒プレイヤーにめり込んでいるとき
					if (blockX1[i] < blackPlayer.x + 176 && blackPlayer.x + 176 < blockX2[i])
					{
						blackPlayer.x -= blackPlayer.speed;

						//入力を無効にする
						inputX.ThumbLX = 0;
					}
				}
			}
		}

		//LBボタンを押してる間だけ弾を吸う
		if (input.Buttons[4] > 0 && isProcon
			|| input.Buttons[6] > 0 && isProcon
			|| inputX.LeftTrigger > 0
			|| inputX.Buttons[XINPUT_BUTTON_LEFT_SHOULDER] > 0)
		{
			//吸い込み効果音
			PlaySoundMem(suctionSound, DX_PLAYTYPE_LOOP, FALSE);

			//ジグザグ敵弾吸い込み処理
			for (int i = 0; i < zigzagEnemyShotNumber; i++)
			{
				if (zigzagEnemyBullet[i].isInScreenFlag)
				{
					if (blackPlayer.x + 125 < zigzagEnemyBullet[i].x1 &&
						zigzagEnemyBullet[i].x1 < blackPlayer.x + 251 &&
						blackPlayer.y < zigzagEnemyBullet[i].y2 &&
						zigzagEnemyBullet[i].y2 < blackPlayer.y + 204 ||
						blackPlayer.x + 125 < zigzagEnemyBullet[i].x1 &&
						zigzagEnemyBullet[i].x1 < blackPlayer.x + 251 &&
						zigzagEnemyBullet[i].y1 < blackPlayer.y + 204 &&
						blackPlayer.y < zigzagEnemyBullet[i].y1)
					{
						//吸い込み成功効果音
						PlaySoundMem(succeedSuctionSound, DX_PLAYTYPE_BACK, TRUE);

						//弾を消す
						zigzagEnemyBullet[i].isInScreenFlag = false;

						//弾回復
						remainingBullet += healBullet;

						//弾の上限を設定
						if (remainingBullet > MaxremainingBullet)
						{
							remainingBullet = MaxremainingBullet;
						}

						//スコア倍率を増やす
						scoreMagnificatoin++;

						//吸い込み成功エフェクトフラグをtrueにする
						suctionSucceedEffectFlag = true;
					}
				}
			}

			//うちまくり敵弾吸い込み処理
			for (int i = 0; i < shootingEnemyShotNumber; i++)
			{
				if (shootingEnemyBullet[i].isInScreenFlag)
				{
					if (blackPlayer.x + blackPlayerWidht <= shootingEnemyBullet[i].x1 &&
						shootingEnemyBullet[i].x1 <= blackPlayer.x + suctionWidht &&
						blackPlayer.y <= shootingEnemyBullet[i].y2 &&
						shootingEnemyBullet[i].y2 <= blackPlayer.y + suctionHeight ||
						blackPlayer.x + blackPlayerWidht <= shootingEnemyBullet[i].x1 &&
						shootingEnemyBullet[i].x1 <= blackPlayer.x + suctionWidht &&
						shootingEnemyBullet[i].y1 <= blackPlayer.y + suctionHeight &&
						blackPlayer.y <= shootingEnemyBullet[i].y1)
					{
						//吸い込み成功効果音
						PlaySoundMem(succeedSuctionSound, DX_PLAYTYPE_BACK, TRUE);

						//弾を消す
						shootingEnemyBullet[i].isInScreenFlag = false;

						//弾回復
						remainingBullet += healBullet;

						//弾の上限を設定
						if (remainingBullet > MaxremainingBullet)
						{
							remainingBullet = MaxremainingBullet;
						}

						//スコア倍率を増やす
						scoreMagnificatoin++;

						//吸い込み成功エフェクトフラグをtrueにする
						suctionSucceedEffectFlag = true;
					}
				}
			}
		}
		//RBボタンを押してないときは吸い込み効果音を止める
		else
		{
			StopSoundMem(suctionSound);
		}
	}
	//クリアしたあと
	else
	{
		whitePlayer.x += 10;
		blackPlayer.x += 10;
	}
	
}

//プレイヤー描画
void DrawPlayer(Player& whitePlayer, Player& blackPlayer, DINPUT_JOYSTATE input,int suctionEffect[],int& suctionEffectCount,bool& invincibleFlag,int& invincibleTimeCount, bool& suctionSucceedEffectFlag, int& suctionSucceedEffectCount, int suctionSucceedEffect[], int Lstick,int Rstick, bool isProcon)
{
	//インプット
	if (GetJoypadType(DX_INPUT_PAD1) == DX_PADTYPE_XBOX_360
		|| GetJoypadType(DX_INPUT_PAD1) == DX_PADTYPE_XBOX_ONE)
	{
		GetJoypadXInputState(DX_INPUT_PAD1, &inputX);
	}
	
	if (whitePlayer.isInScreenFlag && blackPlayer.isInScreenFlag)
	{
		//両キャラのアクション状態の描画
		if (input.Buttons[4] > 0 && input.Buttons[5] > 0 && isProcon
			|| input.Buttons[6] > 0 && input.Buttons[7] > 0 && isProcon
			|| input.Buttons[4] > 0 && input.Buttons[7] > 0 && isProcon
			|| input.Buttons[6] > 0 && input.Buttons[5] > 0 && isProcon
			|| inputX.RightTrigger > 0 && inputX.LeftTrigger > 0
			|| inputX.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] > 0 && inputX.Buttons[XINPUT_BUTTON_LEFT_SHOULDER] > 0
			|| inputX.RightTrigger > 0 && inputX.Buttons[XINPUT_BUTTON_LEFT_SHOULDER] > 0
			|| inputX.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] > 0 && inputX.LeftTrigger > 0)
		{
			//プレイヤーを描画
			if (invincibleFlag && invincibleTimeCount % 2 == 0)//点滅描画
			{
				
			}
			else //通常描画
			{
				DrawExtendGraph(whitePlayer.x - 75, whitePlayer.y - 25, whitePlayer.x + 50, whitePlayer.y + 50, Rstick, TRUE);
				DrawGraph(whitePlayer.x, whitePlayer.y, whitePlayer.actiongraph, TRUE);
				DrawExtendGraph(blackPlayer.x - 75, blackPlayer.y - 25, blackPlayer.x + 50, blackPlayer.y + 50, Lstick, TRUE);
				DrawGraph(blackPlayer.x, blackPlayer.y, blackPlayer.normalgraph, TRUE);
			}

			//吸い込みカウントが0になったら7に戻す
			if (suctionEffectCount < 0)
			{
				suctionEffectCount = 7;
			}

			//吸い込みエフェクトを描画
			DrawExtendGraph(blackPlayer.x + 300, blackPlayer.y - 50, blackPlayer.x + 50, blackPlayer.y + 275, suctionEffect[suctionEffectCount], TRUE);
			suctionEffectCount--;

		}
		else if (input.Buttons[5] > 0 && isProcon
			|| input.Buttons[7] > 0 && isProcon
			|| inputX.RightTrigger > 0
			|| inputX.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] > 0)
		{
			//プレイヤーを描画
			if (invincibleFlag && invincibleTimeCount % 2 == 0)//点滅描画
			{
				
			}
			else //通常描画
			{
				DrawExtendGraph(whitePlayer.x - 75, whitePlayer.y - 25, whitePlayer.x + 50, whitePlayer.y + 50, Rstick, TRUE);
				DrawGraph(whitePlayer.x, whitePlayer.y, whitePlayer.actiongraph, TRUE);
				DrawExtendGraph(blackPlayer.x - 75, blackPlayer.y - 25, blackPlayer.x + 50, blackPlayer.y + 50, Lstick, TRUE);
				DrawGraph(blackPlayer.x, blackPlayer.y, blackPlayer.normalgraph, TRUE);
			}
		}
		else if (input.Buttons[4] > 0 && isProcon
			|| input.Buttons[6] > 0 && isProcon
			|| inputX.LeftTrigger > 0
			|| inputX.Buttons[XINPUT_BUTTON_LEFT_SHOULDER] > 0)
		{
			//プレイヤーを描画
			if (invincibleFlag && invincibleTimeCount % 2 == 0)//点滅描画
			{
				
			}
			else //通常描画
			{
				DrawExtendGraph(whitePlayer.x - 75, whitePlayer.y - 25, whitePlayer.x + 50, whitePlayer.y + 50, Rstick, TRUE);
				DrawGraph(whitePlayer.x, whitePlayer.y, whitePlayer.normalgraph, TRUE);
				DrawExtendGraph(blackPlayer.x - 75, blackPlayer.y - 25, blackPlayer.x + 50, blackPlayer.y + 50, Lstick, TRUE);
				DrawGraph(blackPlayer.x, blackPlayer.y, blackPlayer.normalgraph, TRUE);
			}

			//吸い込みカウントが0になったら8に戻す
			if (suctionEffectCount < 0)
			{
				suctionEffectCount = 7;
			}

			//吸い込みエフェクトを描画
			DrawExtendGraph(blackPlayer.x + 300, blackPlayer.y - 50, blackPlayer.x + 50, blackPlayer.y + 275, suctionEffect[suctionEffectCount], TRUE);
			suctionEffectCount--;
		}
		else
		{
			//プレイヤーを描画
			if (invincibleFlag && invincibleTimeCount % 2 == 0)//点滅描画
			{

			}
			else //通常描画
			{
				DrawExtendGraph(whitePlayer.x - 75, whitePlayer.y - 25, whitePlayer.x + 50, whitePlayer.y + 50, Rstick, TRUE);
				DrawGraph(whitePlayer.x, whitePlayer.y, whitePlayer.normalgraph, TRUE);
				DrawExtendGraph(blackPlayer.x - 75, blackPlayer.y - 25, blackPlayer.x + 50, blackPlayer.y + 50, Lstick, TRUE);
				DrawGraph(blackPlayer.x, blackPlayer.y, blackPlayer.normalgraph, TRUE);
			}
		}
	}

	//吸い込み成功エフェクトを描画
	if (suctionSucceedEffectFlag)
	{
		if (whitePlayer.y < 40)
		{
			DrawExtendGraph(whitePlayer.x + 90, whitePlayer.y + 140, whitePlayer.x + 215, whitePlayer.y + 265, suctionSucceedEffect[suctionSucceedEffectCount], TRUE);
		}
		else
		{
			DrawExtendGraph(whitePlayer.x + 90, whitePlayer.y - 90, whitePlayer.x + 215, whitePlayer.y + 35, suctionSucceedEffect[suctionSucceedEffectCount], TRUE);
		}
		
		//吸い込み成功エフェクトカウントを増やす
		suctionSucceedEffectCount++;

		if (suctionSucceedEffectCount == 10)
		{
			suctionSucceedEffectCount = 0;
			suctionSucceedEffectFlag = false;
		}
	}
}