
// ”BAKUMIN”のLOGO
// ======================================

#include "logo.h"

static LPDIRECT3DVERTEXBUFFER9 g_p3DVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9  g_pIndexBuffer = NULL;

static D3DXMATRIX g_logo_mtxWorld;

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

bool InitLogo(void) {

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return FALSE; }

	HRESULT hr;

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_p3DVertexBuffer, NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, "LOGO頂点バッファ作成失敗", "エラー", MB_OK);
		return false;
	}
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * 4, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, "LOGOインデックスバッファ作成失敗", "エラー", MB_OK);
		return false;
	}
	VERTEX_3D logo[] = {
		{ D3DXVECTOR3(-LOGO_WIDTH*0.5f, 0,			-1), D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR3(-LOGO_WIDTH*0.5f,LOGO_HEIGHT ,-1), D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR3(LOGO_WIDTH*0.5f, 0 ,			-1), D3DXVECTOR3(0.0f,0.0f,-1.0f) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1.0f,1.0f) },
		{ D3DXVECTOR3(LOGO_WIDTH*0.5f,LOGO_HEIGHT , -1), D3DXVECTOR3(0.0f,0.0f,-1.0f) ,D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,0.0f) },
	};

	VERTEX_3D* pV;
	g_p3DVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	memcpy(pV, &logo, sizeof(logo));
	g_p3DVertexBuffer->Unlock();

	LPWORD pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	// インデックスデータを書き込み
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 3;

	g_pIndexBuffer->Unlock();

	D3DXMatrixIdentity(&g_logo_mtxWorld);

	return true;
}
void UninitLogo(void) {
	if (g_p3DVertexBuffer != NULL) {
		g_p3DVertexBuffer->Release();
		g_p3DVertexBuffer = NULL;
	}

	if (g_pIndexBuffer != NULL) {
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}
void UpdateLogo(void) 
{

}
void DrawLogo(void) 
{

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// マテリアル
	D3DMATERIAL9 mat;
	SecureZeroMemory(&mat, sizeof(mat));
	mat.Diffuse.r = 1.0f;
	mat.Diffuse.b = 1.0f;
	mat.Diffuse.g = 1.0f;
	mat.Diffuse.a = 1.0f;

	mat.Ambient.r = 0.8f;
	mat.Ambient.g = 0.8f;
	mat.Ambient.b = 0.8f;
	mat.Ambient.a = 1.0f;
	pDevice->SetMaterial(&mat);
	// FVF設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// CUBE1頂点バッファ使う
	pDevice->SetTransform(D3DTS_WORLD, &g_logo_mtxWorld);
	SetTextureNum(TEXTURE_LOGO);

	pDevice->SetStreamSource(0, g_p3DVertexBuffer, 0, sizeof(VERTEX_3D));
	// インデックスバッファ使う
	pDevice->SetIndices(g_pIndexBuffer);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);

}
