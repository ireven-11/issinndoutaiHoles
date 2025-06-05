#include"Dxlib.h"
#include"enemy.h"

//うちまくり敵初期化
void InitializeShootingEnemy(Enemy shootingEnemy[])
{
	//画像を保存
    int murasaki_teki = LoadGraph("img/murasaki_teki.png");
	int j = 0;

	for (int i = 0; i < shootingEnemyNumber; i++)
	{
		//画像読み込み
		shootingEnemy[i].graph = murasaki_teki;

		//フラグをtrueにする
		shootingEnemy[i].isInScreenFlag = true;

		//移動変化フラグをfalseにする
		shootingEnemy[i].changeMoveFlag = false;

		//爆発カウントを0にする
		shootingEnemy[i].explosionCount = 0;

		//爆発フラグをtureにする
		shootingEnemy[i].explosionFlag = true;

		//初期座標
		if (i <= 4)
		{
			shootingEnemy[i].y1 = 10 + i * 200;
			shootingEnemy[i].x1 = 2000;
		}
		else
		{
			shootingEnemy[i].x1 = i * 700 + j * 750;
			shootingEnemy[i].y1 = i * 150 - 300;
			j++;
		}
		shootingEnemy[i].x2 = shootingEnemy[i].x1 + 150;
		shootingEnemy[i].y2 = shootingEnemy[i].y1 + 100;

		//動き変化フラグをtureにする
		shootingEnemy[i].changeMoveFlag = true;
	}
}

