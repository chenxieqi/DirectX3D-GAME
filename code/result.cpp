
// リザルト
// ======================================

#include "result.h"

// リザルト
#define GOOD		(19500)
#define GREAT		(26000)
#define EXCELLENT	(30000)

// スコア
#define SCORE_MAX	(33000)
#define SCORE_SPEED (50)

static int g_scoreInc;
static bool g_ScoreSound;

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

// InitResult
void InitResult(void)
{
	g_scoreInc = 0;
	g_ScoreSound = false;
	InitFinalScore();
}

// UninitResult
void UninitResult(void)
{
	UninitFinalScore();
}

// UpdateResult
void UpdateResult(void)
{


	UpdateBackground();
	int score = GetPlayerScore()+GetPlayerLife()*50;
	if (g_scoreInc < score- SCORE_SPEED)
	{
		g_scoreInc+= SCORE_SPEED;
	}
	if (g_scoreInc < score)
	{
		g_scoreInc +=5;
	}
	if (g_scoreInc >= score)
	{
		if (!g_ScoreSound) { StopSound(); PlaySound(SOUND_LABEL_SE_ONEPOINT); }
		g_ScoreSound = true;
		if (GetKeyboardTrigger(DIK_RETURN)) {
			PlaySound(SOUND_LABEL_SE_OK);
			CreatFade();
		}
	}
	UpdateFinalScore();
}

// DrawResult
void DrawResult(void)
{
	DrawBackground();
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	float score_percent = (float)g_scoreInc / SCORE_MAX;
	if (score_percent > 1)
	{
		score_percent = 1;
	}

	SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
	SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	PolygonDraw(T_SCOREBAR, 640, 100+(1-score_percent)*SCOREBAR_HEIGHT, (float)SCOREBAR_WIDTH, score_percent*SCOREBAR_HEIGHT, SCOREBAR_WIDTH, SCOREBAR_HEIGHT, 0, (1-score_percent)*SCOREBAR_HEIGHT, SCOREBAR_WIDTH, score_percent*SCOREBAR_HEIGHT, false);

	if (g_scoreInc < GOOD)
	{
		SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
		SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		PolygonDraw(T_RESULT0, 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	}
	else if (g_scoreInc < GREAT)
	{
		SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
		SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		PolygonDraw(T_RESULT1, 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	}
	else if (g_scoreInc < EXCELLENT)
	{
		SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
		SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		PolygonDraw(T_RESULT2, 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	}
	else {
		SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
		SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		PolygonDraw(T_RESULT3, 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	}

	int score = GetPlayerScore();
	int dig = log10(score) + 1;
	//Draw Score
	DrawFinalScore(score, dig, 1200, 30, false);

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
