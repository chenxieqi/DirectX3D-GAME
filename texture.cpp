
// 3D�`�掞�g���e�N�X�`���̓ǂݍ���
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
		MessageBox(NULL, "�e�N�X�`���t�@�C���ǂݍ��ݎ��s", "�G���[", MB_OK);
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

//�Z�b�g�e�N�X�`���i�e�N�X�`���ԍ��j
void SetTextureNum(int TEXTURE)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetTexture(0, g_pTextures[TEXTURE]);
}