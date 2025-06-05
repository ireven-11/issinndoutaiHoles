#pragma once

//�萔�錾
const int HEIGHT = 1000;       //��ʂ̍���
const int initialWIDTH = 1925; //������ʂ̕�
const int WIDTH = 11000;       //�w�i1���̕�
const int scrollspeed = 4;	   //�X�N���[���X�s�[�h
const int wave1 = 3000;	       //�E�F�[�u�P�̏I���
const int wave2 = 7000;	       //�E�F�[�u�Q�̏I���
const int wave3 = 14000;	   //�E�F�[�u3�̏I���
const int wave4 = 21000;	   //�E�F�[�u4�̏I���
const int IniBulletNumber = 30;//�����e��
const int hyaku = 100;
const int sannbyaku = 300;

//�ϐ��錾
int	   selectscene;     			                //�V�[���ω�
Player player1;										//�v���C���[1�̍\���̕ϐ�
Player player2;										//�v���C���[�Q�̍\���̕ϐ�
Enemy  TutorialEnemy;								//�`���[�g���A���G�̍\���̕ϐ�
Bullet TutorialBullet;								//�`���[�g���A���e�̍\���̕ϐ�
Bullet PlayerBullet[PlayerShotNumber];				//�v���C���[�̒e�̍\���̕ϐ��z��i�e�͉�ʂ�[]���̐����܂ł����łȂ��j
bool   countDown;       				            //�J�E���g�_�E���t���O
int	   scroll;				                        //�X�N���[���ϐ�
Enemy  zigzagEnemy[zigzagEnemyNumber];				//�W�O�U�O�G�̍\���̕ϐ� ()�͓G�̐�
Bullet zigzagEnemyBullet[zigzagEnemyShotNumber];	//�W�O�U�O�G�e�̍\���̕ϐ�
int    score;										//�X�R�A
int    scoreMagnificatoin;							//�X�R�A�{��
int    FontSize125;                                 //�t�H���g�T�C�Y125
int    FontSize50;                                  //�t�H���g�T�C�Y50
int    FontSize100;                                 //�t�H���g�T�C�Y100
int    FontSize300;                                 //�t�H���g�T�C�Y300
int    FontSize30;                                  //�t�H���g�T�C�Y30
int    pauseScreenHandle;							//�|�[�Y��ʗp�X�N���[���o�b�t�@
bool   startPauseFlag;      				        //�|�[�Y��ʊJ�n�t���O
bool   finishPauseFlag;     			            //�|�[�Y��ʏI���t���O
bool   clearSoundFlag;      				        //�Q�[���N���A�T�E���h�t���O
bool   overSoundFlag;       				        //�Q�[���I�[�o�[�T�E���h�t���O
bool   tutorial1and2Flag;							//tutorial1and2�t���O
int    BrinkCounter;    				            //�_�ŃJ�E���^�[
bool   tutorial3Flag;								//tutorial3�t���O
bool   tutorial4Flag;								//tutorial4�t���O
bool   shotFlag;									//�V���b�g�t���O
int    shotCount;									//�V���b�g�J�E���g
bool   bgmFlag;										//bgm�t���O
int    remainingBullet;								//�c�e
Enemy  straightEnemy[straightEnemyNumber];			//�^�������G�̍\���̕ϐ�
Enemy  shootingEnemy[shootingEnemyNumber];			//�����܂���G�̍\���̕ϐ�
Bullet shootingEnemyBullet[shootingEnemyShotNumber];//�����܂���G�̒e�̍\���̕ϐ�
Enemy  backEnemy[backEnemyNumber];					//��납��G�̍\���̕ϐ�
Enemy  raidEnemy[raidEnemyNumber];					//��P�G�̍\���̕ϐ�
int    blockGraph[3];								//�u���b�N�̉摜
int    blockHP[blockNumber];						//�u���b�N��HP
int    blockX1[blockNumber];						//�u���b�N�̍��WX1
int    blockX2[blockNumber];						//�u���b�N�̍��WX2
int	   blockY1[blockNumber];						//�u���b�N�̍��WY1
int    blockY2[blockNumber];						//�u���b�N�̍��WY2
bool   blockFlag[blockNumber];						//�u���b�N�̃t���O
int    explosionEffect[11];							//�����G�t�F�N�g�摜
int	   suctionEffect[8];							//�z�����݃G�t�F�N�g
int    suctionEffectCount;							//�z�����݃J�E���g
int    skullEffect[15];								//�ǂ���G�t�F�N�g
int    PrevBbuttonFlag;     			            //B�{�^���������t���O
int    HPgraph[5];									//hp�摜
int    damage;										//�_���[�W
int    invincibleTimeCount;							//���G���ԃJ�E���g
bool   invincibleFlag;								//���G�t���O
int    startVideoCount = 0;				            //���悪�n�܂�܂ł̃J�E���g
int    suctionSucceedEffect[11];					//�z�����ݐ����G�t�F�N�g
bool   suctionSucceedEffectFlag;        			//�z�����ݐ����G�t�F�N�g�t���O
int    suctionSucceedEffectCount;					//�z�����ݐ����G�t�F�N�g�J�E���g
int    backGraph;				                    //�v���C�w�i
int    shotSound;			                        //�ˌ������ʉ�
int    startPauseSound;	                            //�|�[�Y��ʊJ�n���ʉ�
int    finishPauseSound;	                        //�|�[�Y��ʏI�����ʉ�
int    countDownSound;		                        //�J�E���g�_�E�����ʉ�
int    suctionSound;	                            //�z�����݌��ʉ�
int    clearSound;			                        //�N���A�����ʉ�
int    overSound;			                        //�I�[�o�[�����ʉ�
int    succeedSuctionSound;                         //�z�����ݐ������ʉ�
int    playerDeathSound;	                        //�G���G�̍U���ɓ��������u��
int    hanamaruGraph;			                    //�Ԋ�
int    correctSound;		                        //������
int    bgm;		                                    //bgm
int    remainingBulletGraph;			            //�e���G
int    explosionSound;                              //�������ǂݍ���
int    tutorialBack;				                //�`���[�g���A���w�i
int    rogo;                                        //���S�摜��ǂݍ���
int    Lstick;                                      //L�X�e�B�b�N�摜�ǂݍ���
int    Rstick;		                                //R�X�e�B�b�N�摜�ǂݍ���
int    DemoMovie;	                                //�f�����[�r�[�ǂݍ���