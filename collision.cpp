#include"DxLib.h"
#include"player.h"
#include"enemy.h"
#include"shot.h"
#include"collision.h"
#include"block.h"
#include"scene.h"

//プレイヤーの弾の当たり判定関数
void hitPlayerBullet(Bullet PlayerBullet[], int PlayerShotNumber, Player& player2, Enemy zigzagEnemy[], int& score, Enemy straightEnemy[], Enemy shootingEnemy[], Enemy backEnemy[],Enemy raidEnemy[], int blockHP[], bool blockFlag[], int blockX1[], int blockX2[], int blockY1[], int blockY2[],int explosionSound)
{
    for (int i = 0; i < PlayerShotNumber; i++)
    {
        if (PlayerBullet[i].isInScreenFlag)
        {
            //弾が画面外にでたら消す(フラグをfalseにする)
            if (PlayerBullet[i].x1 > 1925)
            {
                PlayerBullet[i].isInScreenFlag = false;
            }

            //黒に弾が当たったら消す（フレンドリーファイア）
            if (player2.x < PlayerBullet[i].x2 && PlayerBullet[i].x2 < player2.x + 270 && player2.y < PlayerBullet[i].y1 && PlayerBullet[i].y1 < player2.y + 175)
            {
                PlayerBullet[i].isInScreenFlag = false;
            }

            //プレイヤーの弾が画面内にいるときだけ
            if (PlayerBullet[i].x2 < 1925)
            {
                for (int j = 0; j  < zigzagEnemyNumber; j ++)
                {
                //ジグザグ敵当たったら(ついでに)ジグザグ敵と弾を消す
                    if (zigzagEnemy[j].isInScreenFlag)
                    {
                        if (zigzagEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < zigzagEnemy[j].x2 && zigzagEnemy[j].y1 < PlayerBullet[i].y2 && PlayerBullet[i].y2 < zigzagEnemy[j].y2 || zigzagEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < zigzagEnemy[j].x2 && zigzagEnemy[j].y1 < PlayerBullet[i].y1 && PlayerBullet[i].y1 < zigzagEnemy[j].y2)
                        {
							//敵を倒したときの効果音を流す
							PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK, TRUE);

                            PlayerBullet[i].isInScreenFlag = false;
                            zigzagEnemy[j].isInScreenFlag = false;

                            //スコアを増やす
                            score += 10;
                        }
                    }
                }

                for (int j = 0; j < straightEnemyNumber; j++)
                {
                //真っ直ぐ敵当たったら(ついでに)真っ直ぐ敵と弾を消す
                    if (straightEnemy[j].isInScreenFlag)
                    {
                        if (straightEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < straightEnemy[j].x2 && straightEnemy[j].y1 < PlayerBullet[i].y2 && PlayerBullet[i].y2 < straightEnemy[j].y2 || straightEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < straightEnemy[j].x2 && straightEnemy[j].y1 < PlayerBullet[i].y1 && PlayerBullet[i].y1 < straightEnemy[j].y2)
                        {
							//敵を倒したときの効果音を流す
							PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK, TRUE);

                            PlayerBullet[i].isInScreenFlag = false;
                            straightEnemy[j].isInScreenFlag = false;

                            //スコアを増やす
                            score += 10;
                        }
                    }
                }

                for (int j = 0; j < shootingEnemyNumber; j++)
                {
                //うちまくり敵当たったら(ついでに)うちまくり敵と弾を消す
                    if (shootingEnemy[j].isInScreenFlag)
                    {
                        if (shootingEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < shootingEnemy[j].x2 && shootingEnemy[j].y1 < PlayerBullet[i].y2 && PlayerBullet[i].y2 < shootingEnemy[j].y2 || shootingEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < shootingEnemy[j].x2 && shootingEnemy[j].y1 < PlayerBullet[i].y1 && PlayerBullet[i].y1 < shootingEnemy[j].y2)
                        {
							//敵を倒したときの効果音を流す
							PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK, TRUE);

                            PlayerBullet[i].isInScreenFlag = false;
                            shootingEnemy[j].isInScreenFlag = false;

                            //スコアを増やす
                            score += 100;
                        }
                    }
                }
                
                for (int j = 0; j < backEnemyNumber; j++)
                {
                    //後ろから敵に当たったら弾と敵を消す
                    if (backEnemy[j].isInScreenFlag)
                    {
                        if (backEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < backEnemy[j].x2 && backEnemy[j].y1 < PlayerBullet[i].y2 && PlayerBullet[i].y2 < backEnemy[j].y2 || backEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < backEnemy[j].x2 && backEnemy[j].y1 < PlayerBullet[i].y1 && PlayerBullet[i].y1 < backEnemy[j].y2 && j < 12)
                        {
							//敵を倒したときの効果音を流す
							PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK, TRUE);

                            PlayerBullet[i].isInScreenFlag = false;
                            backEnemy[j].isInScreenFlag = false;

                            //スコアを増やす
                            score += 50;
                        }
                    }
                }

				for (int j = 0; j < raidEnemyNumber; j++)
				{
					//奇襲敵当たったら(ついでに)奇襲敵と弾を消す
					if (raidEnemy[j].isInScreenFlag)
					{
						if (raidEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < raidEnemy[j].x2 && raidEnemy[j].y1 < PlayerBullet[i].y2 && PlayerBullet[i].y2 < raidEnemy[j].y2 || raidEnemy[j].x1 < PlayerBullet[i].x2 && PlayerBullet[i].x2 < raidEnemy[j].x2 && raidEnemy[j].y1 < PlayerBullet[i].y1 && PlayerBullet[i].y1 < raidEnemy[j].y2)
						{
							//敵を倒したときの効果音を流す
							PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK, TRUE);

							PlayerBullet[i].isInScreenFlag = false;
							raidEnemy[j].isInScreenFlag = false;

							//スコアを増やす
							score += 10;
						}
					}
				}

				for (int j = 0; j < blockNumber; j++)
				{
					//ブロックに当たったら弾を消す＋ブロックHPを減らす
					if (blockFlag[j])
					{
						if (blockX1[j] < PlayerBullet[i].x2 && PlayerBullet[i].x2 < blockX2[j] && blockY1[j] < PlayerBullet[i].y2 && PlayerBullet[i].y2 < blockY2[j] || blockX1[j] < PlayerBullet[i].x2 && PlayerBullet[i].x2 < blockX2[j] && blockY1[j] < PlayerBullet[i].y1 && PlayerBullet[i].y1 < blockY2[j])
						{
							PlayerBullet[i].isInScreenFlag = false;
							//HPを減らす
							blockHP[j]--;

							//HPが０になったらフラグをfalseにして壁の敵とブロックを消す
							if (blockHP[j] == 0)
							{
								//敵を倒したときの効果音を流す
								PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK, TRUE);

								blockFlag[j] = false;
								backEnemy[2 + j].isInScreenFlag = false;

								//スコアを増やす
								score += 50;
							}
						}
					}
				}
            }
        }
    }
}

