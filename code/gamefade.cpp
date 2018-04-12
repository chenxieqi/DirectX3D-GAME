
// ゲーム開始または終わり時のカウントダウン
// ======================================

#include "gamefade.h"

static bool g_start;	// ゲーム開始フラグ
static int g_timer;		// ウントダウンの時間
static bool g_timeUp;	// ゲーム終了フラグ

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------
void InitGameFade(void)
{
	g_start = false;
	g_start = 0;
	g_timeUp = false;
}
void UninitGameFade(void)
{

}
void UpdateGameFade(void)
{
	if (g_start || g_timeUp)
	{
		g_timer++;
	}
	if (g_start)
	{
		if (g_timer == 60 || g_timer == 120 || g_timer == 180)
		{
			PlaySound(SOUND_LABEL_SE_BI);
		}
		if (g_timer == 240)
		{
			PlaySound(SOUND_LABEL_SE_PI);
		}
	}
}
void DrawGameFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	if (g_start)
	{
		if (g_timer < 120)
		{
			ScoreDraw(3, 1, (SCREEN_WIDTH - NUMBER_WIDTH)*0.5f, (SCREEN_HEIGHT - NUMBER_HEIGHT)*0.5f, false);
		}
		else if (g_timer <= 180)
		{
			ScoreDraw(2, 1, (SCREEN_WIDTH - NUMBER_WIDTH)*0.5f, (SCREEN_HEIGHT - NUMBER_HEIGHT)*0.5f, false);
		}
		else if (g_timer <= 240)
		{
			ScoreDraw(1, 1, (SCREEN_WIDTH - NUMBER_WIDTH)*0.5f, (SCREEN_HEIGHT - NUMBER_HEIGHT)*0.5f, false);
		}
		else if (g_timer <= 300)
		{
			SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
			SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
			PolygonDraw(T_WHITE_BAR, 0, (SCREEN_HEIGHT - BAR_HEIGHT)*0.5f, (float)BAR_WIDTH, (float)BAR_HEIGHT, BAR_WIDTH, BAR_HEIGHT, 0, 0, BAR_WIDTH, BAR_HEIGHT, false);
			PolygonDraw(T_START, (SCREEN_WIDTH - START_WIDTH)*0.5f, (SCREEN_HEIGHT - START_HEIGHT)*0.5f, (float)START_WIDTH, (float)START_HEIGHT, START_WIDTH, START_HEIGHT, 0, 0, START_WIDTH, START_HEIGHT, false);
		}
		else
		{
			g_start = false;
			g_timer = 0;
			InitTimer();
			GameNow();
		}
	}


	if (g_timeUp)
	{
		if (g_timer < 60)
		{
			ScoreDraw(3, 1, (SCREEN_WIDTH - NUMBER_WIDTH)*0.5f, (SCREEN_HEIGHT - NUMBER_HEIGHT)*0.5f, false);
		}
		else if (g_timer <= 120)
		{
			ScoreDraw(2, 1, (SCREEN_WIDTH - NUMBER_WIDTH)*0.5f, (SCREEN_HEIGHT - NUMBER_HEIGHT)*0.5f, false);
		}
		else if (g_timer <= 180)
		{
			ScoreDraw(1, 1, (SCREEN_WIDTH - NUMBER_WIDTH)*0.5f, (SCREEN_HEIGHT - NUMBER_HEIGHT)*0.5f, false);
		}
		else if (g_timer <= 240)
		{
			SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
			SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
			PolygonDraw(T_WHITE_BAR, 0, (SCREEN_HEIGHT - BAR_HEIGHT)*0.5f, (float)BAR_WIDTH, (float)BAR_HEIGHT, BAR_WIDTH, BAR_HEIGHT, 0, 0, BAR_WIDTH, BAR_HEIGHT, false);
			PolygonDraw(T_TIMEUP, (SCREEN_WIDTH - TIMEUP_WIDTH)*0.5f, (SCREEN_HEIGHT - TIMEUP_HEIGHT)*0.5f, (float)TIMEUP_WIDTH, (float)TIMEUP_HEIGHT, TIMEUP_WIDTH, TIMEUP_HEIGHT, 0, 0, TIMEUP_WIDTH, TIMEUP_HEIGHT, false);
		}
		else 
		{
			g_timeUp = false;
			GameOver();
			GameNotNow();
		}
	}

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

// ゲーム開始
void SetStart()
{
	g_start = true;
}

// ゲーム終了
void SetTimeUp()
{
	g_timeUp = true;
}

// -------------------------------------------------------------
//  ゲット用関数
// -------------------------------------------------------------

// カウントダウンしてるか
const bool GetGameFade()
{
	if ((g_start&&g_timer < 240)||(g_timeUp&&g_timer>180))
	{
		return g_start || g_timeUp;
	}
	else {
		return false;
	}
}