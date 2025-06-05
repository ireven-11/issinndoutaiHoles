#include"DxLib.h"
#include"enemy.h"

//ジグザグ敵初期化
void InitializeZigzagEnemy(Enemy zigzagEnemy[])
{
    //読み込み
    int midori_teki = LoadGraph("img/midori_teki.png");
    int i = 0;
    int displaceY = zero; //ｙのずらし量
    int displaceX = zero; //xのずらし量

    //画像を代入
    zigzagEnemy[0].graph = midori_teki;

    //存在フラグをtrueにしておく
    zigzagEnemy[0].isInScreenFlag = true;

    //爆発カウントを0にする
    zigzagEnemy[0].explosionCount = 0;

    //爆発フラグをtureにする
    zigzagEnemy[0].explosionFlag = true;

    //初期座標
    zigzagEnemy[0].x1 = 2000 + i * 100 + displaceX * 100;
    zigzagEnemy[0].x2 = zigzagEnemy[0].x1 + 100;
    zigzagEnemy[0].y1 = 10000;
    zigzagEnemy[0].y2 = 20000;

    while (true)
    {
        //第一小隊
        if (i < zigzagEnemyNumber)
        {
            while (true)
            {
                if (i == 0)
                {
                    
                }
                else
                {
                    //画像を代入
                    zigzagEnemy[i].graph = midori_teki;

                    //存在フラグをtrueにしておく
                    zigzagEnemy[i].isInScreenFlag = true;

                    //爆発カウントを0にする
                    zigzagEnemy[i].explosionCount = 0;

                    //爆発フラグをtureにする
                    zigzagEnemy[i].explosionFlag = true;

                    //初期座標
                    zigzagEnemy[i].x1 = 2000 + i * 100 + displaceX * 100;
                    zigzagEnemy[i].x2 = zigzagEnemy[i].x1 + 100;
                    zigzagEnemy[i].y1 = 100 + displaceY * 150;
                    zigzagEnemy[i].y2 = zigzagEnemy[i].y1 + 100;
                }
                

                i++;

                if (i % 5 == 0)
                {
                    displaceY++;
                    break;
                }
            }
        }
            
        //第二小隊
        if (i < zigzagEnemyNumber)
        {
            while (true)
            {
                //画像を代入
                zigzagEnemy[i].graph = midori_teki;

                //存在フラグをtrueにしておく
                zigzagEnemy[i].isInScreenFlag = true;

                //爆発カウントを0にする
                zigzagEnemy[i].explosionCount = 0;

                //爆発フラグをtureにする
                zigzagEnemy[i].explosionFlag = true;

                //初期座標
                zigzagEnemy[i].x1 = 2250 + i * 100 + displaceX * 100;
                zigzagEnemy[i].x2 = zigzagEnemy[i].x1 + 100;
                zigzagEnemy[i].y1 = 750 - displaceY * 150;
                zigzagEnemy[i].y2 = zigzagEnemy[i].y1 + 100;

                i++;

                if (i % 5 == 0)
                {
                    displaceX++;
                    break;
                }
            }
        }
            
        if (i == zigzagEnemyNumber)
        {
            break;
        }
    }
}

//ジグザグ敵ルーチン
void UpdateZigzagEnemy(Enemy zigzagEnemy[])
{
    //移動
    for (int i = 0; i < zigzagEnemyNumber; i++)
    {
        if (i == 0)
        {
            //０のやつは移動させない
        }
        else
        {
            if (zigzagEnemy[i].isInScreenFlag)
            {
                zigzagEnemy[i].x1 -= zigzagEnemy[i].speed * 2 + 1;
                zigzagEnemy[i].x2 -= zigzagEnemy[i].speed * 2 + 1;

                if (zigzagEnemy[i].x1 < 1300 && zigzagEnemy[i].x1 > 1000)
                {
                    zigzagEnemy[i].y1 += zigzagEnemy[i].speed * 3;
                    zigzagEnemy[i].y2 += zigzagEnemy[i].speed * 3;
                }
                else if (zigzagEnemy[i].x1 < 1000 && zigzagEnemy[i].x1 > 700)
                {
                    zigzagEnemy[i].y1 -= zigzagEnemy[i].speed * 3;
                    zigzagEnemy[i].y2 -= zigzagEnemy[i].speed * 3;
                }
                else if (zigzagEnemy[i].x1 < 700)
                {
                    zigzagEnemy[i].y1 += zigzagEnemy[i].speed * 3;
                    zigzagEnemy[i].y2 += zigzagEnemy[i].speed * 3;
                }
            }
        }
    }
}

//ジグザグ敵描画
void DrawZigzagEnemy(Enemy zigzagEnemy[], int explosionEffect[])
{
    for (int i = 0; i < zigzagEnemyNumber; i++)
    {
        //ジグザグ敵描画
        if (zigzagEnemy[i].x2 <= 2000 && zigzagEnemy[i].isInScreenFlag)
        {
            if (i == 0)
            {
                DrawExtendGraph(zigzagEnemy[0].x2, zigzagEnemy[0].y1, zigzagEnemy[0].x1, zigzagEnemy[0].y2, zigzagEnemy[0].graph, TRUE);
            }
            else
            {
                DrawExtendGraph(zigzagEnemy[i].x2, zigzagEnemy[i].y1, zigzagEnemy[i].x1, zigzagEnemy[i].y2, zigzagEnemy[i].graph, TRUE);
            }
        }
        
        //爆発エフェクトを描画
        if (!zigzagEnemy[i].isInScreenFlag && zigzagEnemy[i].explosionFlag)
        {
            DrawGraph(zigzagEnemy[i].x1 + 10, zigzagEnemy[i].y1 + 10, explosionEffect[zigzagEnemy[i].explosionCount], TRUE);

            //カウントを増やす。count++;
            zigzagEnemy[i].explosionCount++;

            //カウントがアニメーションの数よりおおきくなったら０に戻す
            if (zigzagEnemy[i].explosionCount > 11)
            {
                zigzagEnemy[i].explosionFlag = false;
                zigzagEnemy[i].explosionCount = 0;
            }
        }
    }
}