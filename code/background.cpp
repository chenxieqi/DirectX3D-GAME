
// ゲームシーン以外の黄色バックグラウンド
// ======================================

#include "background.h"

// バッファ
static LPDIRECT3DVERTEXBUFFER9 g_cube1_p3DVertexBuffer = NULL;
static LPDIRECT3DVERTEXBUFFER9 g_cube2_p3DVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9  g_pIndexBuffer = NULL;

// 行列
static D3DXMATRIX g_cube1_mtxWorld, g_cube1_mtxRotSky;
static D3DXMATRIX g_cube2_mtxWorld, g_cube2_mtxRotSky;

// 回転速度
static float g_cube1_rotspeed;
static float g_cube2_rotspeed;
static float g_addspeed;


// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

// 初期化
bool InitBackground(void) {

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return FALSE; }

	HRESULT hr;

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_cube1_p3DVertexBuffer, NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, "CUBE1頂点バッファ作成失敗", "エラー", MB_OK);
		return false;
	}

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_cube2_p3DVertexBuffer, NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, "CUBE2頂点バッファ作成失敗", "エラー", MB_OK);
		return false;
	}
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * 4,D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, "CUBEインデックスバッファ作成失敗", "エラー", MB_OK);
		return false;
	}
	VERTEX_3D cube1[] = {
		{ D3DXVECTOR3(-CUBE1_LENGTH*0.5f, -CUBE1_LENGTH*0.5f,0), D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR3(-CUBE1_LENGTH*0.5f ,CUBE1_LENGTH*0.5f ,0),  D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR3(CUBE1_LENGTH*0.5f,-CUBE1_LENGTH*0.5f  ,0),  D3DXVECTOR3(0.0f,0.0f,-1.0f) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1.0f,1.0f) },
		{ D3DXVECTOR3(CUBE1_LENGTH*0.5f,CUBE1_LENGTH*0.5f   ,0),  D3DXVECTOR3(0.0f,0.0f,-1.0f) ,D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,0.0f) },
	};
	VERTEX_3D cube2[] = {
		{ D3DXVECTOR3(-CUBE2_LENGTH*0.5f, -CUBE2_LENGTH*0.5f,5), D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR3(-CUBE2_LENGTH*0.5f , CUBE2_LENGTH*0.5f,5), D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),  D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR3(CUBE2_LENGTH*0.5f, -CUBE2_LENGTH*0.5f ,5),D3DXVECTOR3(0.0f,0.0f,-1.0f) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1.0f,1.0f) },
		{ D3DXVECTOR3(CUBE2_LENGTH*0.5f,CUBE2_LENGTH*0.5f   ,5),D3DXVECTOR3(0.0f,0.0f,-1.0f) ,D3DCOLOR_RGBA(255,255,255,255),  D3DXVECTOR2(1.0f,0.0f) },
	};

	VERTEX_3D* pV1;
	g_cube1_p3DVertexBuffer->Lock(0, 0, (void**)&pV1, D3DLOCK_DISCARD);
	memcpy(pV1, &cube1, sizeof(cube1));
	g_cube1_p3DVertexBuffer->Unlock();

	VERTEX_3D* pV2;
	g_cube2_p3DVertexBuffer->Lock(0, 0, (void**)&pV2, D3DLOCK_DISCARD);
	memcpy(pV2, &cube2, sizeof(cube2));
	g_cube2_p3DVertexBuffer->Unlock();

	LPWORD pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	// インデックスデータを書き込み
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 3;

	g_pIndexBuffer->Unlock();

	D3DXMatrixIdentity(&g_cube1_mtxWorld);
	D3DXMatrixIdentity(&g_cube1_mtxRotSky);
	g_cube1_rotspeed = 0;

	D3DXMatrixIdentity(&g_cube2_mtxWorld);
	D3DXMatrixIdentity(&g_cube2_mtxRotSky);
	g_cube2_rotspeed = 0;

	g_addspeed = 0.00002f;
	return true;
}

// 解放
void UninitBackground(void) {
	if (g_cube1_p3DVertexBuffer != NULL) {
		g_cube1_p3DVertexBuffer->Release();
		g_cube1_p3DVertexBuffer = NULL;
	}
	if (g_cube2_p3DVertexBuffer != NULL) {
		g_cube2_p3DVertexBuffer->Release();
		g_cube2_p3DVertexBuffer = NULL;
	}
	if (g_pIndexBuffer != NULL) {
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}

// 更新
void UpdateBackground(void) {
	g_cube1_rotspeed += g_addspeed;
	D3DXMatrixRotationZ(&g_cube1_mtxRotSky, g_cube1_rotspeed);
	g_cube1_mtxWorld = g_cube1_mtxRotSky*g_cube1_mtxWorld;

	g_cube2_rotspeed += g_addspeed*0.5f;
	D3DXMatrixRotationZ(&g_cube2_mtxRotSky, g_cube2_rotspeed);
	g_cube2_mtxWorld = g_cube2_mtxRotSky*g_cube2_mtxWorld;
	
	if (g_cube1_rotspeed >= D3DX_PI*0.001|| g_cube1_rotspeed <= -D3DX_PI*0.001)
	{
		g_addspeed = -g_addspeed;
	}
}

// 描画処理
void DrawBackground(void) {

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

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

	
	// CUBE2頂点バッファ使う
	pDevice->SetStreamSource(0, g_cube2_p3DVertexBuffer, 0, sizeof(VERTEX_3D));
	pDevice->SetTransform(D3DTS_WORLD, &g_cube2_mtxWorld);
	
	SetTextureNum(TEXTURE_CUBE2);
	
	pDevice->SetTransform(D3DTS_WORLD, &g_cube2_mtxWorld);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);

	// CUBE1頂点バッファ使う
	pDevice->SetTransform(D3DTS_WORLD, &g_cube1_mtxWorld);
	SetTextureNum(TEXTURE_CUBE1);

	pDevice->SetStreamSource(0, g_cube1_p3DVertexBuffer, 0, sizeof(VERTEX_3D));
	// インデックスバッファ使う
	pDevice->SetIndices(g_pIndexBuffer);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);

}
