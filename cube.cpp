
// 描画用キューブ（プレイヤー弾の”しっぽ”
// ======================================

#include "cube.h"


// FVFの宣言(定数)
#define FVF_CUBE		(D3DFVF_XYZ|D3DFVF_TEX1)
#define MAX_CUBE_ANIME	(100)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 texcoord;
}CUBE;

// プレイヤー弾のしっぽの構造体
typedef struct
{
	D3DXVECTOR3 pos;
	int life;
	bool banime;
	float scale;
	TEXTURE_NUM num;
	D3DXMATRIX mtxWorld;
}CUBEANIME;

static CUBEANIME cube_anime[MAX_CUBE_ANIME];
static TEXTURE_NUM g_Texture3DNum;
static LPDIRECT3DVERTEXBUFFER9 g_p3DVertexBuffer = NULL;
static D3DXMATRIX g_mtxWorld;

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

// 初期化
bool InitCube(void) {

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return FALSE; }

	HRESULT hr;

	hr = pDevice->CreateVertexBuffer(sizeof(CUBE) * 24, D3DUSAGE_WRITEONLY, FVF_CUBE, D3DPOOL_MANAGED, &g_p3DVertexBuffer, NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, "頂点バッファ作成失敗", "エラー", MB_OK);
		return false;
	}

	float sc_length = CUBE_WIDTH / 2;
	CUBE v1[] = {
	// 後ろ
	{ D3DXVECTOR3(-sc_length, sc_length,-sc_length),D3DXVECTOR2(0.75f,0.5f) },
	{ D3DXVECTOR3(sc_length ,sc_length,-sc_length), D3DXVECTOR2(0.75f,0.25f) },
	{ D3DXVECTOR3(-sc_length,-sc_length,-sc_length),D3DXVECTOR2(1.0f,0.5f) },
	{ D3DXVECTOR3(sc_length,-sc_length,-sc_length), D3DXVECTOR2(1.0f,0.25f) },
	// 右										   
	{ D3DXVECTOR3(sc_length, sc_length,-sc_length), D3DXVECTOR2(0.5f,0.5f) },
	{ D3DXVECTOR3(sc_length, sc_length, sc_length), D3DXVECTOR2(0.5f,0.25f) },
	{ D3DXVECTOR3(sc_length,-sc_length,-sc_length), D3DXVECTOR2(0.75f,0.5f) },
	{ D3DXVECTOR3(sc_length,-sc_length, sc_length), D3DXVECTOR2(0.75f,0.25f) },
	// 前										   
	{ D3DXVECTOR3(sc_length, sc_length,sc_length), D3DXVECTOR2(0.25f,0.5f) },
	{ D3DXVECTOR3(-sc_length, sc_length,sc_length),D3DXVECTOR2(0.25f,0.25f) },
	{ D3DXVECTOR3(sc_length,-sc_length,sc_length), D3DXVECTOR2(0.5f,0.5f) },
	{ D3DXVECTOR3(-sc_length,-sc_length,sc_length),D3DXVECTOR2(0.5f,0.25f) },
	// 左										   
	{ D3DXVECTOR3(-sc_length, sc_length, sc_length),D3DXVECTOR2(0.0f,0.5f) },
	{ D3DXVECTOR3(-sc_length, sc_length,-sc_length),D3DXVECTOR2(0.0f,0.25f) },
	{ D3DXVECTOR3(-sc_length,-sc_length, sc_length),D3DXVECTOR2(0.25f,0.5f) },
	{ D3DXVECTOR3(-sc_length,-sc_length,-sc_length),D3DXVECTOR2(0.25f,0.25f) },
	// 上										   
	{ D3DXVECTOR3(-sc_length,sc_length, sc_length), D3DXVECTOR2(0.25f,0.25f) },
	{ D3DXVECTOR3(sc_length,sc_length, sc_length),  D3DXVECTOR2(0.25f,0.0f) },
	{ D3DXVECTOR3(-sc_length,sc_length,-sc_length), D3DXVECTOR2(0.5f,0.25f) },
	{ D3DXVECTOR3(sc_length,sc_length,-sc_length),  D3DXVECTOR2(0.5f,0.0f) },
	// 下										  
	{ D3DXVECTOR3(-sc_length,-sc_length,-sc_length),D3DXVECTOR2(0.25f,0.75f) },
	{ D3DXVECTOR3(sc_length,-sc_length,-sc_length), D3DXVECTOR2(0.25f,0.5f) },
	{ D3DXVECTOR3(-sc_length, -sc_length,sc_length),D3DXVECTOR2(0.5f,0.75f) },
	{ D3DXVECTOR3(sc_length, -sc_length, sc_length),D3DXVECTOR2(0.5f,0.5f) },

	};

	CUBE* pV;
	g_p3DVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	memcpy(pV, &v1, sizeof(v1));
	g_p3DVertexBuffer->Unlock();

	D3DXMatrixIdentity(&g_mtxWorld);

	for (int cnt = 0; cnt < MAX_CUBE_ANIME; cnt++)
	{
		cube_anime[cnt].pos= D3DXVECTOR3(0.0,0.0,0.0);
		cube_anime[cnt].life=60;
		cube_anime[cnt].banime=false;
		cube_anime[cnt].scale=1.0f;
		cube_anime[cnt].num=TEXTURE_BLUE;
		D3DXMatrixIdentity(&cube_anime[cnt].mtxWorld);
	}


	return true;
}

