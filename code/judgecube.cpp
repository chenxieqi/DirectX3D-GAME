
// 当たり判定の具現化キューブーデバッグ用
// ======================================

#include "judgecube.h"


// 頂点構造体の宣言
typedef struct
{
	D3DXVECTOR3 pos;	// 3D
	D3DCOLOR color;
}VERTEX_JUDEGCUBE;

// FVFの宣言(定数)
#define FVF_VERTEX3D		(D3DFVF_XYZ|D3DFVF_DIFFUSE)

static D3DXMATRIX g_mtx;

VERTEX_JUDEGCUBE cube[2][5];

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

void InitJudgecube()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cube[i][j].pos = D3DXVECTOR3(0, 0, 0);
			cube[i][j].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
	}
}
void UninitJudgecube()
{

}
void UpdateJudgecube()
{
	D3DXMatrixIdentity(&g_mtx);

}
void DrawJudgecube(D3DXMATRIX mtx)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// FVF設定
	pDevice->SetFVF(FVF_VERTEX3D);

	g_mtx = mtx;
	// 各種行列の設定--状況による設定する
	pDevice->SetTransform(D3DTS_WORLD, &g_mtx);

	for (int i = 0; i < 2; i++)
	{
		pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &cube[i][0], sizeof(VERTEX_JUDEGCUBE));
	}

}

// 生成する
void SetJudgecube(float Width, float Height)
{
	// XY軸の平面
	float width = Width;
	float height = Height;
	cube[0][0].pos.x =- width*0.5f;
	cube[0][0].pos.y =  height*0.5f;
	cube[0][1].pos.x =- width*0.5f;
	cube[0][1].pos.y =- height*0.5f;
	cube[0][2].pos.x =  width*0.5f;
	cube[0][2].pos.y =- height*0.5f;
	cube[0][3].pos.x =  width*0.5f;
	cube[0][3].pos.y =  height*0.5f;
	cube[0][4].pos = cube[0][0].pos;

	// ZY軸の平面
	cube[1][0].pos.z = - width*0.5f;
	cube[1][0].pos.y =   height*0.5f;
	cube[1][1].pos.z = - width*0.5f;
	cube[1][1].pos.y = - height*0.5f;
	cube[1][2].pos.z =   width*0.5f;
	cube[1][2].pos.y = - height*0.5f;
	cube[1][3].pos.z =   width*0.5f;
	cube[1][3].pos.y =   height*0.5f;
	cube[1][4].pos = cube[1][0].pos;
}