//うちまくり敵ル-チン
void UpdateShootingEnemy(Enemy shootingEnemy[],int& scroll)
{
	for (int i = 0; i < shootingEnemyNumber; i++)
	{
		//1,2体目がやられたら3,4体目を出す
		if (i < 4 && i > 1 && !shootingEnemy[0].isInScreenFlag && !shootingEnemy[1].isInScreenFlag)
		{
			//直進
			shootingEnemy[i].x1 -= shootingEnemy[i].speed * 3;
			shootingEnemy[i].x2 -= shootingEnemy[i].speed * 3;

			//3体目上に移動
			if (shootingEnemy[2].changeMoveFlag)
			{
				shootingEnemy[2].y1 += shootingEnemy[2].speed * 5;
				shootingEnemy[2].y2 += shootingEnemy[2].speed * 5;
			}
			//3体目下に移動
			else if (!shootingEnemy[2].changeMoveFlag)
			{
				shootingEnemy[2].y1 -= shootingEnemy[2].speed * 2;
				shootingEnemy[2].y2 -= shootingEnemy[2].speed * 2;
			}

			//4体目上に移動
			if (shootingEnemy[3].changeMoveFlag)
			{
				shootingEnemy[3].y1 += shootingEnemy[3].speed * 2;
				shootingEnemy[3].y2 += shootingEnemy[3].speed * 2;
			}
			//4体目下に移動
			else if (!shootingEnemy[3].changeMoveFlag)
			{
				shootingEnemy[3].y1 -= shootingEnemy[3].speed * 5;
				shootingEnemy[3].y2 -= shootingEnemy[3].speed * 5;
			}

			//押し戻り処理＋移動方向の反転
			if (shootingEnemy[i].y2 > 1000)
			{
				shootingEnemy[i].y1 = 1000 - 100;
				shootingEnemy[i].y2 = 1000;
				shootingEnemy[i].changeMoveFlag = false;
			}
			else if (shootingEnemy[i].y1 < 0)
			{
				shootingEnemy[i].y1 = 0;
				shootingEnemy[i].y2 = 100;
				shootingEnemy[i].changeMoveFlag = true;
			}
		}
		//最初の2体の動き
		else if(i < 2)
		{
			//最初だけ直進
			if (scroll > 950 && scroll < 1100)
			{
				shootingEnemy[i].x1 -= shootingEnemy[i].speed * 3;
				shootingEnemy[i].x2 -= shootingEnemy[i].speed * 3;
			}

			if (scroll > 1100 && scroll < 2500)
			{
				//上に移動
				if (shootingEnemy[i].changeMoveFlag)
				{
					shootingEnemy[i].y1 += shootingEnemy[i].speed * 5;
					shootingEnemy[i].y2 += shootingEnemy[i].speed * 5;
				}
				//下に移動
				else if (!shootingEnemy[i].changeMoveFlag)
				{
					shootingEnemy[i].y1 -= shootingEnemy[i].speed * 5;
					shootingEnemy[i].y2 -= shootingEnemy[i].speed * 5;
				}

				//押し戻り処理＋移動方向の反転
				if (shootingEnemy[i].y2 > 1000)
				{
					shootingEnemy[i].y1 = 1000 - 100;
					shootingEnemy[i].y2 = 1000;
					shootingEnemy[i].changeMoveFlag = false;
				}
				else if (shootingEnemy[i].y1 < 0)
				{
					shootingEnemy[i].y1 = 0;
					shootingEnemy[i].y2 = 100;
					shootingEnemy[i].changeMoveFlag = true;
				}
			}

			//最後は直進
			if (scroll > 2500)
			{
				shootingEnemy[i].x1 -= shootingEnemy[i].speed * 5;
				shootingEnemy[i].x2 -= shootingEnemy[i].speed * 5;
			}
		}
		//5体目はジグザグ敵に混ぜて出す
		else if(scroll > 5000 && i == 4)
		{
			if (shootingEnemy[4].x1 >= 1700)
			{
				shootingEnemy[4].x1 -= shootingEnemy[4].speed * 5;
				shootingEnemy[4].x2 -= shootingEnemy[4].speed * 5;
			}
			//上に移動
			else if (shootingEnemy[4].changeMoveFlag)
			{
				shootingEnemy[4].y1 += shootingEnemy[4].speed * 4;
				shootingEnemy[4].y2 += shootingEnemy[4].speed * 4;
			}
			//下に移動
			else if (!shootingEnemy[i].changeMoveFlag)
			{
				shootingEnemy[4].y1 -= shootingEnemy[4].speed * 4;
				shootingEnemy[4].y2 -= shootingEnemy[4].speed * 4;
			}

			//押し戻り処理＋移動方向の反転
			if (shootingEnemy[4].y2 > 1000)
			{
				shootingEnemy[4].y1 = 1000 - 100;
				shootingEnemy[4].y2 = 1000;
				shootingEnemy[4].changeMoveFlag = false;
			}
			else if (shootingEnemy[4].y1 < 0)
			{
				shootingEnemy[4].y1 = 0;
				shootingEnemy[4].y2 = 100;
				shootingEnemy[4].changeMoveFlag = true;
			}

			if (scroll > 6750)
			{
				shootingEnemy[4].x1 -= shootingEnemy[4].speed * 8;
				shootingEnemy[4].x2 -= shootingEnemy[4].speed * 8;
			}
		}
		//6体目以降はwave4でだす
		else if (scroll > 14000 && i > 4)
		{
			//画面内にいなかなったら左に直進
			if (shootingEnemy[i].x2 > 1500 && shootingEnemy[i].changeMoveFlag)
			{
				shootingEnemy[i].x1 -= shootingEnemy[i].speed * 3;
				shootingEnemy[i].x2 -= shootingEnemy[i].speed * 3;
			}
			//三角を描く様に動く
			else if (shootingEnemy[i].x1 > 1300 && shootingEnemy[i].changeMoveFlag)
			{
				shootingEnemy[i].x1 -= shootingEnemy[i].speed * 3;
				shootingEnemy[i].x2 -= shootingEnemy[i].speed * 3;
				shootingEnemy[i].y1 -= shootingEnemy[i].speed * 3;
				shootingEnemy[i].y2 -= shootingEnemy[i].speed * 3;
			}
			else
			{
				if (shootingEnemy[i].y1 < 1100 - i * 100 && shootingEnemy[i].changeMoveFlag)
				{
					shootingEnemy[i].y1 += shootingEnemy[i].speed * 4;
					shootingEnemy[i].y2 += shootingEnemy[i].speed * 4;

					if (shootingEnemy[i].y1 > 1100 - i * 100)
					{
						shootingEnemy[i].changeMoveFlag = false;
					}
				}
				else
				{
					shootingEnemy[i].x1 += shootingEnemy[i].speed * 3;
					shootingEnemy[i].x2 += shootingEnemy[i].speed * 3;
					shootingEnemy[i].y1 -= shootingEnemy[i].speed * 3;
					shootingEnemy[i].y2 -= shootingEnemy[i].speed * 3;

					if (shootingEnemy[i].x1 > 1500)
					{
						shootingEnemy[i].changeMoveFlag = true;
					}
				}
			}
		}

		//スクロールが終わったらフラグをfalseにする
		if (scroll > 21000)
		{
			shootingEnemy[i].isInScreenFlag = false;
		}
	}
}

//うちまくり敵描画
void DrawShootingEnemy(Enemy shootingEnemy[], int explosionEffect[])
{
	for (int i = 0; i < shootingEnemyNumber; i++)
	{
		//真っ直ぐ敵描画
		if (shootingEnemy[i].x2 <= 2000 && shootingEnemy[i].isInScreenFlag)
		{
			DrawExtendGraph(shootingEnemy[i].x2, shootingEnemy[i].y1, shootingEnemy[i].x1, shootingEnemy[i].y2, shootingEnemy[i].graph, TRUE);
		}

		//爆発エフェクトを描画
		if (!shootingEnemy[i].isInScreenFlag && shootingEnemy[i].explosionFlag)
		{
			DrawGraph(shootingEnemy[i].x1 + 10, shootingEnemy[i].y1 + 10, explosionEffect[shootingEnemy[i].explosionCount], TRUE);

			//カウントを増やす。count++;
			shootingEnemy[i].explosionCount++;

			//カウントがアニメーションの数よりおおきくなったら０に戻す
			if (shootingEnemy[i].explosionCount > 11)
			{
				shootingEnemy[i].explosionFlag = false;
				shootingEnemy[i].explosionCount = 0;
			}
		}
	}
}