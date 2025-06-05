#pragma once

//定数宣言
const int HEIGHT = 1000;       //画面の高さ
const int initialWIDTH = 1925; //初期画面の幅
const int WIDTH = 11000;       //背景1枚の幅
const int scrollspeed = 4;	   //スクロールスピード
const int wave1 = 3000;	       //ウェーブ１の終わり
const int wave2 = 7000;	       //ウェーブ２の終わり
const int wave3 = 14000;	   //ウェーブ3の終わり
const int wave4 = 21000;	   //ウェーブ4の終わり
const int IniBulletNumber = 30;//初級弾数
const int hyaku = 100;
const int sannbyaku = 300;

//変数宣言
int	   selectscene;     			                //シーン変化
Player player1;										//プレイヤー1の構造体変数
Player player2;										//プレイヤー２の構造体変数
Enemy  TutorialEnemy;								//チュートリアル敵の構造体変数
Bullet TutorialBullet;								//チュートリアル弾の構造体変数
Bullet PlayerBullet[PlayerShotNumber];				//プレイヤーの弾の構造体変数配列（弾は画面に[]内の数字までしかでない）
bool   countDown;       				            //カウントダウンフラグ
int	   scroll;				                        //スクロール変数
Enemy  zigzagEnemy[zigzagEnemyNumber];				//ジグザグ敵の構造体変数 ()は敵の数
Bullet zigzagEnemyBullet[zigzagEnemyShotNumber];	//ジグザグ敵弾の構造体変数
int    score;										//スコア
int    scoreMagnificatoin;							//スコア倍率
int    FontSize125;                                 //フォントサイズ125
int    FontSize50;                                  //フォントサイズ50
int    FontSize100;                                 //フォントサイズ100
int    FontSize300;                                 //フォントサイズ300
int    FontSize30;                                  //フォントサイズ30
int    pauseScreenHandle;							//ポーズ画面用スクリーンバッファ
bool   startPauseFlag;      				        //ポーズ画面開始フラグ
bool   finishPauseFlag;     			            //ポーズ画面終了フラグ
bool   clearSoundFlag;      				        //ゲームクリアサウンドフラグ
bool   overSoundFlag;       				        //ゲームオーバーサウンドフラグ
bool   tutorial1and2Flag;							//tutorial1and2フラグ
int    BrinkCounter;    				            //点滅カウンター
bool   tutorial3Flag;								//tutorial3フラグ
bool   tutorial4Flag;								//tutorial4フラグ
bool   shotFlag;									//ショットフラグ
int    shotCount;									//ショットカウント
bool   bgmFlag;										//bgmフラグ
int    remainingBullet;								//残弾
Enemy  straightEnemy[straightEnemyNumber];			//真っ直ぐ敵の構造体変数
Enemy  shootingEnemy[shootingEnemyNumber];			//うちまくる敵の構造体変数
Bullet shootingEnemyBullet[shootingEnemyShotNumber];//うちまくる敵の弾の構造体変数
Enemy  backEnemy[backEnemyNumber];					//後ろから敵の構造体変数
Enemy  raidEnemy[raidEnemyNumber];					//奇襲敵の構造体変数
int    blockGraph[3];								//ブロックの画像
int    blockHP[blockNumber];						//ブロックのHP
int    blockX1[blockNumber];						//ブロックの座標X1
int    blockX2[blockNumber];						//ブロックの座標X2
int	   blockY1[blockNumber];						//ブロックの座標Y1
int    blockY2[blockNumber];						//ブロックの座標Y2
bool   blockFlag[blockNumber];						//ブロックのフラグ
int    explosionEffect[11];							//爆発エフェクト画像
int	   suctionEffect[8];							//吸い込みエフェクト
int    suctionEffectCount;							//吸い込みカウント
int    skullEffect[15];								//どくろエフェクト
int    PrevBbuttonFlag;     			            //Bボタン押したフラグ
int    HPgraph[5];									//hp画像
int    damage;										//ダメージ
int    invincibleTimeCount;							//無敵時間カウント
bool   invincibleFlag;								//無敵フラグ
int    startVideoCount = 0;				            //動画が始まるまでのカウント
int    suctionSucceedEffect[11];					//吸い込み成功エフェクト
bool   suctionSucceedEffectFlag;        			//吸い込み成功エフェクトフラグ
int    suctionSucceedEffectCount;					//吸い込み成功エフェクトカウント
int    backGraph;				                    //プレイ背景
int    shotSound;			                        //射撃時効果音
int    startPauseSound;	                            //ポーズ画面開始効果音
int    finishPauseSound;	                        //ポーズ画面終了効果音
int    countDownSound;		                        //カウントダウン効果音
int    suctionSound;	                            //吸い込み効果音
int    clearSound;			                        //クリア時効果音
int    overSound;			                        //オーバー時効果音
int    succeedSuctionSound;                         //吸い込み成功効果音
int    playerDeathSound;	                        //敵か敵の攻撃に当たった瞬間
int    hanamaruGraph;			                    //花丸
int    correctSound;		                        //正解音
int    bgm;		                                    //bgm
int    remainingBulletGraph;			            //弾数絵
int    explosionSound;                              //爆発音読み込み
int    tutorialBack;				                //チュートリアル背景
int    rogo;                                        //ロゴ画像を読み込み
int    Lstick;                                      //Lスティック画像読み込み
int    Rstick;		                                //Rスティック画像読み込み
int    DemoMovie;	                                //デモムービー読み込み