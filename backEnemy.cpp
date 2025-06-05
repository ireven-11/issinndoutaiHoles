#include"DxLib.h"
#include"enemy.h"
#include"player.h"

//後ろから敵初期化
void InitializeBackEnemy(Enemy backEnemy[])
{
    int tyairoteki = LoadGraph("img/tyairo_teki.png");
	int j = 0;
				
	for (int i = 0; i < backEnemyNumber	; i++)
	{
		//画像読み込み
		backEnemy[i].graph = tyairoteki;

		//爆発カウントを0にする
		backEnemy[i].explosionCount = 0;

		//爆発フラグをtureにする
		backEnemy[i].explosionFlag = true;

		//初期座標を設定
		//最初の2体
		if (i < 2)
		{
			if (i == 0)
			{
				backEnemy[0].x1 = IniBackEnemyX;
				backEnemy[0].y1 = IniBackEnemyY + i * fiveHundred;
				backEnemy[0].x2 = backEnemy[0].x1 + hundredfifteen;
				backEnemy[0].y2 = backEnemy[0].y1 + IniBackEnemyY;
			}
			else
			{
				backEnemy[i].x1 = IniBackEnemyX;
				backEnemy[i].y1 = IniBackEnemyY + i * fiveHundred;
				backEnemy[i].x2 = backEnemy[i].x1 + hundredfifteen;
				backEnemy[i].y2 = backEnemy[i].y1 + IniBackEnemyY;
			}
		}
		//残りは壁としてwave４でだす
		else if(i < 12)
		{
			backEnemy[i].x1 = -150;
			backEnemy[i].y1 = 0 + j * 100;
			backEnemy[i].x2 = backEnemy[i].x1 + 150;
			backEnemy[i].y2 = backEnemy[i].y1 + 100;
			j++;
		}
		//くそでかいやつ
		else
		{
			backEnemy[i].x1 = -1500;
			backEnemy[i].y1 = 0;
			backEnemy[i].x2 = backEnemy[i].x1 + 1400;
			backEnemy[i].y2 = backEnemy[i].y1 + 1000;
		}
		//存在フラグをtureにする
		backEnemy[i].isInScreenFlag = true;

		//動き変化フラグをfalseにする
		backEnemy[i].changeMoveFlag = false;
	}
}

//後ろから敵ルーチン
void UpdateBackEnemy(Enemy backEnemy[],int wave1,int& scroll,Player& player2, int wave3, int wave4)
{
	for (int i = 0; i < backEnemyNumber; i++)
	{
		//最初の2体のうごき
		if (i < 2)
		{
			//座標が1000より小さくwave2のときに右に移動
			if (backEnemy[i].x1 < 1000 && scroll > wave1 && !backEnemy[i].changeMoveFlag)
			{
				backEnemy[i].x1 += backEnemy[i].speed * 2;
				backEnemy[i].x2 += backEnemy[i].speed * 2;
			}

			if (backEnemy[i].x1 == 1000)
			{
				//動き変化フラグをtrueにする
				backEnemy[i].changeMoveFlag = true;
			}

			//スクロールが一定になったら左に移動を始める
			if (backEnemy[i].changeMoveFlag)
			{
				backEnemy[i].x1 -= backEnemy[i].speed * 2;
				backEnemy[i].x2 -= backEnemy[i].speed * 2;

				//プレイヤーと敵のyの距離によって移動を変える
				if (backEnemy[i].y1 - player2.y < 0)
				{
					backEnemy[i].y1 += backEnemy[i].speed;
					backEnemy[i].y2 += backEnemy[i].speed;
				}
				else if (backEnemy[i].y1 - player2.y > 0)
				{
					backEnemy[i].y1 -= backEnemy[i].speed;
					backEnemy[i].y2 -= backEnemy[i].speed;
				}
			}
		}
		//敵で壁を作る(途中から移動しなくなる)
		else if (i > 1 && i < 12 && scroll > wave3 && scroll % 2 == 0)
		{
			backEnemy[i].x1 += backEnemy[i].speed;
			backEnemy[i].x2 += backEnemy[i].speed;
		}
		//でかいやつの移動
		else if(scroll > wave3 && scroll % 5 == 0 && i == 12)
		{
			backEnemy[i].x1 += backEnemy[i].speed;
			backEnemy[i].x2 += backEnemy[i].speed;
		}

		//クリア画面になったら存在フラグをfalseにする
		if (scroll > wave4)
		{
			backEnemy[i].isInScreenFlag = false;
		}
	}
}

//後ろから敵描画
void DrawBackEnemy(Enemy backEnemy[], int explosionEffect[])
{
	for (int i = 0; i < backEnemyNumber; i++)
	{
		//フラグがtureのときだけ
		if (backEnemy[i].isInScreenFlag)
		{
			if (i == 0)
			{
				if (!backEnemy[0].changeMoveFlag)
				{
					DrawExtendGraph(backEnemy[0].x1, backEnemy[0].y1, backEnemy[0].x2, backEnemy[0].y2, backEnemy[0].graph, TRUE);
				}
				else
				{
					DrawExtendGraph(backEnemy[0].x2, backEnemy[0].y1, backEnemy[0].x1, backEnemy[0].y2, backEnemy[0].graph, TRUE);
				}
			}
			else
			{
				if (!backEnemy[i].changeMoveFlag)
				{
					DrawExtendGraph(backEnemy[i].x1, backEnemy[i].y1, backEnemy[i].x2, backEnemy[i].y2, backEnemy[i].graph, TRUE);
				}
				else
				{
					DrawExtendGraph(backEnemy[i].x2, backEnemy[i].y1, backEnemy[i].x1, backEnemy[i].y2, backEnemy[i].graph, TRUE);
				}
			}
		}

		//爆発エフェクトを描画
		if (!backEnemy[i].isInScreenFlag && backEnemy[i].explosionFlag)
		{
			if (i < 12)
			{
				DrawGraph(backEnemy[i].x1 + 10, backEnemy[i].y1 + 10, explosionEffect[backEnemy[i].explosionCount], TRUE);
			}
			else
			{
				DrawExtendGraph(backEnemy[i].x1 / 2, backEnemy[i].y1, backEnemy[i].x2, backEnemy[i].y2, explosionEffect[backEnemy[i].explosionCount], TRUE);
			}
			//カウントを増やす。count++;
			backEnemy[i].explosionCount++;

			//カウントがアニメーションの数よりおおきくなったら０に戻す
			if (backEnemy[i].explosionCount > 11)
			{
				backEnemy[i].explosionFlag = false;
				backEnemy[i].explosionCount = 0;
			}
		}
	}
}