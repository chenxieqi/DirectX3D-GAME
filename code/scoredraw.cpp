//--------------------スコア描画---------------------

#include "scoredraw.h"
#include "Polygon.h"
#include "number.h"

static int g_score;		// スコア

// スコア描画処理（スコア、くらい、描画座標、ゼロかどうか）
void ScoreDraw(int score, int dig, float x, float y, bool bZero)
{
	int num;
	g_score = score;

	if (score > 99999999) {
		for (int i = 0; i < dig; i++) {
			DrawNumber(9, x, y);
			x = x - float(NUMBER_WIDTH) * 2;
		}
	}
	else {
		for (int i = 0; i < dig; i++) {
			num = score % 10;
			DrawNumber(num, x, y);
			x = x - float(NUMBER_WIDTH) * 2;
			score = score / 10;
		}
	}
}

// ゲットスコア
int GetScore() {
	return g_score;
}