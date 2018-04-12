
// ゲームシーンのSKYCUBE
// ======================================

#include "NightCube.h"



// FVFの宣言(定数)
#define FVF_NightCube		(D3DFVF_XYZ|D3DFVF_TEX1)

typedef struct
{
	D3DXVECTOR3 pos; 
	D3DXVECTOR2 texcoord;
}NightCube;


static TEXTURE_NUM g_Texture3DNum;
static LPDIRECT3DVERTEXBUFFER9 g_p3DVertexBuffer = NULL;
static D3DXMATRIX g_mtxWorld, g_mtxRotSky;
static float g_rotspeed;

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------
bool InitNightCube(void) {

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return FALSE; }

	HRESULT hr;

	hr = pDevice->CreateVertexBuffer(sizeof(NightCube) * 24, D3DUSAGE_WRITEONLY, FVF_NightCube, D3DPOOL_MANAGED, &g_p3DVertexBuffer, NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, "頂点バッファ作成失敗", "エラー", MB_OK);
		return false;
	}

	float sc_length = NIGHTCUBE_WIDTH / 2;
	NightCube v1[] = {
		// 後ろ
		{ D3DXVECTOR3(sc_length, -sc_length,-sc_length),D3DXVECTOR2(0.75f,0.5f)},
		{ D3DXVECTOR3(sc_length ,sc_length,-sc_length), D3DXVECTOR2(0.75f,0.25f)},
		{ D3DXVECTOR3(-sc_length,-sc_length,-sc_length),D3DXVECTOR2(1.0f,0.5f)  },
		{ D3DXVECTOR3(-sc_length,sc_length,-sc_length), D3DXVECTOR2(1.0f,0.25f)  },
		// 右										   
		{ D3DXVECTOR3(sc_length, -sc_length,sc_length), D3DXVECTOR2(0.5f,0.5f) },
		{ D3DXVECTOR3(sc_length, sc_length, sc_length), D3DXVECTOR2(0.5f,0.25f) },
		{ D3DXVECTOR3(sc_length,-sc_length,-sc_length), D3DXVECTOR2(0.75f,0.5f) },
		{ D3DXVECTOR3(sc_length,sc_length, -sc_length), D3DXVECTOR2(0.75f,0.25f) },
		// 前										   
		{ D3DXVECTOR3(-sc_length, -sc_length,sc_length),D3DXVECTOR2(0.25f,0.5f) },
		{ D3DXVECTOR3(-sc_length, sc_length,sc_length), D3DXVECTOR2(0.25f,0.25f) },
		{ D3DXVECTOR3(sc_length,-sc_length,sc_length),  D3DXVECTOR2(0.5f,0.5f) },
		{ D3DXVECTOR3(sc_length,sc_length,sc_length),   D3DXVECTOR2(0.5f,0.25f) },
		// 左										   
		{ D3DXVECTOR3(-sc_length, -sc_length, -sc_length),D3DXVECTOR2(0.0f,0.5f)  },
		{ D3DXVECTOR3(-sc_length, sc_length,-sc_length),  D3DXVECTOR2(0.0f,0.25f)  },
		{ D3DXVECTOR3(-sc_length,-sc_length, sc_length),  D3DXVECTOR2(0.25f,0.5f)},
		{ D3DXVECTOR3(-sc_length,sc_length,sc_length),    D3DXVECTOR2(0.25f,0.25f)},
		// 上										   
		{ D3DXVECTOR3(sc_length,sc_length, -sc_length), D3DXVECTOR2(0.25f,0.25f) },
		{ D3DXVECTOR3(sc_length,sc_length, sc_length),  D3DXVECTOR2(0.25f,0.0f) },
		{ D3DXVECTOR3(-sc_length,sc_length,-sc_length), D3DXVECTOR2(0.5f,0.25f) },
		{ D3DXVECTOR3(-sc_length,sc_length,sc_length),  D3DXVECTOR2(0.5f,0.0f) },
		// 下										  
		{ D3DXVECTOR3(-sc_length,-sc_length,-sc_length),D3DXVECTOR2(0.25f,0.75f) },
		{ D3DXVECTOR3(-sc_length,-sc_length,sc_length), D3DXVECTOR2(0.25f,0.5f) },
		{ D3DXVECTOR3(sc_length, -sc_length,-sc_length),D3DXVECTOR2(0.5f,0.75f) },
		{ D3DXVECTOR3(sc_length, -sc_length, sc_length),D3DXVECTOR2(0.5f,0.5f) },

	};

	NightCube* pV;
	g_p3DVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	memcpy(pV, &v1, sizeof(v1));
	g_p3DVertexBuffer->Unlock();

	D3DXMatrixIdentity(&g_mtxWorld);
	D3DXMatrixIdentity(&g_mtxRotSky);
	g_rotspeed = 0.0001f;

	return true;
}
void UninitNightCube(void) {
	if (g_p3DVertexBuffer != NULL) {
		g_p3DVertexBuffer->Release();
		g_p3DVertexBuffer = NULL;
	}

}
void UpdateNightCube(void) {
	D3DXMatrixRotationY(&g_mtxRotSky, g_rotspeed);
	g_mtxWorld = g_mtxRotSky*g_mtxWorld;
}
void DrawNightCube(void) {

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);

	// マテリアル
	D3DMATERIAL9 mat;
	SecureZeroMemory(&mat, sizeof(mat));
	mat.Diffuse.r = 1.0f;
	mat.Diffuse.b = 1.0f;
	mat.Diffuse.g = 1.0f;
	mat.Diffuse.a = 0.5f;

	mat.Ambient.r = 0.8f;
	mat.Ambient.g = 0.8f;
	mat.Ambient.b = 0.8f;
	mat.Ambient.a = 0.5f;
	pDevice->SetMaterial(&mat);


	// 各種行列の設定--状況による設定する
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

	// FVF設定
	pDevice->SetFVF(FVF_NightCube);


	// 頂点バッファ使う
	pDevice->SetStreamSource(0, g_p3DVertexBuffer, 0, sizeof(NightCube));

	SetTextureNum(TEXTURE_NIGHT);

	for (int i = 0; i < 24; i += 4)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i, 2);
	}
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

}