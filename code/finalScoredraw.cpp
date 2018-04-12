
// エンディングの時描くスコア
// ======================================

#include "finalScoredraw.h"

static int g_score;		// スコア
static int g_number[900];
static int g_cnt;


// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

void InitFinalScore()
{
	for (int i = 0; i < 900; i++) {
		int num = rand() % 10;
		g_number[i] = num;
	}
	g_cnt = 0;
}

void UninitFinalScore()
{

}

void UpdateFinalScore()
{
	if (g_cnt < 900)
	{
		g_cnt++;
	}
	else {
		g_cnt = 900;
	}

}

// スコア描画処理（スコア、くらい、描画座標、ゼロかどうか）
void DrawFinalScore(int score, int dig, float x, float y, bool bZero)
{
	int num;
	g_score = score;

	int dig_cnt = g_cnt / 100;


	if (score > 9999999) {
		for (int i = 0; i < 7; i++) {
			DrawNumber(9, x, y);
			x = x - float(NUMBER_WIDTH) * 2;
		}
	}
	else {
		for (int i = 0; i < 7; i++) {

			if (i < dig_cnt&&i<dig)
			{
				num = score % 10;
				score = score / 10;
				DrawNumber(num, x, y);
			}
			if (i >= dig_cnt&&dig_cnt<dig)
			{
				DrawNumber(g_number[g_cnt], x, y);
			}
			x = x - float(NUMBER_WIDTH) * 2;
		}
	}
}

// -------------------------------------------------------------
//  ゲット用関数
// -------------------------------------------------------------

// ゲットスコア
const int GetFinalScore() {
	return g_score;
}