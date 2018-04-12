
// �Q�[���V�[����UI
// ======================================

#include "mainUI.h"

#define GAME_TIME	(3)

static float life_x;				 // �v���C���[���C�t
static float life_boss_x;			 // BOSS���C�t
static float energe_y;				 // �v���C���[�G�l���M�[
static DWORD g_time;				 // �^�C��
static int g_secondTime;			 // ��
static int g_minuteTime;			 // �b
static DWORD g_startTime;			 // �J�n����
static bool g_count;				 // �J�E���g���Ă邩
static bool g_pastPause;			 // �|�[�Y���Ă邩�@
static DWORD g_pauseStartTime;		 // �|�[�Y�J�n����
static DWORD g_pauseEndTime;		 // �|�[�Y�I��莞��
static DWORD g_pauseTime;			 // �|�[�Y����
static DWORD g_pausedTime;			 // �|�[�Y��������

// -------------------------------------------------------------
//  �^�C�}�[
// -------------------------------------------------------------

void InitTimer()
{
	g_startTime = timeGetTime();
	g_count = true;
	g_pauseStartTime = 0;
	g_pauseEndTime = 0;
	g_pauseTime = 0;
	g_pausedTime = 0;
	g_secondTime = 0;
	g_minuteTime = 0;
}

void UpdatePauseTimer()
{
	bool pause = IfPause();
	if (pause)
	{
		if (!g_pastPause) { g_pastPause = true; g_pauseStartTime = timeGetTime(); }
	}
	else {
		if (g_pastPause)
		{
			g_pauseEndTime = timeGetTime();
			g_pauseTime = g_pauseEndTime - g_pauseStartTime;
			g_pausedTime += g_pauseTime;
			g_pauseTime = 0;
			g_pauseStartTime = 0;
			g_pastPause = false;
		}
	}
}

void UpdateTimer()
{
	
	if (g_count)
	{
		DWORD nowTime = 0;
		nowTime=timeGetTime() - g_pausedTime;
		g_time = (nowTime - g_startTime)*0.01f;
		g_secondTime = 59 - (g_time / 10) % 60;
		g_minuteTime = (GAME_TIME - 1) - g_time / 600;
		if (g_minuteTime <= 0 || g_minuteTime >= 9)
		{
			g_minuteTime = 0;
		}
	}
	if (g_minuteTime == 0 && g_secondTime == 3)
	{
		SetTimeUp();
	}
	if (g_minuteTime == 0 && g_secondTime == 0)
	{
		g_count = false;
	}

}

// -------------------------------------------------------------
//  �Q�[���V�[����UI�i�^�C�}�[�`��܂߁j
// -------------------------------------------------------------

void UpdateMainUI()
{
	life_x = (int)GetPlayerLife()*0.01f;
	life_boss_x = (int)GetEnemyLife()*0.002f;
	energe_y = 1.0f-(int)GetPLayerEnerge()*0.02f;
}

void DrawMainUI() 
{
	int score = GetPlayerScoreInc();

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	// Draw Energe
	SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
	SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	PolygonDraw(T_ENERGE, 1078, 608+ ENERGE_HEIGHT*energe_y, (float)ENERGE_WIDTH, (float)ENERGE_HEIGHT- ENERGE_HEIGHT*energe_y, ENERGE_WIDTH, ENERGE_HEIGHT, 0, ENERGE_HEIGHT*energe_y, ENERGE_WIDTH, ENERGE_HEIGHT- ENERGE_HEIGHT*energe_y, false);


	// Draw HP
	SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
	SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	if (life_x < 0.25)
	{
		SetPolygonColor(D3DCOLOR_RGBA(255, 0, 0, 255));
	}
	PolygonDraw(T_HP, 125, 730, (float)HP_WIDTH*life_x, (float)HP_HEIGHT, HP_WIDTH, HP_HEIGHT, 0, 0, HP_WIDTH, HP_HEIGHT, false);

	// Draw Boss HP
	PolygonDraw(T_BOSS_HP, 150, 150, (float)BOSS_HP_WIDTH*life_boss_x, (float)BOSS_HP_HEIGHT, BOSS_HP_WIDTH, BOSS_HP_HEIGHT, 0, 0, BOSS_HP_WIDTH, BOSS_HP_HEIGHT, false);

	// Draw UI
	SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
	SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	PolygonDraw(T_UI, 0, 0, (float)UI_WIDTH , (float)UI_HEIGHT, UI_WIDTH, UI_HEIGHT,0, 0, UI_WIDTH, UI_HEIGHT, false);

	// Draw Timer
	ScoreDraw(g_minuteTime, 2, 580, 30, false);
	ScoreDraw(g_secondTime, 2, 680, 30, false);

	//Draw Score
	ScoreDraw(score, 6, 1200, 30, false);


	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
