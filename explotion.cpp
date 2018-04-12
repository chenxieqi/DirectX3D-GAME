//=============================================================================
//
// ------------------爆発処理 -----------------------
//
//=============================================================================
#include "explotion.h"

static const int MAX_EXPLO = 100;			// 爆発最大個数
static const float EXPLOSION_SC = 20.0f;	// 爆発大きさ

typedef struct {
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 oldPos;
	int nAnimCount;// 爆発アニメーションフレームカウンター
	bool bUse;
	D3DXMATRIX mtx;
	int row;//パターン行
	int line;//パターン列
	int texNum;//パターン個数
}EXPLO;

// 行列
static D3DXMATRIX g_mtxInvView;
static D3DXMATRIX g_mtxCamView;

// バッファ
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9  g_pIndexBuffer = NULL;

static 	VERTEX_3D* pV;

static EXPLO g_explo[MAX_EXPLO];

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

// 初期化
bool InitExplosion()
{
	for (int count = 0; count < MAX_EXPLO; count++)
	{
		g_explo[count].bUse = false;
		g_explo[count].nAnimCount = 0;
		g_explo[count].oldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_explo[count].vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_explo[count].row = 0;
		g_explo[count].line = 0;
		g_explo[count].texNum = 0;
		D3DXMatrixIdentity(&g_explo[count].mtx);
	}

	VERTEX_3D v1[] = {
		{ D3DXVECTOR3(-EXPLOSION_SC, EXPLOSION_SC,-EXPLOSION_SC),  D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR3(EXPLOSION_SC, EXPLOSION_SC,-EXPLOSION_SC),   D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR3(-EXPLOSION_SC,-EXPLOSION_SC,-EXPLOSION_SC), D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR3(EXPLOSION_SC,-EXPLOSION_SC,-EXPLOSION_SC),  D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,1.0f) }
	};

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return false; }

	HRESULT hr;


	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, "頂点バッファ作成失敗", "エラー", MB_OK);
		return false;
	}
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * 4,//2byte  DWORD--4byte
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,//if DWORD :32
		D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, "インデックスバッファ作成失敗", "エラー", MB_OK);
		return false;
	}

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	memcpy(pV, &v1, sizeof(v1));
	g_pVertexBuffer->Unlock();


	LPWORD pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	// インデックスデータを書き込み
	pIndex[0] = 2;
	pIndex[1] = 0;
	pIndex[2] = 3;
	pIndex[3] = 1;

	g_pIndexBuffer->Unlock();
}

// 解放
void UninitExplosion() 
{
	if (g_pVertexBuffer != NULL) {
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	if (g_pIndexBuffer != NULL) {
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}

// 更新
void UpdateExplosion() 
{
	for (int count = 0; count < MAX_EXPLO; count++)
	{
		if (g_explo[count].bUse)
		{
			g_explo[count].nAnimCount++;
			
			D3DXMatrixTranslation(&g_explo[count].mtx, g_explo[count].vPos.x, g_explo[count].vPos.y, g_explo[count].vPos.z);

			//  ビュー行列の取得  
			LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
			pDevice->GetTransform(D3DTS_VIEW, &g_mtxCamView);

			D3DXMatrixInverse(&g_mtxInvView,NULL, &g_mtxCamView);

			g_mtxInvView._41 = 0.0f;
			g_mtxInvView._42 = 0.0f;
			g_mtxInvView._43 = 0.0f;
			D3DXMatrixMultiply(&g_explo[count].mtx, &g_mtxInvView, &g_explo[count].mtx);
		}
	}

}

// 描画処理
void DrawExplosion()
{
	for (int count = 0; count < MAX_EXPLO; count++)
	{
		if (!g_explo[count].bUse) { continue; }
		int nPattern = (g_explo[count].nAnimCount / 6) % (g_explo[count].row*g_explo[count].line)+1;
		//draw
		ChangeUV(g_explo[count].row, g_explo[count].line, nPattern);
		SetDrawEx(g_explo[count].mtx, g_explo[count].texNum);

		if (nPattern == g_explo[count].row*g_explo[count].line) {
			g_explo[count].bUse = false;
			g_explo[count].nAnimCount = 0;
			g_explo[count].oldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_explo[count].vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}
}

// 生成
void CreateExplosion(D3DXVECTOR3 vec,int row,int line,int texNum) 
{
	for (int count = 0; count < MAX_EXPLO; count++)
	{
		if (!g_explo[count].bUse)
		{
			g_explo[count].vPos = D3DXVECTOR3(vec.x,vec.y+ EXPLOSION_SC*0.5f,vec.z);
			g_explo[count].bUse = true;
			g_explo[count].row = row;
			g_explo[count].line = line;
			g_explo[count].texNum = texNum;
			break;
		}
	}
}


// -------------------------------------------------------------
//  ゲット用関数
// -------------------------------------------------------------

// 座標
const D3DXVECTOR3 GetExPos(int i)
{
	return g_explo[i].vPos;
}

// 存在しているか
bool IsEx(int i)
{
	return g_explo[i].bUse;
}


// -------------------------------------------------------------
//  そのほか関数
// -------------------------------------------------------------

// 描画のセット
void SetDrawEx(D3DXMATRIX mtx, int tex)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	// pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


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

	SetTextureNum(tex);
	// 各種行列の設定--状況による設定する
	pDevice->SetTransform(D3DTS_WORLD, &mtx);

	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_3D));
	// インデックスバッファ使う
	pDevice->SetIndices(g_pIndexBuffer);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

// UVを変える
void ChangeUV(int trow, int tline, int num)
{

		float u0 = (1 / (float)tline);
		float v0 = (1 / (float)trow);
		float u = u0*(num % tline - 1);
		float v = v0 *(num / (tline + 1));

		g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD); // LockするとGPU止まってます

		pV[0].texcoord = D3DXVECTOR2(u, v);
		pV[1].texcoord = D3DXVECTOR2(u + u0, v);
		pV[2].texcoord = D3DXVECTOR2(u, v + v0);
		pV[3].texcoord = D3DXVECTOR2(u + u0, v + v0);

		g_pVertexBuffer->Unlock();
}