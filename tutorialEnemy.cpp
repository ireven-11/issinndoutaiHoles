#include"Dxlib.h"
#include"enemy.h"
#include"shot.h"

//チュートリアル敵初期化
void InitializeTutorialEnemy(Enemy& TutorialEnemy,Bullet& TutorialBullet)
{
    //画像の読み込み
    TutorialEnemy.graph = LoadGraph("img/midori_teki.png"); 

    //チュートリアル敵の初期位置
    TutorialEnemy.x1 = 1925 - 150;
    TutorialEnemy.y1 = 0;
    TutorialEnemy.x2 = 1900;
    TutorialEnemy.y2 = 100;
 
    //チュートリアル敵が上に移動しているかのフラグをリセット
    TutorialEnemy.changeMoveFlag = true;

    //チュートリアル敵の弾を初期化
    InitializeTutorialBullet(TutorialBullet);
}

//チュートリアル敵ルーチン
void UpdateTutorialEnemy(Enemy& TutorialEnemy)
{
    //フラグがTRUEのときは上に移動する
    if (TutorialEnemy.changeMoveFlag == true)
    {
        TutorialEnemy.y1 += TutorialEnemy.speed * 2;
        TutorialEnemy.y2 += TutorialEnemy.speed * 2;
    }
    else
    {
        TutorialEnemy.y1 -= TutorialEnemy.speed * 2;
        TutorialEnemy.y2 -= TutorialEnemy.speed * 2;
    }

    //押し戻り処理＋移動方向の反転
    if (TutorialEnemy.y2 > 1000)
    {
        TutorialEnemy.y1 = 1000 - 100;
        TutorialEnemy.y2 = 1000;
        TutorialEnemy.changeMoveFlag = false;
    }
    else if (TutorialEnemy.y1 < 0)
    {
        TutorialEnemy.y1 = 0;
        TutorialEnemy.y2 = 100;
        TutorialEnemy.changeMoveFlag = true;
    }
}

//チュートリアル敵の描画
void DrawTutorialEnemy(Enemy& TutorialEnemy)
{
    DrawExtendGraph(TutorialEnemy.x2, TutorialEnemy.y1,TutorialEnemy.x1,TutorialEnemy.y2, TutorialEnemy.graph, TRUE);
}