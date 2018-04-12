
// 3D描画時使うテクスチャの読み込み
// ======================================

#include "texture.h"


static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_MAX];


bool InitTexture() 
{
	
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return FALSE; }

	HRESULT hr;

	for (int i = 0; i < TEXTURE_MAX; i++) {

		hr = D3DXCreateTextureFromFile(pDevice, g_Texture[i].FileName, &g_pTextures[i]);

	}
	if (FAILED(hr)) {
		MessageBox(NULL, "テクスチャファイル読み込み失敗", "エラー", MB_OK);
		return false;
	}
}
void UninitTexture()
{
	for (int i = 0; i < TEXTURE_MAX; i++) {
		if (g_pTextures[i] != NULL) {
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}

}

//セットテクスチャ（テクスチャ番号）
void SetTextureNum(int TEXTURE)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetTexture(0, g_pTextures[TEXTURE]);
}