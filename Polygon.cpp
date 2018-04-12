
// --------------------2D-Polygonの描画-----------------------

#include <math.h>
#include "main.h"
#include "Polygon.h"


static LPDIRECT3DTEXTURE9 g_pTextures[T_MAX];			// テクスチャ
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;		// 頂点バッファ
static D3DCOLOR g_PolygonColor = (255, 255, 255);			// 頂点色

static float g_fAngle = 0.0f;								// 回転角度
static float g_fRotationOffsetX = 0.0f;						// 回転中心ｘ座標
static float g_fRotationOffsetY = 0.0f;						// 回転中心ｙ座標
static float g_fScaleX = 1.0f;								// 横幅拡大縮小
static float g_fScaleY = 1.0f;								// 縦幅拡大縮小
static float g_fScaleOffsetX = 0.0f;						// 拡大縮小中心
static float g_fScaleOffsetY = 0.0f;						// 拡大縮小中心

//======構造体======
typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR	color;
	D3DXVECTOR2 texcoord;
}VERTEX_2D;

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )


bool PolygonInit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		return false;
	}

	//load texture & error check

	HRESULT hr;

	for (int i = 0; i < T_MAX; i++)
	{
		hr = D3DXCreateTextureFromFile(pDevice, g_aTextureFileNames[i], &g_pTextures[i]);
		if (FAILED(hr))
		{
			MessageBox(NULL, "テクスチャ読み込み失敗", "error", MB_OK);
			return false;
		}
	}

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "頂点バッファ生成失敗", "error", MB_OK);
		return false;
	}

	return true;
}
void PolygonUninit(void)
{
	if (g_pVertexBuffer)
	{//release
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	for (int i = 0; i < T_MAX; i++)
	{
		if (g_pTextures != NULL)
		{//release texture
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}
void PolygonUpdate(void)
{
	//
}

// テクスチャ回転
void SetPolygonRotation(float cx, float cy, float angle)
{
	g_fRotationOffsetX = cx;
	g_fRotationOffsetY = cy;
	g_fAngle = angle;

}

// セットテクスチャカラー
void SetPolygonColor(D3DCOLOR nColor) {
	g_PolygonColor = nColor;
}

// ポリゴン描画処理（テクスチャ番号、テクスチャ左上座標、テクスチャ横縦幅、
// 用意したテクスチャのピクセル、描画したいテクスチャの部分の座標と幅高さ、回転するか）
void PolygonDraw(TEXTURE_ENUM texNum, float dx, float dy, float dw, float dh, int tw, int th, int tcx, int tcy, int tcw, int tch, bool bAffine)
{

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		return;
	}

	if (bAffine) { CreateVertexAffine(dx, dy, dw, dh, tw, th, tcx, tcy, tcw, tch); }
	else { CreateVertex(dx, dy, dw, dh, tw, th, tcx, tcy, tcw, tch); }

	// FVF（今から使用する頂点情報）の設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_2D));


	pDevice->SetTexture(0, g_pTextures[texNum]);

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vtx[0], sizeof(VERTEX_2D));
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

// 頂点バッファ生成（テクスチャ座標、テクスチャのピクセル、描画したいテクスチャの部分の座標と幅高さ）
void CreateVertex(float dx, float dy, float dw, float dh, int tw, int th, int tcx, int tcy, int tcw, int tch)
{
	VERTEX_2D* pV;

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	pV[0].pos = D3DXVECTOR4(-0.5f + dx + 0.0f, -0.5f + dy + 0.0f, 1.0f, 1.0f);
	pV[1].pos = D3DXVECTOR4(-0.5f + dx + dw, -0.5f + dy + 0.0f, 1.0f, 1.0f);
	pV[2].pos = D3DXVECTOR4(-0.5f + dx + 0.0f, -0.5f + dy + dh, 1.0f, 1.0f);
	pV[3].pos = D3DXVECTOR4(-0.5f + dx + dw, -0.5f + dy + dh, 1.0f, 1.0f);

	pV[0].color =
		pV[1].color =
		pV[2].color =
		pV[3].color = g_PolygonColor;

	float u0 = (float)tcx / tw;
	float v0 = (float)tcy / th;
	float u1 = (float)(tcx + tcw) / tw;
	float v1 = (float)(tcy + tch) / th;
	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	g_pVertexBuffer->Unlock();
}

// 頂点回転処理
void CreateVertexAffine(float dx, float dy, float dw, float dh, int tw, int th, int tcx, int tcy, int tcw, int tch)
{
	VERTEX_2D* pV;

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	float fRotationOffsetX = (g_fRotationOffsetX - g_fScaleOffsetX)*g_fScaleX;
	float fRotationOffsetY = (g_fRotationOffsetY - g_fScaleOffsetY)*g_fScaleY;
	float x = (0.0f - g_fScaleOffsetX) *g_fScaleX + (g_fScaleOffsetX * g_fScaleX);
	float x_w = (tcw - g_fScaleOffsetX)*g_fScaleX + (g_fScaleOffsetX * g_fScaleX);
	float y = (0.0f - g_fScaleOffsetY) *g_fScaleY + (g_fScaleOffsetY * g_fScaleY);
	float y_h = (tch - g_fScaleOffsetY)*g_fScaleY + (g_fScaleOffsetY * g_fScaleY);

	x -= fRotationOffsetX;
	x_w -= fRotationOffsetX;
	y -= fRotationOffsetY;
	y_h -= fRotationOffsetY;
	dx += fRotationOffsetX - 0.5f;
	dy += fRotationOffsetY - 0.5f;

	pV[0].pos = D3DXVECTOR4(x	*cosf(g_fAngle) - y*sinf(g_fAngle) + dx, x *sinf(g_fAngle) + y*cosf(g_fAngle) + dy, 1.0f, 1.0f);
	pV[1].pos = D3DXVECTOR4(x_w *cosf(g_fAngle) - y*sinf(g_fAngle) + dx, x_w *sinf(g_fAngle) + y*cosf(g_fAngle) + dy, 1.0f, 1.0f);
	pV[2].pos = D3DXVECTOR4(x	*cosf(g_fAngle) - y_h*sinf(g_fAngle) + dx, x *sinf(g_fAngle) + y_h*cosf(g_fAngle) + dy, 1.0f, 1.0f);
	pV[3].pos = D3DXVECTOR4(x_w *cosf(g_fAngle) - y_h*sinf(g_fAngle) + dx, x_w *sinf(g_fAngle) + y_h*cosf(g_fAngle) + dy, 1.0f, 1.0f);

	pV[0].color =
		pV[1].color =
		pV[2].color =
		pV[3].color = g_PolygonColor;

	float u0 = (float)tcx / tw;
	float v0 = (float)tcy / th;
	float u1 = (float)(tcx + tcw) / tw;
	float v1 = (float)(tcy + tch) / th;
	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	g_pVertexBuffer->Unlock();
}

// セットポリゴン大きさ
void SetPolygonScale(float cx, float cy, float sx, float sy) {
	g_fScaleX = sx;
	g_fScaleY = sy;
	g_fScaleOffsetX = cx;
	g_fScaleOffsetY = cy;
}