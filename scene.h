#pragma once

//—ñ‹“‘Ì
enum
{
	TITLE,
	EXPLANE,
	PLAY,
	OVER,
	PAUSE
};

struct Player;
struct Enemy;

void pauseScene(bool& startPauseFlag, int& BrinkCounter, int pauseScreenHandle, int FontSize100, int FontSize50, int bgm, int& startVideoCount, bool finishPauseFlag, int startPauseSound, int initialWIDTH, int HEIGHT, int& selectscene, DINPUT_JOYSTATE input, int warningSound);
void gameOverScene(bool& overSoundFlag, int overSound, int& BrinkCounter, int initialWIDTH, int HEIGHT, int FontSize50, int FontSize100, int& score, int& scoreMagnificatoin, int& startVideoCount, int FontSize300, int& selectscene);
void clearScene(Player& player1, int initialWIDTH, Player& player2, int& BrinkCounter, int shotSound, int HEIGHT, int FontSize300, int FontSize30, bool& clearSoundFlag, int& score, int FontSize100, int& scoreMagnificatoin, int& damage, int& startVideoCount, int& selectscene, int suctionSound, int bgm, int clearSound, int FontSize50);
void proceedPause();