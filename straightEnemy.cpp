#include"Dxlib.h"
#include"enemy.h"

//真っ直ぐ敵初期化
void InitializeStraightEnemy(Enemy straightEnemy[])
{
    //読み込み
    int midori_teki = LoadGraph("img/midori_teki.png");
    int i = 0;

    

    while (true)
    {
        //第一小隊
        if (i <= straightEnemyNumber)
        {
            while (true)
            {
                //画像を代入
                straightEnemy[i].graph = midori_teki;

                //存在フラグをtrueにしておく
                straightEnemy[i].isInScreenFlag = true;

                //爆発カウントを0にする
                straightEnemy[i].explosionCount = 0;

                //爆発フラグをtureにする
                straightEnemy[i].explosionFlag = true;

                //初期座標
                straightEnemy[i].x1 = 2000 + i * 100;
                straightEnemy[i].x2 = straightEnemy[i].x1 + 100;
                straightEnemy[i].y1 = 133;
                straightEnemy[i].y2 = straightEnemy[i].y1 + 100;

                i++;

                if (i % 3 == 0)
                {
                    break;
                }
            }
        }

        //第二小隊
        if (i <= straightEnemyNumber)
        {
            while (true)
            {
                //画像を代入
                straightEnemy[i].graph = midori_teki;

                //存在フラグをtrueにしておく
                straightEnemy[i].isInScreenFlag = true;

                //爆発カウントを0にする
                straightEnemy[i].explosionCount = 0;

                //爆発フラグをtureにする
                straightEnemy[i].explosionFlag = true;

                //初期座標
                straightEnemy[i].x1 = 2000 + i * 100;
                straightEnemy[i].x2 = straightEnemy[i].x1 + 100;
                straightEnemy[i].y1 = 799;
                straightEnemy[i].y2 = straightEnemy[i].y1 + 100;

                i++;

                if (i % 3 == 0)
                {
                    break;
                }
            }
        }

        //第三小隊
        if (i <= straightEnemyNumber)
        {
            while (true)
            {
                i++;

                //画像を代入
                straightEnemy[i].graph = midori_teki;

                //存在フラグをtrueにしておく
                straightEnemy[i].isInScreenFlag = true;

                //爆発カウントを0にする
                straightEnemy[i].explosionCount = 0;

                //爆発フラグをtureにする
                straightEnemy[i].explosionFlag = true;

                //初期座標
                straightEnemy[i].x1 = 2000 + i * 100;
                straightEnemy[i].x2 = straightEnemy[i].x1 + 100;
                straightEnemy[i].y1 = 466;
                straightEnemy[i].y2 = straightEnemy[i].y1 + 100;

                if (i % 3 == 0)
                {
                    break;
                }
            }
        }

        if (i == straightEnemyNumber)
        {
            break;
        }
    }
}

//真っ直ぐ敵ルーチン
void UpdateStraightEnemy(Enemy straightEnemy[])
{
    for (int i = 0; i < straightEnemyNumber; i++)
    {
        if (straightEnemy[i].isInScreenFlag)
        {
            //上側と下側の小隊の移動
            straightEnemy[i].x1 -= straightEnemy[i].speed * 3 - 1;
            straightEnemy[i].x2 -= straightEnemy[i].speed * 3 - 1;

            //真ん中の2体だけ奇襲を仕掛ける
            if (i > 6)
            {
                straightEnemy[i].x1 -= straightEnemy[i].speed * 4 - 1;
                straightEnemy[i].x2 -= straightEnemy[i].speed * 4 - 1;
            }
        }
    }
}

//真っ直ぐ敵描画
void DrawStraightEnemy(Enemy straightEnemy[], int explosionEffect[])
{
    for (int i = 0; i < straightEnemyNumber; i++)
    {
        //真っ直ぐ敵描画
        if (straightEnemy[i].x2 <= 2000 && straightEnemy[i].isInScreenFlag)
        {
            DrawExtendGraph(straightEnemy[i].x2, straightEnemy[i].y1, straightEnemy[i].x1, straightEnemy[i].y2, straightEnemy[i].graph, TRUE);
        }

        //爆発エフェクトを描画
        if (!straightEnemy[i].isInScreenFlag && straightEnemy[i].explosionFlag)
        {
            DrawGraph(straightEnemy[i].x1 + 10, straightEnemy[i].y1 + 10, explosionEffect[straightEnemy[i].explosionCount], TRUE);

            //カウントを増やす。count++;
            straightEnemy[i].explosionCount++;

            //カウントがアニメーションの数よりおおきくなったら０に戻す
            if (straightEnemy[i].explosionCount > 11)
            {
                straightEnemy[i].explosionFlag = false;
                straightEnemy[i].explosionCount = 0;
            }
        }
    }
}