
//-------------�t�F�C�h�C���E�t�F�C�h�A�E�g����-----------------------
// ------------------------------------------------------------
#include "fade.h"

#define FADE_SC		(1.0f)

static int g_gameFlag = 0;	 // �Q�[�����[�h�t���O
static int g_fadeTime;		
static bool g_bUse;			 // �g���Ă��邩
static bool g_bchangeFlag;

static float g_rotSpeed;
static float g_scaleSpeed;

// �s��
static D3DXMATRIX g_mtxWolrd, g_mtxRot, g_mtxSca;

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9  g_pIndexBuffer = NULL;


// -------------------------------------------------------------
//  ��{�֐�
// -------------------------------------------------------------

// ������
bool InitFade()
{

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return false; }

	HRESULT hr;

	VERTEX_3D v1[] = {
		{ D3DXVECTOR3(-FADE_SC, FADE_SC,-FADE_SC),  D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR3(FADE_SC, FADE_SC, -FADE_SC),   D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR3(-FADE_SC,-FADE_SC,-FADE_SC), D3DXVECTOR3(0.0f,0.0f,-1.0f) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR3(FADE_SC,-FADE_SC, -FADE_SC),  D3DXVECTOR3(0.0f,0.0f,-1.0f) ,D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,1.0f) }
	};

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, "���_�o�b�t�@�쐬���s", "�G���[", MB_OK);
		return false;
	}
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * 4,//2byte  DWORD--4byte
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,//if DWORD :32
		D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�쐬���s", "�G���[", MB_OK);
		return false;
	}

	VERTEX_3D* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	memcpy(pV, &v1, sizeof(v1));
	g_pVertexBuffer->Unlock();


	LPWORD pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	// �C���f�b�N�X�f�[�^����������
	pIndex[0] = 2;
	pIndex[1] = 0;
	pIndex[2] = 3;
	pIndex[3] = 1;

	g_pIndexBuffer->Unlock();

	g_fadeTime = 0;
	g_bUse = false;

	g_rotSpeed = 0.01;
	g_scaleSpeed = 5.0f;
	g_bchangeFlag = false;
}

// ���
void UninitFade()
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

// �X�V
void UpdateFade()
{
	g_gameFlag = GetGameFlag();
	if (g_bUse)
	{		

		D3DXMatrixIdentity(&g_mtxWolrd);
		D3DXMatrixRotationZ(&g_mtxRot, g_rotSpeed);
		D3DXMatrixScaling(&g_mtxSca, g_scaleSpeed, g_scaleSpeed, g_scaleSpeed);
		g_mtxWolrd = g_mtxWolrd*g_mtxRot*g_mtxSca;

			g_fadeTime++;
			g_rotSpeed += 0.2f;
			
		if (g_fadeTime <= 60)
		{
			g_scaleSpeed += 2.0f;
		}
		if (g_fadeTime > 60)
		{
			g_scaleSpeed -= 2.0f;
			if (!g_bchangeFlag)
			{
				ChangeFlag();
				g_bchangeFlag = true;
			}
		}

		if (g_fadeTime > 120)
		{
			g_bUse = false;
			g_bchangeFlag = false;
			g_rotSpeed = 0.01;
			g_scaleSpeed = 5.0f;
			g_fadeTime = 0;
			D3DXMatrixIdentity(&g_mtxWolrd);
			D3DXMatrixIdentity(&g_mtxRot);
			D3DXMatrixIdentity(&g_mtxSca);

		}

	}
}

// �`�揈��
void DrawFade()
{
	if (g_bUse)
	{
		LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
		// �������ݎ��}�X�N�J���[�̐ݒ�
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
		
		// z�ݒ�
		pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		// �}�X�N�`��	
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// FVF�ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		SetTextureNum(TEXTURE_FADE);
		// �e��s��̐ݒ�--�󋵂ɂ��ݒ肷��
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWolrd);

		pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_3D));
		// �C���f�b�N�X�o�b�t�@�g��
		pDevice->SetIndices(g_pIndexBuffer);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);

		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	}
}

// �t�F�C�h�̐���
void CreatFade()
{
	g_bUse = true;
}

// -------------------------------------------------------------
//  �Q�b�g�p�֐�
// -------------------------------------------------------------

// �g���Ă��邩
bool Isfade()
{
	return g_bUse;
}

// �Q�b�g�Q�[���t���O
int IsChangeFlag() {
	return g_gameFlag;
}

// -------------------------------------------------------------
//  ���̂ق��֐�
// -------------------------------------------------------------

// �Q�[���t���O�`�F���W
void FlagBeChange(int num)
{
	g_gameFlag = num;
}

// �Q�[���t���O�`�F���W����
void ChangeFlag()
{
	
	if (g_gameFlag < END)
	{
		g_gameFlag++;
		if (g_gameFlag != TUTORIAL)
		{
			StopSound();
		}
		if (g_gameFlag == GAME)
		{
			SetStart();
			
		}
		if (g_gameFlag == FSCORE)
		{
		
			PlaySound(SOUND_LABEL_SE_CHARGE);
			PlaySound(SOUND_LABEL_SE_SCORE);
		}
	}
	else
	{
		g_gameFlag = TITLE;
		InitGame();
		InitGameClear();
		InitTutorial();
		InitResult();
		PlaySound(SOUND_LABEL_BGM000);
	}
}