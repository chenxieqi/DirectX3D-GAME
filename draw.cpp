
// 3D�`��p
// ======================================

#include "draw.h"


#define FVF_VERTEX3D		(D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1|D3DFVF_NORMAL)


static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9  g_pIndexBuffer = NULL;


// -------------------------------------------------------------
//  ��{�֐�
// -------------------------------------------------------------

bool InitDraw(int VerBufCnt,int IndBufCnt, VERTEX_DRAW* v1, WORD* index)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return false; }

	HRESULT hr;


	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_DRAW) * VerBufCnt, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, "���_�o�b�t�@�쐬���s", "�G���[", MB_OK);
		return false;
	}
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * IndBufCnt,//2byte  DWORD--4byte
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,//if DWORD :32
		D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�쐬���s", "�G���[", MB_OK);
		return false;
	}

	CreateVertex(v1, index);
	return true;

}
void UninitDraw()
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
void UpdateDraw()
{

}
void DrawDraw(bool IfLight,bool IfAlphaTest,D3DXMATRIX* g_mtxWorld,int TEXNUM,int VerCnt,int PrimCnt)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, IfLight);
	//pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	// pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// �}�e���A��
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


	// �e��s��̐ݒ�--�󋵂ɂ��ݒ肷��
	pDevice->SetTransform(D3DTS_WORLD, g_mtxWorld);

	// FVF�ݒ�
	pDevice->SetFVF(FVF_VERTEX3D);
	//pDevice->SetTexture(0, g_pTextures[TEXTURE_FIELD000]);
	SetTextureNum(TEXNUM);
	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_DRAW));
	// �C���f�b�N�X�o�b�t�@�g��
	pDevice->SetIndices(g_pIndexBuffer);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VerCnt, 0, PrimCnt);

}

// �o�b�t�@�ǂݍ���
void CreateVertex(VERTEX_DRAW* v1,WORD* index)
{
	// NOWLOADING�̎��ς܂���-----Init

	VERTEX_DRAW* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	// �������ݕ��F
	// �P�A��V��V�̓��e��sizeof(v)/sizeof(VERTEX_3D)*24���R�s�[����
	// memcpy ��for����
	// �Q�A���ڏ���
	// pV[0].pos=D3DXVERCTOR3(-0.5f,0.5f,0.5f);pV[0].color.........
	memcpy(pV, v1, sizeof(v1));
	g_pVertexBuffer->Unlock();


	LPWORD pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	// �C���f�b�N�X�f�[�^����������
	memcpy(pIndex, index, sizeof(index));

	g_pIndexBuffer->Unlock();

}