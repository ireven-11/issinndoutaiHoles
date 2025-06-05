#include"Dxlib.h"
#include"enemy.h"

//奇襲敵初期化
void InitializeRaidEnemy(Enemy raidEnemy[])
{
    int fukamidoriteki = LoadGraph("img/fukamidori_teki.png");
    int i = 0;
    int j = 0;

    

    while (true)
    {
        //画像読み込み
        raidEnemy[i].graph = fukamidoriteki;

        //存在フラグをtrueにする
        raidEnemy[i].isInScreenFlag = true;

        //移動変化フラグをfalseにする
        raidEnemy[i].changeMoveFlag = false;

        //爆発カウントを0にする
        raidEnemy[i].explosionCount = 0;

        //爆発フラグをtureにする
        raidEnemy[i].explosionFlag = true;

        //上からくる敵の初期座標
        if (i % 2 == 0)
        {
            //第一小隊
            if (i < 16)
            {
                raidEnemy[i].x1 = 0 + i * 125;
                raidEnemy[i].x2 = raidEnemy[i].x1 + 125;
                raidEnemy[i].y1 = -400 - i * 200;
                raidEnemy[i].y2 = raidEnemy[i].y1 + 75;
            }
            //第二小隊
            else
            {
                raidEnemy[i].x1 = 0 + j * 125;
                raidEnemy[i].x2 = raidEnemy[i].x1 + 125;
                raidEnemy[i].y1 = -100 - i * 150;
                raidEnemy[i].y2 = raidEnemy[i].y1 + 75;
                j++;
            }
        }
        //下からくる敵の初期座標
        else
        {
            //第一小隊
            if (i < 16)
            {
                raidEnemy[i].x1 = 1925 - i * 125;
                raidEnemy[i].x2 = raidEnemy[i].x1 + 125;
                raidEnemy[i].y1 = 1400 + i * 200;
                raidEnemy[i].y2 = raidEnemy[i].y1 + 75;
            }
            //第二小隊
            else
            {
                raidEnemy[i].x1 = 1925 - j * 125;
                raidEnemy[i].x2 = raidEnemy[i].x1 + 125;
                raidEnemy[i].y1 = 1000 + i * 150;
                raidEnemy[i].y2 = raidEnemy[i].y1 + 75;
                j++;
            }
        }

        i++;

        if (i == raidEnemyNumber)
        {
            break;
        }
    }
}

