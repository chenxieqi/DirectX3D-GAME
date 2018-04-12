
// 地面判定範囲ーデバッグ用
// ======================================

#include "grid.h"

// 頂点構造体の宣言
typedef struct
{
	D3DXVECTOR3 pos;	// 3D
	D3DCOLOR color;
}VERTEX_GRID;

// FVFの宣言(定数)
#define FVF_VERTEX3D		(D3DFVF_XYZ|D3DFVF_DIFFUSE)
#define MAX_GRID			(72)

static D3DXMATRIX g_mtxGrid;

VERTEX_GRID grid[MAX_GRID];

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

void InitGrid(void) 
{
	int degree = 0;
	for (int i = 0; i < MAX_GRID; i++)
	{
		grid[i].pos.x = cosf(D3DXToRadian(degree))*FLOOR_L_R;
		grid[i].pos.z = sinf(D3DXToRadian(degree))*FLOOR_L_R;
		grid[i].pos.y = 0;
		grid[i].color= D3DCOLOR_RGBA(255, 0, 255, 255);

		degree += 10;
	}

}
void UninitGrid(void) {

}
void UpdateGrid(void) {
	// ワールド変換行列
	// 何もしない（単位行列）
	D3DXMatrixIdentity(&g_mtxGrid);

}
void DrawGrid(void) {

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	
	// FVF設定
	pDevice->SetFVF(FVF_VERTEX3D);



	// 各種行列の設定--状況による設定する
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxGrid);


	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 71, &grid[0], sizeof(VERTEX_GRID));

}