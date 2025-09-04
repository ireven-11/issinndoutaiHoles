#include"Dxlib.h"
#include"player.h"
#include"shot.h"
#include"block.h"

//プレイヤー初期化
void InitializePlayer(Player& player1,Player& player2)
{
	//プレイヤーの画像読み込み
	player1.normalgraph = LoadGraph("img/siro.png");
	player2.normalgraph = LoadGraph("img/kuro.png");
	player1.actiongraph = LoadGraph("img/siro_hakidasi.png");
	player2.actiongraph = LoadGraph("img/kuro_suikomi.png");

	//プレイヤーの初期値
	player1.x = 300;
	player1.y = 300;
	player2.x = 100;
	player2.y = 300;

	//存在フラグをtureにする
	player1.isInScreenFlag = true;
	player2.isInScreenFlag = true;
}

//プレイヤールーチン
void UpdatePlayer(Player& player1, Player& player2, DINPUT_JOYSTATE input, Bullet zigzagEnemyBullet[], int& scoreMagnificatoin, int suctionSound, int succeedSuctionSound, int& remainingBullet, Bullet shootingEnemyBullet[], bool blockFlag[], int blockX1[], int blockX2[], int blockY1[], int blockY2[],int& scroll,int wave4, bool& suctionSucceedEffectFlag)
{
	//コントローラーの入力状態を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	//クリアするまで
	if (scroll <= wave4)
	{
		//キャラが画面外に出たときコントローラーのスティック入力を無効にする(多少バグ？あり。余裕があれば修正)
	    //白プレイヤーの入力無効
		/*if (player1.x < 0)
		{
			input.Z = 0;
		}
		else if (player1.y < 0)
		{
			input.Rz = 0;
		}
		else if (player1.x + 176 > 1925)
		{
			input.Z = 0;
		}
		else if (player1.y + 185 > 1000)
		{
			input.Rz = 0;;
		}*/
		if (player1.x < 0)
		{
			input.Rx = 0;
		}
		else if (player1.y < 0)
		{
			input.Ry = 0;
		}
		else if (player1.x + 176 > 1925)
		{
			input.Rx = 0;
		}
		else if (player1.y + 185 > 1000)
		{
			input.Ry = 0;;
		}
		//黒プレイヤーの入力無効
		if (player2.x <= 0)
		{
			input.X = 0;
		}
		else if (player2.y <= 0)
		{
			input.Y = 0;
		}
		else if (player2.x + 183 > 1925)
		{
			input.X = 0;
		}
		else if (player2.y + 190 > 1000)
		{
			input.Y = 0;
		}

		//でかいブロックが白プレイヤーにめり込んでいるとき
		//if (blockX1[10] < player1.x + 176 && player1.x + 176 < blockX2[10] && blockFlag[10])
		//{
		//	//入力を無効にする
		//	input.Z = 0;
		//}
		if (blockX1[10] < player1.x + 176 && player1.x + 176 < blockX2[10] && blockFlag[10])
		{
			//入力を無効にする
			input.Rx = 0;
		}
		//でかいブロックが黒プレイヤーにめり込んでいるとき
		if (blockX1[10] < player2.x + 176 && player2.x + 176 < blockX2[10] && blockFlag[10])
		{
			//入力を無効にする
			input.X = 0;
		}

		// 右スティックを倒していたら白プレイヤーを移動させる
		/*if (input.Rz < 0)
		{
			player1.y -= player1.speed;
		}
		if (input.Rz > 0)
		{
			player1.y += player1.speed;
		}
		if (input.Z < 0)
		{
			player1.x -= player1.speed;
		}
		if (input.Z > 0)
		{
			player1.x += player1.speed;
		}*/
		if (input.Ry < 0)
		{
			player1.y -= player1.speed;
		}
		if (input.Ry > 0)
		{
			player1.y += player1.speed;
		}
		if (input.Rx < 0)
		{
			player1.x -= player1.speed;
		}
		if (input.Rx > 0)
		{
			player1.x += player1.speed;
		}

		//左スティックを倒したら黒プレイヤーを移動させる
		if (input.Y < 0)
		{
			player2.y -= player2.speed + 3;
		}
		if (input.Y > 0)
		{
			player2.y += player2.speed + 3;
		}
		if (input.X < 0)
		{
			player2.x -= player2.speed + 3;
		}
		if (input.X > 0)
		{
			player2.x += player2.speed + 3;
		}

		//白プレイヤー押し戻し処理
		if (player1.x < 0)
		{
			player1.x += player1.speed;
		}
		else if (player1.y < 0)
		{
			player1.y += player1.speed;
		}
		else if (player1.x + 176 > 1925)
		{
			player1.x -= player1.speed;
		}
		else if (player1.y + 185 > 1000)
		{
			player1.y -= player1.speed;
		}
		//黒プレイヤー押し戻し処理
		if (player2.x <= 0)
		{
			player2.x += player2.speed + 3;
		}
		else if (player2.y <= 0)
		{
			player2.y += player2.speed + 3;
		}
		else if (player2.x + 183 > 1925)
		{
			player2.x -= player2.speed + 3;
		}
		else if (player2.y + 190 > 1000)
		{
			player2.y -= player2.speed + 3;
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
					if (player1.x < blockX1[i] && blockX1[i] < player1.x + 176 &&
						player1.y < blockY1[i] && blockY1[i] < player1.y + 185 ||
						player1.x < blockX1[i] && blockX1[i] < player1.x + 176 &&
						player1.y < blockY2[i] && blockY2[i] < player1.y + 185)
					{
						player1.x -= player1.speed;

						//入力を無効にする
						input.Z = 0;
					}
					else if (player1.x < blockX2[i] && blockX2[i] < player1.x + 176 &&
						player1.y < blockY1[i] && blockY1[i] < player1.y + 185 ||
						player1.x < blockX2[i] && blockX2[i] < player1.x + 176 &&
						player1.y < blockY2[i] && blockY2[i] < player1.y + 185)
					{
						player1.x += player1.speed;

						//入力を無効にする
						input.Z = 0;
					}

					//ブロックが黒プレイヤーにめり込んでいるとき
					if (player2.x < blockX1[i] && blockX1[i] < player2.x + 176 &&
						player2.y < blockY1[i] && blockY1[i] < player2.y + 185 ||
						player2.x < blockX1[i] && blockX1[i] < player2.x + 176 &&
						player2.y < blockY2[i] && blockY2[i] < player2.y + 185)
					{
						player2.x -= player2.speed;

						//入力を無効にする
						input.X = 0;
					}
					else if (player2.x < blockX2[i] && blockX2[i] < player2.x + 176 &&
						player2.y < blockY1[i] && blockY1[i] < player2.y + 185 ||
						player2.x < blockX2[i] && blockX2[i] < player2.x + 176 &&
						player2.y < blockY2[i] && blockY2[i] < player2.y + 185)
					{
						player2.x += player2.speed;

						//入力を無効にする
						input.X = 0;
					}
				}
				else
				{
					//ブロックが白プレイヤーにめり込んでいるとき
					if (blockX1[i] < player1.x + 176 && player1.x + 176 < blockX2[i])
					{
						player1.x -= player1.speed;

						//入力を無効にする
						input.Z = 0;
					}
					//ブロックが黒プレイヤーにめり込んでいるとき
					if (blockX1[i] < player2.x + 176 && player2.x + 176 < blockX2[i])
					{
						player2.x -= player2.speed;

						//入力を無効にする
						input.X = 0;
					}
				}
			}
		}

		//LBボタンを押してる間だけ弾を吸う
		if (input.Buttons[4] > 0 || input.Buttons[6] > 0)
		{
			//吸い込み効果音
			PlaySoundMem(suctionSound, DX_PLAYTYPE_LOOP, FALSE);

			//ジグザグ敵弾吸い込み処理
			for (int i = 0; i < zigzagEnemyShotNumber; i++)
			{
				if (zigzagEnemyBullet[i].isInScreenFlag)
				{
					if (player2.x + 125 < zigzagEnemyBullet[i].x1 &&
						zigzagEnemyBullet[i].x1 < player2.x + 251 &&
						player2.y < zigzagEnemyBullet[i].y2 &&
						zigzagEnemyBullet[i].y2 < player2.y + 204 ||
						player2.x + 125 < zigzagEnemyBullet[i].x1 &&
						zigzagEnemyBullet[i].x1 < player2.x + 251 &&
						zigzagEnemyBullet[i].y1 < player2.y + 204 &&
						player2.y < zigzagEnemyBullet[i].y1)
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
					if (player2.x + player2Widht <= shootingEnemyBullet[i].x1 &&
						shootingEnemyBullet[i].x1 <= player2.x + suctionWidht &&
						player2.y <= shootingEnemyBullet[i].y2 &&
						shootingEnemyBullet[i].y2 <= player2.y + suctionHeight ||
						player2.x + player2Widht <= shootingEnemyBullet[i].x1 &&
						shootingEnemyBullet[i].x1 <= player2.x + suctionWidht &&
						shootingEnemyBullet[i].y1 <= player2.y + suctionHeight &&
						player2.y <= shootingEnemyBullet[i].y1)
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
		player1.x += 10;
		player2.x += 10;
	}
	
}

//プレイヤー描画
void DrawPlayer(Player& player1, Player& player2, DINPUT_JOYSTATE input,int suctionEffect[],int& suctionEffectCount,bool& invincibleFlag,int& invincibleTimeCount, bool& suctionSucceedEffectFlag, int& suctionSucceedEffectCount, int suctionSucceedEffect[], int Lstick,int Rstick)
{
	//コントローラーの入力状態を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	if (player1.isInScreenFlag && player2.isInScreenFlag)
	{
		if (input.Buttons[4] > 0 && input.Buttons[5] > 0 || input.Buttons[6] > 0 && input.Buttons[7] > 0)
		{
			//プレイヤーを描画
			if (invincibleFlag && invincibleTimeCount % 2 == 0)//点滅描画
			{
				
			}
			else //通常描画
			{
				DrawExtendGraph(player1.x - 75, player1.y - 25, player1.x + 50, player1.y + 50, Rstick, TRUE);
				DrawGraph(player1.x, player1.y, player1.actiongraph, TRUE);
				DrawExtendGraph(player2.x - 75, player2.y - 25, player2.x + 50, player2.y + 50, Lstick, TRUE);
				DrawGraph(player2.x, player2.y, player2.normalgraph, TRUE);
			}

			//吸い込みカウントが0になったら7に戻す
			if (suctionEffectCount < 0)
			{
				suctionEffectCount = 7;
			}

			//吸い込みエフェクトを描画
			DrawExtendGraph(player2.x + 300, player2.y - 50, player2.x + 50, player2.y + 275, suctionEffect[suctionEffectCount], TRUE);
			suctionEffectCount--;

		}
		else if (input.Buttons[5] > 0 || input.Buttons[7] > 0)
		{
			//プレイヤーを描画
			if (invincibleFlag && invincibleTimeCount % 2 == 0)//点滅描画
			{
				
			}
			else //通常描画
			{
				DrawExtendGraph(player1.x - 75, player1.y - 25, player1.x + 50, player1.y + 50, Rstick, TRUE);
				DrawGraph(player1.x, player1.y, player1.actiongraph, TRUE);
				DrawExtendGraph(player2.x - 75, player2.y - 25, player2.x + 50, player2.y + 50, Lstick, TRUE);
				DrawGraph(player2.x, player2.y, player2.normalgraph, TRUE);
			}
		}
		else if (input.Buttons[4] > 0 || input.Buttons[6] > 0)
		{
			//プレイヤーを描画
			if (invincibleFlag && invincibleTimeCount % 2 == 0)//点滅描画
			{
				
			}
			else //通常描画
			{
				DrawExtendGraph(player1.x - 75, player1.y - 25, player1.x + 50, player1.y + 50, Rstick, TRUE);
				DrawGraph(player1.x, player1.y, player1.normalgraph, TRUE);
				DrawExtendGraph(player2.x - 75, player2.y - 25, player2.x + 50, player2.y + 50, Lstick, TRUE);
				DrawGraph(player2.x, player2.y, player2.normalgraph, TRUE);
			}

			//吸い込みカウントが0になったら8に戻す
			if (suctionEffectCount < 0)
			{
				suctionEffectCount = 7;
			}

			//吸い込みエフェクトを描画
			DrawExtendGraph(player2.x + 300, player2.y - 50, player2.x + 50, player2.y + 275, suctionEffect[suctionEffectCount], TRUE);
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
				DrawExtendGraph(player1.x - 75, player1.y - 25, player1.x + 50, player1.y + 50, Rstick, TRUE);
				DrawGraph(player1.x, player1.y, player1.normalgraph, TRUE);
				DrawExtendGraph(player2.x - 75, player2.y - 25, player2.x + 50, player2.y + 50, Lstick, TRUE);
				DrawGraph(player2.x, player2.y, player2.normalgraph, TRUE);
			}
		}
	}

	//吸い込み成功エフェクトを描画
	if (suctionSucceedEffectFlag)
	{
		if (player1.y < 40)
		{
			DrawExtendGraph(player1.x + 90, player1.y + 140, player1.x + 215, player1.y + 265, suctionSucceedEffect[suctionSucceedEffectCount], TRUE);
		}
		else
		{
			DrawExtendGraph(player1.x + 90, player1.y - 90, player1.x + 215, player1.y + 35, suctionSucceedEffect[suctionSucceedEffectCount], TRUE);
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