//ゲームオーバー関数
void gameOver(Bullet zigzagEnemyBullet[],Player& player1,int bgm,int suctionSound,int succeedSuctionSound,Enemy backEnemy[],Player player2,int playerDeathSound,int& selectscene,Enemy shootingEnemy[],Bullet shootingEnemyBullet[],Enemy straightEnemy[],Enemy zigzagEnemy[],Enemy raidEnemy[],int skullEffect[],int& damage,bool& invincibleFlag)
{
	//無敵時間でなければ当たり判定に入る
	if (!invincibleFlag && player1.x <= 1925 && player2.x <= 1925)
	{
		//ジグザグ敵の弾に当たったらゲームオーバー画面へ移行
		for (int i = 0; i < zigzagEnemyShotNumber; i++)
		{
			if (zigzagEnemyBullet[i].isInScreenFlag)
			{
				//白が敵のジグザグ敵弾に当たったらゲームオーバー
				if (player1.x + nizyuugo < zigzagEnemyBullet[i].x1 && zigzagEnemyBullet[i].x1 < player1.x + hyakugozyuu && player1.y + nizyuugo < zigzagEnemyBullet[i].y1 && zigzagEnemyBullet[i].y1 < player1.y + hyakunanazyuugo
				 || player1.x + nizyuugo < zigzagEnemyBullet[i].x1 && zigzagEnemyBullet[i].x1 < player1.x + hyakugozyuu && player1.y + nizyuugo < zigzagEnemyBullet[i].y2 && zigzagEnemyBullet[i].y2 < player1.y + hyakunanazyuugo)
				{
					//ダメージをカウントする
					damage++;

					//無敵フラグをtrueにする
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE); //ダメージ効果音を流す

					//ダメージが4になったらゲームオーバー
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
						StopSoundMem(succeedSuctionSound); //ゲームオーバーは吸い込み成功効果音を止める
						StopSoundMem(bgm); //bgmを止める

						//どくろエフェクトをだす
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
				//黒が敵のジグザグ敵弾に当たったらゲームオーバー
				if (player2.x + nizyuugo < zigzagEnemyBullet[i].x1 && zigzagEnemyBullet[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < zigzagEnemyBullet[i].y1 && zigzagEnemyBullet[i].y1 < player2.y + hyakunanazyuugo
				 || player2.x + nizyuugo < zigzagEnemyBullet[i].x1 && zigzagEnemyBullet[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < zigzagEnemyBullet[i].y2 && zigzagEnemyBullet[i].y2 < player2.y + hyakunanazyuugo)
				{
					//ダメージをカウントする
					damage++;

					//無敵フラグをtrueにする
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//ダメージが４になったらゲームオーバー
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
						StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
						StopSoundMem(bgm); //bgmを止める

						//どくろエフェクトをだす
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
			}
		}

		//うちまくり敵の弾にあたったらゲームオーバー画面へ
		for (int i = 0; i < shootingEnemyShotNumber; i++)
		{
			if (shootingEnemyBullet[i].isInScreenFlag)
			{
				//白が敵のうちまくり敵弾に当たったらゲームオーバー
				if (player1.x + nizyuugo < shootingEnemyBullet[i].x1 && shootingEnemyBullet[i].x1 < player1.x + hyakugozyuu && player1.y + nizyuugo < shootingEnemyBullet[i].y1 && shootingEnemyBullet[i].y1 < player1.y + hyakunanazyuugo
				 || player1.x + nizyuugo < shootingEnemyBullet[i].x1 && shootingEnemyBullet[i].x1 < player1.x + hyakugozyuu && player1.y + nizyuugo < shootingEnemyBullet[i].y2 && shootingEnemyBullet[i].y2 < player1.y + hyakunanazyuugo)
				{
					//ダメージをカウントする
					damage++;

					//無敵フラグをtrueにする
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//ダメージが４になったらゲームオーバー
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
						StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
						StopSoundMem(bgm); //bgmを止める
						
						//どくろエフェクトをだす
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
				//黒が敵のうちまくり敵弾に当たったらゲームオーバー
				if (player2.x + nizyuugo < shootingEnemyBullet[i].x1 && shootingEnemyBullet[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < shootingEnemyBullet[i].y1 && shootingEnemyBullet[i].y1 < player2.y + hyakunanazyuugo
				 || player2.x + nizyuugo < shootingEnemyBullet[i].x1 && shootingEnemyBullet[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < shootingEnemyBullet[i].y2 && shootingEnemyBullet[i].y2 < player2.y + hyakunanazyuugo)
				{
					//ダメージをカウントする
					damage++;

					//無敵フラグをtrueにする
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//ダメージが４になったらゲームオーバー
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
						StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
						StopSoundMem(bgm); //bgmを止める
						
						//どくろエフェクトをだす
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
			}
		}

		//ジグザグ敵に当たったらゲームオーバー画面へ移行
		for (int i = 0; i < zigzagEnemyNumber; i++)
		{
			if (zigzagEnemy[i].isInScreenFlag)
			{
				//白がジグザグ敵に当たったらゲームオーバー
				if (player1.x + nizyuugo < zigzagEnemy[i].x1 && zigzagEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < zigzagEnemy[i].y1 && zigzagEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < zigzagEnemy[i].x1 && zigzagEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < zigzagEnemy[i].y2 && zigzagEnemy[i].y2 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < zigzagEnemy[i].x2 && zigzagEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < zigzagEnemy[i].y1 && zigzagEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < zigzagEnemy[i].x2 && zigzagEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < zigzagEnemy[i].y2 && zigzagEnemy[i].y2 < player1.y + hyakugozyuu)
				{
					//ダメージをカウントする
					damage++;

					//無敵フラグをtrueにする
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//ダメージが４になったらゲームオーバー
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
						StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
						StopSoundMem(bgm); //bgmを止める
						
						//どくろエフェクトをだす
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}

				//黒がジグザグ敵に当たったらゲームオーバー
				if (player2.x + nizyuugo < zigzagEnemy[i].x1 && zigzagEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < zigzagEnemy[i].y1 && zigzagEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < zigzagEnemy[i].x1 && zigzagEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < zigzagEnemy[i].y2 && zigzagEnemy[i].y2 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < zigzagEnemy[i].x2 && zigzagEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < zigzagEnemy[i].y1 && zigzagEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < zigzagEnemy[i].x2 && zigzagEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < zigzagEnemy[i].y2 && zigzagEnemy[i].y2 < player2.y + hyakugozyuu)
				{
					//ダメージをカウントする
					damage++;

					//無敵フラグをtrueにする
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//ダメージが４になったらゲームオーバー
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
						StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
						StopSoundMem(bgm); //bgmを止める

						//どくろエフェクトをだす
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
			}

		}
		//真っ直ぐ敵にあたったらゲームオーバー画面へ
		for (int i = 0; i < straightEnemyNumber; i++)
		{
			if (straightEnemy[i].isInScreenFlag)
			{
				//白が真っ直ぐ敵に当たったらゲームオーバー
				if (player1.x + nizyuugo < straightEnemy[i].x1 && straightEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < straightEnemy[i].y1 && straightEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < straightEnemy[i].x1 && straightEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < straightEnemy[i].y2 && straightEnemy[i].y2 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < straightEnemy[i].x2 && straightEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < straightEnemy[i].y1 && straightEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < straightEnemy[i].x2 && straightEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < straightEnemy[i].y2 && straightEnemy[i].y2 < player1.y + hyakugozyuu)
				{
					//ダメージをカウントする
					damage++;

					//無敵フラグをtrueにする
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//ダメージが４になったらゲームオーバー
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
						StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
						StopSoundMem(bgm); //bgmを止める

						//どくろエフェクトをだす
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
				//黒が真っ直ぐ敵に当たったらゲームオーバー
				if (player2.x + nizyuugo < straightEnemy[i].x1 && straightEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < straightEnemy[i].y1 && straightEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < straightEnemy[i].x1 && straightEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < straightEnemy[i].y2 && straightEnemy[i].y2 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < straightEnemy[i].x2 && straightEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < straightEnemy[i].y1 && straightEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < straightEnemy[i].x2 && straightEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < straightEnemy[i].y2 && straightEnemy[i].y2 < player2.y + hyakugozyuu)
				{
					//ダメージをカウントする
					damage++;

					//無敵フラグをtrueにする
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//ダメージが４になったらゲームオーバー
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
						StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
						StopSoundMem(bgm); //bgmを止める

						//どくろエフェクトをだす
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
			}
		}
		//うちまくり敵にあたったらゲームオーバー
		for (int i = 0; i < shootingEnemyNumber; i++)
		{
			if (shootingEnemy[i].isInScreenFlag)
			{
				//白が敵のうちまくる敵に当たったらゲームオーバー
				if (player1.x + nizyuugo < shootingEnemy[i].x1 && shootingEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < shootingEnemy[i].y1 && shootingEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < shootingEnemy[i].x1 && shootingEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < shootingEnemy[i].y2 && shootingEnemy[i].y2 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < shootingEnemy[i].x2 && shootingEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < shootingEnemy[i].y1 && shootingEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < shootingEnemy[i].x2 && shootingEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < shootingEnemy[i].y2 && shootingEnemy[i].y2 < player1.y + hyakugozyuu)
				{
					//ダメージをカウントする
					damage++;

					//無敵フラグをtrueにする
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//ダメージが４になったらゲームオーバー
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
						StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
						StopSoundMem(bgm); //bgmを止める

						//どくろエフェクトをだす
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
				//黒がうちまくる敵に当たったらゲームオーバー
				if (player2.x + nizyuugo < shootingEnemy[i].x1 && shootingEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < shootingEnemy[i].y1 && shootingEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < shootingEnemy[i].x1 && shootingEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < shootingEnemy[i].y2 && shootingEnemy[i].y2 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < shootingEnemy[i].x2 && shootingEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < shootingEnemy[i].y1 && shootingEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < shootingEnemy[i].x2 && shootingEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < shootingEnemy[i].y2 && shootingEnemy[i].y2 < player2.y + hyakugozyuu)
				{
					//ダメージをカウントする
					damage++;

					//無敵フラグをtrueにする
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//ダメージが４になったらゲームオーバー
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
						StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
						StopSoundMem(bgm); //bgmを止める
						

						//どくろエフェクトをだす
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
			}
		}
		//後ろから敵にあたったらゲームオーバー画面へ
		for (int i = 0; i < backEnemyNumber; i++)
		{
			if (backEnemy[i].isInScreenFlag)
			{
				//でかい敵との判定(しろ）
				if (i == 12 && backEnemy[12].x1 < player1.x && player1.x < backEnemy[12].x2 - 100 && backEnemy[12].y1 < player1.y && player1.y < backEnemy[12].y2)
				{
					//ダメージをカウントする
					damage++;

					//無敵フラグをtrueにする
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//ダメージが４になったらゲームオーバー
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
						StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
						StopSoundMem(bgm); //bgmを止める
						
						//どくろエフェクトをだす
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
				//でかい敵との当たり判定（黒)
				else if (i == 12 && backEnemy[12].x1 < player2.x && player2.x < backEnemy[12].x2 - 100 && backEnemy[12].y1 < player2.y && player2.y < backEnemy[12].y2)
				{
					//ダメージをカウントする
					damage++;

					//無敵フラグをtrueにする
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//ダメージが４になったらゲームオーバー
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
						StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
						StopSoundMem(bgm); //bgmを止める
						
						//どくろエフェクトをだす
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
				else
				{
					//白が敵の後ろから敵に当たったらゲームオーバー
					if (player1.x + nizyuugo < backEnemy[i].x1 && backEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < backEnemy[i].y1 && backEnemy[i].y1 < player1.y + hyakugozyuu
						|| player1.x + nizyuugo < backEnemy[i].x1 && backEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < backEnemy[i].y2 && backEnemy[i].y2 < player1.y + hyakugozyuu
						|| player1.x + nizyuugo < backEnemy[i].x2 && backEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < backEnemy[i].y1 && backEnemy[i].y1 < player1.y + hyakugozyuu
						|| player1.x + nizyuugo < backEnemy[i].x2 && backEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < backEnemy[i].y2 && backEnemy[i].y2 < player1.y + hyakugozyuu)
					{
						//ダメージをカウントする
						damage++;

						//無敵フラグをtrueにする
						invincibleFlag = true;

						PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

						//ダメージが４になったらゲームオーバー
						if (damage >= overDamage)
						{
							StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
							StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
							StopSoundMem(bgm); //bgmを止める
							
							//どくろエフェクトをだす
							for (int i = 0; i < 15; i++)
							{
								DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
								WaitTimer(100);
							}

							selectscene = OVER;
							break;
						}
					}
					//黒が後ろから敵に当たったらゲームオーバー
					if (player2.x + nizyuugo < backEnemy[i].x1 && backEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < backEnemy[i].y1 && backEnemy[i].y1 < player2.y + hyakugozyuu
						|| player2.x + nizyuugo < backEnemy[i].x1 && backEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < backEnemy[i].y2 && backEnemy[i].y2 < player2.y + hyakugozyuu
						|| player2.x + nizyuugo < backEnemy[i].x2 && backEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < backEnemy[i].y1 && backEnemy[i].y1 < player2.y + hyakugozyuu
						|| player2.x + nizyuugo < backEnemy[i].x2 && backEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < backEnemy[i].y2 && backEnemy[i].y2 < player2.y + hyakugozyuu)
					{
						//ダメージをカウントする
						damage++;

						//無敵フラグをtrueにする
						invincibleFlag = true;

						PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

						//ダメージが４になったらゲームオーバー
						if (damage >= overDamage)
						{
							StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
							StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
							StopSoundMem(bgm); //bgmを止める
							

							//どくろエフェクトをだす
							for (int i = 0; i < 15; i++)
							{
								DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
								WaitTimer(100);
							}

							selectscene = OVER;
							break;
						}
					}
				}
			}
		}
		//奇襲敵にあたったらゲームオーバー画面へ
		for (int i = 0; i < raidEnemyNumber; i++)
		{
			if (raidEnemy[i].isInScreenFlag)
			{
				//白が奇襲敵に当たったらゲームオーバー
				if (player1.x + nizyuugo < raidEnemy[i].x1 && raidEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < raidEnemy[i].y1 && raidEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < raidEnemy[i].x1 && raidEnemy[i].x1 < player1.x + hyakunizyuugo && player1.y + nizyuugo < raidEnemy[i].y2 && raidEnemy[i].y2 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < raidEnemy[i].x2 && raidEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < raidEnemy[i].y1 && raidEnemy[i].y1 < player1.y + hyakugozyuu
					|| player1.x + nizyuugo < raidEnemy[i].x2 && raidEnemy[i].x2 < player1.x + hyakunizyuugo && player1.y + nizyuugo < raidEnemy[i].y2 && raidEnemy[i].y2 < player1.y + hyakugozyuu)
				{
					//ダメージをカウントする
					damage++;

					//無敵フラグをtrueにする
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//ダメージが４になったらゲームオーバー
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
						StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
						StopSoundMem(bgm); //bgmを止める
						
						//どくろエフェクトをだす
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player1.x, player1.y, player1.x + 200, player1.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
				//黒が奇襲敵に当たったらゲームオーバー
				if (player2.x + nizyuugo < raidEnemy[i].x1 && raidEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < raidEnemy[i].y1 && raidEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < raidEnemy[i].x1 && raidEnemy[i].x1 < player2.x + hyakunizyuugo && player2.y + nizyuugo < raidEnemy[i].y2 && raidEnemy[i].y2 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < raidEnemy[i].x2 && raidEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < raidEnemy[i].y1 && raidEnemy[i].y1 < player2.y + hyakugozyuu
					|| player2.x + nizyuugo < raidEnemy[i].x2 && raidEnemy[i].x2 < player2.x + hyakunizyuugo && player2.y + nizyuugo < raidEnemy[i].y2 && raidEnemy[i].y2 < player2.y + hyakugozyuu)
				{
					//ダメージをカウントする
					damage++;

					//無敵フラグをtrueにする
					invincibleFlag = true;

					PlaySoundMem(playerDeathSound, DX_PLAYTYPE_BACK, TRUE);

					//ダメージが４になったらゲームオーバー
					if (damage >= overDamage)
					{
						StopSoundMem(suctionSound); // ゲームオーバーは吸い込み効果音を止める
						StopSoundMem(succeedSuctionSound); //ゲームオーバー中は吸い込み成功効果音を止める
						StopSoundMem(bgm); //bgmを止める
						
						//どくろエフェクトをだす
						for (int i = 0; i < 15; i++)
						{
							DrawExtendGraph(player2.x, player2.y, player2.x + 200, player2.y + 200, skullEffect[i], TRUE);
							WaitTimer(100);
						}

						selectscene = OVER;
						break;
					}
				}
			}
		}
	}
}