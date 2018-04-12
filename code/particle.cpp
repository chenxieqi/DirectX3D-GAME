
// 爆発時のパーティクル
// ======================================

#include "particle.h"

#define FVF_VERTEX3D		(D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1|D3DFVF_NORMAL)
#define MAX_PARTICLE		(4000)
#define PI					(3.14)

typedef struct
{
	D3DXVECTOR3 pos; 
	D3DXVECTOR3 normal; // 法線
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_PARTICLE;
typedef struct 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 speed;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxMove;
	float force;
	int birth;
	int life;
	int angle;
	bool bUse;
}PARTICLE;

static PARTICLE g_particle[MAX_PARTICLE];

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferWhite = NULL;
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferYellow = NULL;
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferRed = NULL;
static LPDIRECT3DINDEXBUFFER9  g_pIndexBuffer = NULL;

static D3DXMATRIX g_mtxInvView;
static D3DXMATRIX g_mtxCamView;

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

// 初期化
bool InitParticle()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return false; }
	WORD index[] = { 2,0,3,1 };

	VERTEX_PARTICLE vred[] = {
	{ D3DXVECTOR3(-1.5f,1.5f,-1.5f),  D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,0,0,255) ,D3DXVECTOR2(0.0f,0.0f) },
	{ D3DXVECTOR3(1.5f,1.5f,-1.5f),   D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,0,0,255), D3DXVECTOR2(1.0f,0.0f) },
	{ D3DXVECTOR3(-1.5f,-1.5f,-1.5f), D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,0,0,255) ,D3DXVECTOR2(0.0f,1.0f) },
	{ D3DXVECTOR3(1.5f,-1.5f,-1.5f),  D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,0,0,255), D3DXVECTOR2(1.0f,1.0f) }
	};
	VERTEX_PARTICLE vyellow[] = {
	{ D3DXVECTOR3(-1.5f,1.5f,-1.5f),  D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,0,255) ,D3DXVECTOR2(0.0f,0.0f) },
	{ D3DXVECTOR3(1.5f,1.5f,-1.5f),   D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,0,255), D3DXVECTOR2(1.0f,0.0f) },
	{ D3DXVECTOR3(-1.5f,-1.5f,-1.5f), D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,0,255) ,D3DXVECTOR2(0.0f,1.0f) },
	{ D3DXVECTOR3(1.5f,-1.5f,-1.5f),  D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,0,255), D3DXVECTOR2(1.0f,1.0f) }
	};
	VERTEX_PARTICLE vwhite[] = {
	{ D3DXVECTOR3(-1.5f,1.5f,-1.5f),  D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,0.0f) },
	{ D3DXVECTOR3(1.5f,1.5f,-1.5f),   D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,0.0f) },
	{ D3DXVECTOR3(-1.5f,-1.5f,-1.5f), D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
	{ D3DXVECTOR3(1.5f,-1.5f,-1.5f),  D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,1.0f) }
	};
	HRESULT hr;


	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_PARTICLE) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_pVertexBufferWhite, NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, "頂点バッファ作成失敗", "エラー", MB_OK);
		return false;
	}

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_PARTICLE) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_pVertexBufferYellow, NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, "頂点バッファ作成失敗", "エラー", MB_OK);
		return false;
	}

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_PARTICLE) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_pVertexBufferRed, NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, "頂点バッファ作成失敗", "エラー", MB_OK);
		return false;
	}

	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * 4,D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, "インデックスバッファ作成失敗", "エラー", MB_OK);
		return false;
	}

	// NOWLOADINGの時済ませる-----Init

	VERTEX_PARTICLE* pVwhite;
	g_pVertexBufferWhite->Lock(0, 0, (void**)&pVwhite, D3DLOCK_DISCARD);
	memcpy(pVwhite, &vwhite, sizeof(vwhite));
	g_pVertexBufferWhite->Unlock();

	VERTEX_PARTICLE* pVyellow;
	g_pVertexBufferYellow->Lock(0, 0, (void**)&pVyellow, D3DLOCK_DISCARD);
	memcpy(pVyellow, &vyellow, sizeof(vyellow));
	g_pVertexBufferYellow->Unlock();

	VERTEX_PARTICLE* pVred;
	g_pVertexBufferRed->Lock(0, 0, (void**)&pVred, D3DLOCK_DISCARD);
	memcpy(pVred, &vred, sizeof(vred));
	g_pVertexBufferRed->Unlock();

	LPWORD pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	// インデックスデータを書き込み
	memcpy(pIndex, &index, sizeof(index));

	g_pIndexBuffer->Unlock();

	
	for (int cnt = 0; cnt < MAX_PARTICLE; cnt++)
	{
		g_particle[cnt].pos = D3DXVECTOR3(0, 0, 0);
		g_particle[cnt].speed= D3DXVECTOR3(0, 0, 0);
		g_particle[cnt].angle = 0;
		g_particle[cnt].bUse = false;
		g_particle[cnt].birth = 0;
		g_particle[cnt].life = 0;
		g_particle[cnt].force = 0;
		D3DXMatrixIdentity(&g_particle[cnt].mtxMove);
		D3DXMatrixIdentity(&g_particle[cnt].mtxWorld);
	}

	return true;

}

