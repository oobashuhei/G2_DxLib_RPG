#include "DxLib.h"

#define GAME_WIDTH		640	//画面の横の大きさ
#define GAME_HEIGHT		480	//画面の縦の大きさ
#define GAME_COLOR		32	//画面のカラーピット

#define GAME_WINDOW_BAR		0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"Dxlib_Movie"	//ウィンドウのタイトル

//MOVIEフォルダと、mp4ファイルも追加してください
#define MOVIE_PATH  ".\\MOVIE\\srn.mp4"	//動画パス

//動画のハンドル
int handle = -1;

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//log.txtを出力しない
	//log.txtは一回一回出力するからいらないかも？
	ChangeWindowMode(TRUE);								//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値はウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);				//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);								//非アクティブでも実行する

	//DXLib初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//動画の読み込み
	handle = LoadGraph(MOVIE_PATH);

	//無限ループ
	while (TRUE)
	{
		//メッセージ処理の結果がエラーのとき、強制終了
		if (ProcessMessage() != 0)
		{
			break;
		}

		//画面を消去できなかったとき、強制終了
		if (ClearDrawScreen() != 0)
		{
			break;
		}

		if (GetMovieStateToGraph(handle) == 0)
		{
			SeekMovieToGraph(handle, 0);	//動画の再生バーを最初にする
			PlayMovieToGraph(handle);		//動画を再生状態にする

			//動画の音を調整する(0が無音～255が動画の音量)
			ChangeMovieVolumeToGraph(127, handle);
		}

		//タイトル動画描画
		//DrawGraph(0, 0, handle, FALSE);

		//動画サイズを同じにする(処理遅いかも)
		DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, handle, FALSE);

		DrawString(0, 0, "動画を再生しています・・・", GetColor(255, 255, 255));
		DrawString(0, 20, "ソ連国家の動画", GetColor(255, 255, 255));

		//モニタのリフレッシュレ0との速さで裏画面を再描画
		ScreenFlip();
	}

	//DXライブラリ使用の終了処理
	DxLib_End();

	//動画の削除
	DeleteGraph(handle);

	return 0;
}
