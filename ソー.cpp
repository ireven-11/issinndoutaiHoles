#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	XINPUT_STATE input;
	int i;
	int Color;

	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0) return -1;

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// メインループ(何かキーが押されたらループを抜ける)
	while (ProcessMessage() == 0)
	{
		// 画面のクリア
		ClearDrawScreen();

		// 入力状態を取得
		GetJoypadXInputState(DX_INPUT_PAD1, &input);

		// 画面に XINPUT_STATE の中身を描画
		Color = GetColor(255, 255, 255);
		DrawFormatString(0, 0, Color, "LeftTrigger:%d RightTrigger:%d",
			input.LeftTrigger, input.RightTrigger);
		DrawFormatString(0, 16, Color, "ThumbLX:%d ThumbLY:%d",
			input.ThumbLX, input.ThumbLY);
		DrawFormatString(0, 32, Color, "ThumbRX:%d ThumbRY:%d",
			input.ThumbRX, input.ThumbRY);
		DrawString(0, 64, "Button", Color);
		for (i = 0; i < 16; i++)
		{
			DrawFormatString(64 + i % 8 * 64, 64 + i / 8 * 16, Color,
				"%2d:%d", i, input.Buttons[i]);
		}

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}