// 解放
void UninitParticle()
{
	if (g_pVertexBufferWhite != NULL) {
		g_pVertexBufferWhite->Release();
		g_pVertexBufferWhite = NULL;
	}
	if (g_pVertexBufferYellow != NULL) {
		g_pVertexBufferYellow->Release();
		g_pVertexBufferYellow = NULL;
	}
	if (g_pVertexBufferRed != NULL) {
		g_pVertexBufferRed->Release();
		g_pVertexBufferRed = NULL;
	}
	if (g_pIndexBuffer != NULL) {
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}

// 更新
void UpdateParticle()
{
	for (int cnt = 0; cnt < MAX_PARTICLE; cnt++)
	{
		if (g_particle[cnt].bUse)
		{
			g_particle[cnt].birth--;
			if (g_particle[cnt].birth > 0) { continue; }
			g_particle[cnt].angle ++;
			g_particle[cnt].speed.x = sin(PI*g_particle[cnt].angle / 180)*g_particle[cnt].force;
			g_particle[cnt].speed.z += 0.02f;
			g_particle[cnt].speed.y = cos(PI*g_particle[cnt].angle / 180)*g_particle[cnt].force;
			g_particle[cnt].pos += g_particle[cnt].speed;
			D3DXMatrixIdentity(&g_particle[cnt].mtxWorld);
			D3DXMatrixTranslation(&g_particle[cnt].mtxMove, g_particle[cnt].pos.x, g_particle[cnt].pos.y, g_particle[cnt].pos.z);
			D3DXMatrixMultiply(&g_particle[cnt].mtxWorld, &g_particle[cnt].mtxMove, &g_particle[cnt].mtxMove);
			//  ビュー行列の取得  
			LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
			pDevice->GetTransform(D3DTS_VIEW, &g_mtxCamView);

			D3DXMatrixInverse(&g_mtxInvView, NULL, &g_mtxCamView);

			g_mtxInvView._41 = 0.0f;
			g_mtxInvView._42 = 0.0f;
			g_mtxInvView._43 = 0.0f;

			D3DXMatrixMultiply(&g_particle[cnt].mtxWorld, &g_mtxInvView, &g_particle[cnt].mtxWorld);
			g_particle[cnt].life--;
			if (g_particle[cnt].life <= 0)
			{
				DestroyParticle(cnt);
			}
		}
	}
}

// 描画処理
void DrawParticle()
{
	for (int cnt = 0; cnt < MAX_PARTICLE; cnt++)
	{
		if (g_particle[cnt].bUse)
		{
			if (g_particle[cnt].birth > 0) { continue; }
			LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

			// FVF設定
			pDevice->SetFVF(FVF_VERTEX3D);
			SetTextureNum(TEXTURE_EFFECT);

			if (g_particle[cnt].life < 100)
			{
				pDevice->SetStreamSource(0, g_pVertexBufferWhite, 0, sizeof(VERTEX_PARTICLE));
			}
			else if (g_particle[cnt].life < 150)
			{
				pDevice->SetStreamSource(0, g_pVertexBufferYellow, 0, sizeof(VERTEX_PARTICLE));
			}
			else
			{
				pDevice->SetStreamSource(0, g_pVertexBufferRed, 0, sizeof(VERTEX_PARTICLE));
			}


			// インデックスバッファ使う
			pDevice->SetIndices(g_pIndexBuffer);

			// Z-Buffer Off
			pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			// 加算合成によるアルファブレンド
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


			pDevice->SetTransform(D3DTS_WORLD, &g_particle[cnt].mtxWorld);
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
			pDevice->SetTransform(D3DTS_WORLD, &g_particle[cnt].mtxWorld);
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);

			// Z-Buffer On
			pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// 通常のアルファブレンド
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}

// 描画セット
void SetDrawParticle(D3DXVECTOR3 vec)
{
	int creat_cnt=0;
	for (int cnt = 0; cnt < MAX_PARTICLE; cnt++)
	{
		if (creat_cnt > 150)
		{
			break;
		}
		if (!g_particle[cnt].bUse)
		{
			g_particle[cnt].angle =cnt*20;
			g_particle[cnt].bUse = true;
			g_particle[cnt].birth = creat_cnt;
			g_particle[cnt].force = rand()%10 * 0.2f;
			g_particle[cnt].pos = vec+ D3DXVECTOR3(g_particle[cnt].force*5, -g_particle[cnt].force * 5, g_particle[cnt].force * 5);
			g_particle[cnt].life = 200+ g_particle[cnt].birth;
			D3DXMatrixIdentity(&g_particle[cnt].mtxMove);
			D3DXMatrixIdentity(&g_particle[cnt].mtxWorld);
			creat_cnt++;
		}
	}
}

// 消す
void DestroyParticle(int cnt)
{
	g_particle[cnt].pos = D3DXVECTOR3(0, 0, 0);
	g_particle[cnt].speed = D3DXVECTOR3(0, 0, 0);
	g_particle[cnt].angle = 0;
	g_particle[cnt].bUse = false;
	g_particle[cnt].life = 0;
	g_particle[cnt].birth = 0;
	g_particle[cnt].force = 0;
	D3DXMatrixIdentity(&g_particle[cnt].mtxMove);
	D3DXMatrixIdentity(&g_particle[cnt].mtxWorld);
}

