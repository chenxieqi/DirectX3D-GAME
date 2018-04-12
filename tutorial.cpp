
// チュートリアル
// ======================================

#include"tutorial.h"

#define MAX_PAGE	(2)

// チュートリアルページ数
static int g_page;

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

// InitTutorial
void InitTutorial(void)
{
	g_page = 0;
}

// UninitTutorial
void UninitTutorial(void)
{
}

// UpdateTutorial
void UpdateTutorial(void)
{
	if (GetKeyboardTrigger(DIK_RETURN)) {
		g_page++;
		PlaySound(SOUND_LABEL_SE_OK);
		if (g_page >= MAX_PAGE)
		{
			CreatFade();
		}
	}
	UpdateBackground();
}

// DrawTutorial
void DrawTutorial(void)
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

	SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
	SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	if (g_page == 0)
	{
		PolygonDraw(T_TUTORIAL, 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	}
	else {
		PolygonDraw(T_TUTORIAL1, 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	}

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

