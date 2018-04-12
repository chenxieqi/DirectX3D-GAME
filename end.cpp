
// エンディング
// ======================================

// インクルードファイル

#include "end.h"

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

// InitEnd
void InitEnd(void)
{

}

// UninitEnd
void UninitEnd(void)
{
}

// UpdateEnd
void UpdateEnd(void)
{
	if (GetKeyboardTrigger(DIK_RETURN)) {
		PlaySound(SOUND_LABEL_SE_OK);
		CreatFade();
	}
	UpdateBackground();
}

// DrawEnd
void DrawEnd(void)
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
	PolygonDraw(T_END, 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, false);


	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

