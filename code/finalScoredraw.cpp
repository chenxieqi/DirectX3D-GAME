
// �G���f�B���O�̎��`���X�R�A
// ======================================

#include "finalScoredraw.h"

static int g_score;		// �X�R�A
static int g_number[900];
static int g_cnt;


// -------------------------------------------------------------
//  ��{�֐�
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

// �X�R�A�`�揈���i�X�R�A�A���炢�A�`����W�A�[�����ǂ����j
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
//  �Q�b�g�p�֐�
// -------------------------------------------------------------

// �Q�b�g�X�R�A
const int GetFinalScore() {
	return g_score;
}