// 解放
void UninitCube(void) {
	if (g_p3DVertexBuffer != NULL) {
		g_p3DVertexBuffer->Release();
		g_p3DVertexBuffer = NULL;
	}

}

// 更新
void UpdateCube(void) 
{
	for (int cnt = 0; cnt < MAX_CUBE_ANIME; cnt++)
	{
		if (cube_anime[cnt].banime)
		{
			if (cube_anime[cnt].life <= 0)
			{
				cube_anime[cnt].pos = D3DXVECTOR3(0.0, 0.0, 0.0);
				cube_anime[cnt].life = 60;
				cube_anime[cnt].banime = false;
				cube_anime[cnt].scale = 1.0f;
				cube_anime[cnt].num = TEXTURE_BLUE;
				D3DXMatrixIdentity(&cube_anime[cnt].mtxWorld);
			}

			if (cube_anime[cnt].life >= 55)
			{
				cube_anime[cnt].scale = 1.0;
				cube_anime[cnt].num = TEXTURE_BLUE;
			}
			else if (cube_anime[cnt].life >= 45)
			{
				cube_anime[cnt].scale = 0.8;
				cube_anime[cnt].num = TEXTURE_GREEN;
			}
			else if (cube_anime[cnt].life >= 35)
			{
				cube_anime[cnt].scale = 0.6;
				cube_anime[cnt].num = TEXTURE_YELLOW;
			}
			else if (cube_anime[cnt].life >= 25)
			{
				cube_anime[cnt].scale = 0.4;
				cube_anime[cnt].num = TEXTURE_ORANGE;
			}
			else if (cube_anime[cnt].life > 0)
			{
				cube_anime[cnt].scale = 0.2;
				cube_anime[cnt].num = TEXTURE_RED;
			}
			cube_anime[cnt].life--;
		}
	}
}

// 一つのキューブの描画処理
void DrawCube(D3DXMATRIX mtx, int num) {

	g_mtxWorld = mtx;


	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 各種行列の設定--状況による設定する
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

	// FVF設定
	pDevice->SetFVF(FVF_CUBE);


	// 頂点バッファ使う
	pDevice->SetStreamSource(0, g_p3DVertexBuffer, 0, sizeof(CUBE));

	SetTextureNum(num);

	for (int i = 0; i < 24; i += 4)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i, 2);
	}

	
}

// 生成
void CreateCubeAnime(D3DXMATRIX mtx) {
	
	for (int cnt = 0; cnt < MAX_CUBE_ANIME; cnt++)
	{
		if (!cube_anime[cnt].banime) {
			cube_anime[cnt].pos = D3DXVECTOR3(mtx._41,mtx._42,mtx._43);
			cube_anime[cnt].banime = true;
			break;
		}
	}

}

// 一連のしっぽの描画
void DrawCubeAnime() {

	for (int cnt = 0; cnt < MAX_CUBE_ANIME; cnt++)
	{
		if (cube_anime[cnt].banime)
		{
			D3DXMATRIX scale_mtx, move_mtx;

			LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			D3DXMatrixIdentity(&scale_mtx);
			D3DXMatrixIdentity(&move_mtx);
			D3DXMatrixIdentity(&cube_anime[cnt].mtxWorld);
			// 移動
			D3DXMatrixTranslation(&move_mtx, cube_anime[cnt].pos.x, cube_anime[cnt].pos.y, cube_anime[cnt].pos.z);
			// 拡大縮小
			D3DXMatrixScaling(&scale_mtx, cube_anime[cnt].scale, cube_anime[cnt].scale, cube_anime[cnt].scale);

			cube_anime[cnt].mtxWorld = cube_anime[cnt].mtxWorld * scale_mtx*move_mtx;

			// 各種行列の設定--状況による設定する
			pDevice->SetTransform(D3DTS_WORLD, &cube_anime[cnt].mtxWorld);

			// FVF設定
			pDevice->SetFVF(FVF_CUBE);


			// 頂点バッファ使う
			pDevice->SetStreamSource(0, g_p3DVertexBuffer, 0, sizeof(CUBE));

			SetTextureNum(cube_anime[cnt].num);
			if (cube_anime[cnt].life % 10 == 0)
			{
				for (int i = 0; i < 24; i += 4)
				{
					pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i, 2);
				}
			}

		//	CreateEffect(cube_anime[cnt].pos.x, cube_anime[cnt].pos.y,100);
			
		}
	}
}