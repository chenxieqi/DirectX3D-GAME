
//---------”Žš‚ð•`‰æ‚·‚é-----------------------

#include "number.h"
#include "Polygon.h"

// ”Žš‚ð•`‰æi”ŽšAÀ•Wj
void DrawNumber(int n, float x, float y) {
	int nPattern;
	nPattern = n;
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ‰ÁŽZ‡¬‚ÌÝ’è
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
	SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	SetPolygonRotation(0.0f, 0.0f, 0);
	PolygonDraw(T_NUMBER, x, y, (float)NUMBER_WIDTH - 0.5f, (float)NUMBER_HEIGHT - 0.5f, 250, 50, NUMBER_WIDTH * nPattern, 0, NUMBER_WIDTH, NUMBER_HEIGHT, true);

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}