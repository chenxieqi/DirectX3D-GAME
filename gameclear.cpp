
// ゲームクリアした時のアニメーション描画
// ======================================

#include "gameclear.h"

#define LIMIT	(50)		// 爆発範囲
#define CLEAR_WIDTH		(600)
#define CLEAR_HEIGHT	(123)

static int g_timer;
static bool g_gameclear;


// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

void InitGameClear(void)
{
	g_timer=0;
	g_gameclear = false;
}
void UninitGameClear(void)
{
	
}
void UpdateGameClear(bool gameclear)
{
	g_gameclear = gameclear;

	if (g_timer > 350)
	{
		if (GetKeyboardTrigger(DIK_RETURN)) {
			PlaySound(SOUND_LABEL_SE_OK);
			CreatFade();
		}
	}

	D3DXVECTOR3 vec;
	float x, y, z;

	x = rand() % (LIMIT * 2 )-LIMIT;
	y = rand() % (LIMIT * 2 )-LIMIT;
	z = 0;
	vec = D3DXVECTOR3(x, y, z);
	if (g_timer % 20 == 0)
	{
		CreateExplosion(vec, 4, 4, TEXTURE_EX1);
	}
	g_timer++;

}
void DrawGameClear(void)
{
	if (g_gameclear)
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

		SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
		SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));

		if (g_timer > 300)
		{
			PolygonDraw(T_GAMECLEAR, 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, false);
		}
		else {
			// Draw CLEAR
			StopSound();
			PolygonDraw(T_WHITE_BAR, 0, (SCREEN_HEIGHT - BAR_HEIGHT)*0.5f, (float)BAR_WIDTH, (float)BAR_HEIGHT, BAR_WIDTH, BAR_HEIGHT, 0, 0, BAR_WIDTH, BAR_HEIGHT, false);
			PolygonDraw(T_CLEAR, (SCREEN_WIDTH - CLEAR_WIDTH)*0.5f, (SCREEN_HEIGHT - CLEAR_HEIGHT)*0.5f, (float)CLEAR_WIDTH, (float)CLEAR_HEIGHT, CLEAR_WIDTH, CLEAR_HEIGHT, 0, 0, CLEAR_WIDTH, CLEAR_HEIGHT, false);
		}
		pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}