//奇襲敵ルーチン
void UpdateRaidEnemy(Enemy raidEnemy[],int& scroll, int wave2)
{
    int j = 0;

    if (scroll > wave2)
    {
        for (int i = 0; i < raidEnemyNumber; i++)
        {
            //上からくる敵の移動
            if (i % 2 == 0)
            {
                //第一小隊の移動
                if (i < 16)
                {
                    //最後に左に移動
                    if (raidEnemy[i].y1 < 0 + i * 50 && raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].x1 -= raidEnemy[i].speed * 8;
                        raidEnemy[i].x2 -= raidEnemy[i].speed * 8;
                    }
                    //画面外左下まできたら上に移動
                    else if (raidEnemy[i].x1 > 1925)
                    {
                        raidEnemy[i].y1 -= raidEnemy[i].speed * 3;
                        raidEnemy[i].y2 -= raidEnemy[i].speed * 3;
                    }
                    //画面下外まで移動したら右に移動
                    else if (1925 > raidEnemy[i].x1 && raidEnemy[i].y1 > 1000 && !raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].x1 += raidEnemy[i].speed * 3;
                        raidEnemy[i].x2 += raidEnemy[i].speed * 3;
                    }
                    //最初に下に移動
                    else if (!raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].y1 += raidEnemy[i].speed * 3;
                        raidEnemy[i].y2 += raidEnemy[i].speed * 3;
                    }
                }
                //第二小隊の移動
                else
                {
                    //最後に左に移動
                    if (raidEnemy[i].y1 < 0 + j * 50 && raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].x1 -= raidEnemy[i].speed * 5;
                        raidEnemy[i].x2 -= raidEnemy[i].speed * 5;
                    }
                    //画面外左下まできたら上に移動
                    else if (raidEnemy[i].x1 > 1925)
                    {
                        raidEnemy[i].y1 -= raidEnemy[i].speed * 3;
                        raidEnemy[i].y2 -= raidEnemy[i].speed * 3;
                    }
                    //画面下外まで移動したら右に移動
                    else if (1925 > raidEnemy[i].x1 && raidEnemy[i].y1 > 1000 && !raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].x1 += raidEnemy[i].speed * 3;
                        raidEnemy[i].x2 += raidEnemy[i].speed * 3;
                    }
                    //最初に下に移動
                    else if (!raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].y1 += raidEnemy[i].speed * 2;
                        raidEnemy[i].y2 += raidEnemy[i].speed * 2;
                    }
                    j++;
                }
            }
            //下からくる敵の移動
            else
            {
                //第一小隊の移動
                if (i < 16)
                {
                    //最後に左に移動
                    if (raidEnemy[i].y1 > 950 - i * 50 && raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].x1 -= raidEnemy[i].speed * 8;
                        raidEnemy[i].x2 -= raidEnemy[i].speed * 8;
                    }
                    //画面外右まできたら下に移動
                    else if (raidEnemy[i].x1 > 1925 && raidEnemy[i - 1].x1 > 1925)
                    {
                        raidEnemy[i].y1 += raidEnemy[i].speed * 3;
                        raidEnemy[i].y2 += raidEnemy[i].speed * 3;
                    }
                    //画面上外まで移動したら右に移動
                    else if (1925 > raidEnemy[i].x1 && raidEnemy[i].y2 < 0 && !raidEnemy[i].changeMoveFlag)
                    {
                        if (i > 7)
                        {
                            raidEnemy[i].x1 = 1926;
                            raidEnemy[i].x2 = raidEnemy[i].x1 + 125;
                        }
                        else
                        {
                            raidEnemy[i].x1 += raidEnemy[i].speed * 3;
                            raidEnemy[i].x2 += raidEnemy[i].speed * 3;
                        }
                    }
                    //最初に上に移動
                    else if (!raidEnemy[i].changeMoveFlag && raidEnemy[i].x1 < 1925)
                    {
                        raidEnemy[i].y1 -= raidEnemy[i].speed * 3;
                        raidEnemy[i].y2 -= raidEnemy[i].speed * 3;
                    }
                }
                //第二小隊の移動
                else
                {
                    //最後に左に移動
                    if (raidEnemy[i].y1 > 950 - j * 50 && raidEnemy[i].changeMoveFlag)
                    {
                        raidEnemy[i].x1 -= raidEnemy[i].speed * 5;
                        raidEnemy[i].x2 -= raidEnemy[i].speed * 5;
                    }
                    //画面外右まできたら下に移動
                    else if (raidEnemy[i].x1 > 1925 && raidEnemy[i - 1].x1 > 1925)
                    {
                        raidEnemy[i].y1 += raidEnemy[i].speed * 3;
                        raidEnemy[i].y2 += raidEnemy[i].speed * 3;
                    }
                    //画面上外まで移動したら右に移動
                    else if (1925 > raidEnemy[i].x1 && raidEnemy[i].y2 < 0 && !raidEnemy[i].changeMoveFlag)
                    {
                        if (i > 7)
                        {
                            raidEnemy[i].x1 = 1926;
                            raidEnemy[i].x2 = raidEnemy[i].x1 + 125;
                        }
                        else
                        {
                            raidEnemy[i].x1 += raidEnemy[i].speed * 3;
                            raidEnemy[i].x2 += raidEnemy[i].speed * 3;
                        }
                    }
                    //最初に上に移動
                    else if (!raidEnemy[i].changeMoveFlag && raidEnemy[i].x1 < 1925)
                    {
                        raidEnemy[i].y1 -= raidEnemy[i].speed * 2;
                        raidEnemy[i].y2 -= raidEnemy[i].speed * 2;
                    }
                    j++;
                }
            }

            //動き変化フラグをtureにする
            if (raidEnemy[i].x1 > 1925)
            {
                raidEnemy[i].changeMoveFlag = true;
            }
        }
    }
}

//奇襲敵描画
void DrawRaidEnemy(Enemy raidEnemy[], int explosionEffect[])
{ 
    for (int i = 0; i < raidEnemyNumber; i++)
    {
        //フラグがtureのときだけ
        if (raidEnemy[i].isInScreenFlag)
        {
            DrawExtendGraph(raidEnemy[i].x2, raidEnemy[i].y1, raidEnemy[i].x1, raidEnemy[i].y2, raidEnemy[i].graph, TRUE);
        }

        //爆発エフェクトを描画
        if (!raidEnemy[i].isInScreenFlag && raidEnemy[i].explosionFlag)
        {
            DrawGraph(raidEnemy[i].x1 + 10, raidEnemy[i].y1 + 10, explosionEffect[raidEnemy[i].explosionCount], TRUE);

            //カウントを増やす。count++;
            raidEnemy[i].explosionCount++;

            //カウントがアニメーションの数よりおおきくなったら０に戻す
            if (raidEnemy[i].explosionCount > 11)
            {
                raidEnemy[i].explosionFlag = false;
                raidEnemy[i].explosionCount = 0;
            }
        }
    }
}