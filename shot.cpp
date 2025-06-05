#include"Dxlib.h"
#include"shot.h"
#include"enemy.h"
#include"player.h"
#include<math.h>

//チュートリアル弾初期化
void InitializeTutorialBullet(Bullet& TutorialBullet)
{
    //画像読み込み
    TutorialBullet.graph = LoadGraph("img/tama1.png");

    //弾の存在フラグをfalseにする
    TutorialBullet.isInScreenFlag = false;
}

//チュートリアル弾ルーチン
void UpdateTutorialBullet(Bullet& TutorialBullet,Enemy& TutorialEnemy)
{
    //弾の発射
    if (!TutorialBullet.isInScreenFlag)
    {
        TutorialBullet.isInScreenFlag = true;
        TutorialBullet.x1 = TutorialEnemy.x1 - 50;
        TutorialBullet.x2 = TutorialEnemy.x1;
        TutorialBullet.y1 = TutorialEnemy.y1 + 25;
        TutorialBullet.y2 = TutorialEnemy.y2 - 25;
    }

    //弾の移動
    if (TutorialBullet.isInScreenFlag)
    {
        TutorialBullet.x1 -= TutorialBullet.enemySpeed;
        TutorialBullet.x2 -= TutorialBullet.enemySpeed;
        //弾が画面外に出たら消す
        if (TutorialBullet.x1 < 0)
        {
            TutorialBullet.isInScreenFlag = false;
        }
    }
}

//チュートリアル弾描画
void DrawTutorialBullet(Bullet& TutorialBullet)
{
    //フラグがtrueのときに弾を描画
    if (TutorialBullet.isInScreenFlag)
    {
        DrawExtendGraph(TutorialBullet.x2, TutorialBullet.y1, TutorialBullet.x1, TutorialBullet.y2, TutorialBullet.graph, TRUE);
    }
}

//プレイヤー弾初期化
void InitializePlayerBullet(Bullet PlayerBullet[],int PlayerShotNumber, Player& player1)
{
    //1回だけ画像を読み込み
    int tama2Graph = LoadGraph("img/tama2.png");

    for (int i = 0; i < PlayerShotNumber; i++)
    {
        //画像を代入
        PlayerBullet[i].graph = tama2Graph;

        //弾のフラグをfalse(画面内に存在しない状態)にする
        PlayerBullet[i].isInScreenFlag = false;   
    }

    //ショットボタンが前フレームで押されたかどうかを保存する変数にfalse(押されていない状態)を代入
    player1.PrevShotFlag = false;
}

//プレイヤー弾ルーチン
void UpdatePlayerBullet(Bullet PlayerBullet[], int PlayerShotNumber , Player& player1, DINPUT_JOYSTATE input, int shotSound,int& remainingBullet)
{
    //コントローラーの入力状態を取得
    GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

    //RBボタンを押したときに射撃する
    if (input.Buttons[5] > 0 && remainingBullet > 0 || input.Buttons[7] > 0 && remainingBullet > 0)
    {
        //前フレームでショットボタンを押したかのフラグがfalseだったら弾を発射
        if (player1.PrevShotFlag == false)
        {
            //画面上に出てない弾があるか、弾の数だけ繰り返して調べる
            for (int i = 0; i < PlayerShotNumber; i++)
            {
                //弾iが画面上にでてない場合は弾を発射する
                if (!PlayerBullet[i].isInScreenFlag)
                {
                    //射撃効果音
                    PlaySoundMem(shotSound, DX_PLAYTYPE_BACK, TRUE);

                    //発射
                    PlayerBullet[i].x1 = player1.x + 100;
                    PlayerBullet[i].y1 = player1.y + 95;
                    PlayerBullet[i].x2 = PlayerBullet[i].x1 + 25;
                    PlayerBullet[i].y2 = PlayerBullet[i].y1 + 15;
                    PlayerBullet[i].isInScreenFlag = true;

                    //残弾数を減らす
                    remainingBullet--;

                    //一つの弾を発射したのでループから逃げる
                    break;
                }
            }
        }

        //前フレームでショットボタンを押されていたかのフラグにtrueを代入
        player1.PrevShotFlag = true;
    }
    else
    {
        //ショットボタンが押されていなかった場合はfalseを代入
        player1.PrevShotFlag = false;
    }

    for (int i = 0; i < PlayerShotNumber; i++)
    {
        //弾の移動
        PlayerBullet[i].x1 += PlayerBullet[i].playerSpeed;
        PlayerBullet[i].x2 += PlayerBullet[i].playerSpeed;
    }
}    

//プレイヤー弾描画
void DrawPlayerBullet(Bullet PlayerBullet[],int PlayerShotNumber)
{
    for (int i = 0; i < PlayerShotNumber; i++)
    {
        if (PlayerBullet[i].isInScreenFlag)
        {
            //描画
            DrawExtendGraph(PlayerBullet[i].x1, PlayerBullet[i].y1, PlayerBullet[i].x2, PlayerBullet[i].y2, PlayerBullet[i].graph, TRUE);
        }
    }
}

//ジグザグ敵弾アウェイク（1回だけ呼べばいい処理をここに書く）
void AwakeZigzagEnemyBullet(Bullet& zigzagEnemyBullet)
{
    //画像読み込み
    zigzagEnemyBullet.graph = LoadGraph("img/tama1.png");
    //弾の存在フラグをflaseにする
    zigzagEnemyBullet.isInScreenFlag = false;
}

