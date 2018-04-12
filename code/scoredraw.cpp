//--------------------�X�R�A�`��---------------------

#include "scoredraw.h"
#include "Polygon.h"
#include "number.h"

static int g_score;		// �X�R�A

// �X�R�A�`�揈���i�X�R�A�A���炢�A�`����W�A�[�����ǂ����j
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

// �Q�b�g�X�R�A
int GetScore() {
	return g_score;
}