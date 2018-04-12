
// ステンシルシャドウ
// ======================================

#include "shadow.h"


static D3DXMATRIX g_MatShadow_Player;
static D3DXMATRIX g_MatShadow_Enemy;
static D3DXMATRIX g_MatPlayer;
static D3DXMATRIX g_MatEnemy;
static D3DXVECTOR4 g_VecLight;
static D3DXPLANE g_Plane;

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

void InitShadow()
{
	g_MatShadow_Player = D3DXMATRIX(
		1.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.01f,0.0f,1.0f
		);
	g_MatShadow_Enemy = D3DXMATRIX(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.01f, 0.0f, 1.0f
	);
	D3DXPlaneFromPointNormal(&g_Plane, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}
void UninitShadow()
{
}
void UpdateShadow()
{
	g_VecLight = D3DXVECTOR4(-GetLightVec().x, -GetLightVec().y, -GetLightVec().z,0);
	D3DXMatrixShadow(&g_MatShadow_Player, &g_VecLight, &g_Plane);
	D3DXMatrixShadow(&g_MatShadow_Enemy, &g_VecLight, &g_Plane);
}
void DrawShadow()
{
	g_MatPlayer = GetPlayerMtx();
	g_MatEnemy = GetEnemyMtx();

	g_MatShadow_Player = g_MatPlayer*g_MatShadow_Player;
	g_MatShadow_Player._12 =
		g_MatShadow_Player._22 =
		g_MatShadow_Player._32 = 0.0f;
	g_MatShadow_Player._42 = 0.0f;

	g_MatShadow_Enemy = g_MatEnemy*g_MatShadow_Enemy;
	g_MatShadow_Enemy._12 =
		g_MatShadow_Enemy._22 =
		g_MatShadow_Enemy._32 = 0.0f;
	g_MatShadow_Enemy._42 = 0.0f;

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	
	SetMask();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	DrawXmodel(g_MatShadow_Player,0, XMODEL_PLAYER);
	DrawXmodel(g_MatShadow_Enemy, 0, XMODEL_ENEMY);
	StencilClear();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

}