//ジグザグ敵弾初期化
void InitializeZigzagEnemyBullet(Bullet& zigzagEnemyBullet, Enemy& zigzagEnemy)
{
    //ジグザグ敵が生きていたら弾を発射
    if (zigzagEnemy.isInScreenFlag)
    {
        //存在フラグをtrueにする
        zigzagEnemyBullet.isInScreenFlag = true;

        if (zigzagEnemy.x1 == 1300 || zigzagEnemy.x1 == 1000 || zigzagEnemy.x1 == 700)
        {
            zigzagEnemyBullet.x1 = zigzagEnemy.x1 - 50;
            zigzagEnemyBullet.x2 = zigzagEnemyBullet.x1 + 50;
            zigzagEnemyBullet.y1 = zigzagEnemy.y1 + 35;
            zigzagEnemyBullet.y2 = zigzagEnemy.y1 + 60;
        }
    }
}

//ジグザグ敵弾ルーチン
void UpdateZigzagEnemyBullet(Bullet& zigzagEnemyBullet)
{  
    if (zigzagEnemyBullet.isInScreenFlag)
    {
        //弾の移動
        zigzagEnemyBullet.x1 -= zigzagEnemyBullet.enemySpeed;
        zigzagEnemyBullet.x2 -= zigzagEnemyBullet.enemySpeed;
    }

    //弾が画面外に出たら消す
    if (zigzagEnemyBullet.x1 < 0)
    {
        zigzagEnemyBullet.isInScreenFlag = false;
    }  
}

//ジグザグ敵弾描画
void DrawZigzagEnemyBullet(Bullet& zigzagEnemyBullet)
{
    if (zigzagEnemyBullet.isInScreenFlag)
    {
        DrawExtendGraph(zigzagEnemyBullet.x2, zigzagEnemyBullet.y1, zigzagEnemyBullet.x1, zigzagEnemyBullet.y2, zigzagEnemyBullet.graph, TRUE);
    }
}

//うちまくる敵弾アウェイク
void AwakeShootingEnemyBullet(Bullet& shootingEnemyBullet)
{
    //画像読み込み
    shootingEnemyBullet.graph = LoadGraph("img/tama3.png");

    //存在フラグをfalseにする
    shootingEnemyBullet.isInScreenFlag = false;
}

//うちまくる敵弾初期化
void InitializeShootingEnemyBullet(Bullet& shootingEnemyBullet, Enemy& shootingEnemy,Player& player1)
{
    //うちまくる敵が生きていたら
    if (shootingEnemy.isInScreenFlag)
    {
        //存在フラグをtrueにする
        shootingEnemyBullet.isInScreenFlag = true;

        //発射した時の座標
        shootingEnemyBullet.x1 = shootingEnemy.x1 - width;
        shootingEnemyBullet.x2 = shootingEnemyBullet.x1 + width;
        shootingEnemyBullet.y1 = shootingEnemy.y1 + IniShotPositionY;
        shootingEnemyBullet.y2 = shootingEnemyBullet.y1 + height;

        //座標参照弾の計算
        shootingEnemyBullet.sbx = player1.x - shootingEnemyBullet.x1;
        shootingEnemyBullet.sby = player1.y - shootingEnemyBullet.y1;

        // 平方根を求めるのに標準関数の sqrt を使う、
        // これを使うには math.h をインクルードする必要がある
        shootingEnemyBullet.sb = sqrt(shootingEnemyBullet.sbx * shootingEnemyBullet.sbx + shootingEnemyBullet.sby * shootingEnemyBullet.sby);

        // 移動速度
        shootingEnemyBullet.coordinateReferenceXSpeed = shootingEnemyBullet.sbx / shootingEnemyBulletSpeed;
        shootingEnemyBullet.coordinateReferenceYSpeed = shootingEnemyBullet.sby / shootingEnemyBulletSpeed;
    }
}

//うちまくる敵弾ルーチン
void UpdateShootingEnemyBullet(Bullet& shootingEnemyBullet)
{
    //移動
    if (shootingEnemyBullet.isInScreenFlag)
    {
        shootingEnemyBullet.x1 += shootingEnemyBullet.coordinateReferenceXSpeed;
        shootingEnemyBullet.x2 = shootingEnemyBullet.x1 + width;
        shootingEnemyBullet.y1 += shootingEnemyBullet.coordinateReferenceYSpeed;
        shootingEnemyBullet.y2 = shootingEnemyBullet.y1 + height;
    }

    //画面外に出たら消す
    if (shootingEnemyBullet.x2 < zero || shootingEnemyBullet.y1 <= zero || shootingEnemyBullet.y1 > senn)
    {
        shootingEnemyBullet.isInScreenFlag = false;
    }
}

//うちまくる敵弾描画
void DrawShootingEnemyBullet(Bullet& shootingEnemyBullet)
{
    if (shootingEnemyBullet.isInScreenFlag)
    {
        DrawExtendGraph(shootingEnemyBullet.x2, shootingEnemyBullet.y1, shootingEnemyBullet.x1, shootingEnemyBullet.y2, shootingEnemyBullet.graph, TRUE);
    }
}