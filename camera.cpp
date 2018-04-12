
// �L������
// ======================================

#include "camera.h"

static D3DXVECTOR3 g_eye; 	// �J�������W
static D3DXVECTOR3 g_at;	// ���Ă�ꏊ
static D3DXVECTOR3 g_up;	// �J�����̏�̕���
static D3DXVECTOR3 g_front;	// �O
static D3DXVECTOR3 g_right;	// �E

static D3DXMATRIX g_mtxView;
static D3DXMATRIX g_mtxprj;

static float g_radian;

// -------------------------------------------------------------
//  ��{�֐�
// -------------------------------------------------------------

void CameraInit(void)
{
	g_eye = { {0.0f,10.0f,-5.0f} };
	g_at = { { 0.0f,0.0f,0.0f } };
	g_up = { { 0.0f,1.0f,0.0f } };
	g_front = { { 0.0f,0.0f,0.0f } };
	g_right = { { 0.0f,0.0f,0.0f } };
	g_radian = 60;

}
void CameraUninit(void)
{

}
void CameraUpdate(void)
{
	D3DXVECTOR3 front;
	D3DXVECTOR3 at;
	D3DXVECTOR3 eye;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	int gameflag = GetGameFlag();

	if (!Isfade()|| !GetGameFade())
	{
		g_at = D3DXVECTOR3(GetPlayerPos().x*0.8f + 0.0f, GetPlayerPos().y*0.2 + 0.0f, GetPlayerPos().z*0.8f +0.0f);
		g_eye = D3DXVECTOR3(GetPlayerPos().x + 0.0f, GetPlayerPos().y*0.7 +150.0f, GetPlayerPos().z - 100.0f);
	}

	if (gameflag != GAME|| Isfade()||GetGameFade())
	{
		g_at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_eye = D3DXVECTOR3(0.0f, 5.0f, -200.0f);
	}
	at = g_at;
	eye = g_eye;
	up = g_up;
	front = g_front;
	right = g_right;
	
	// �O�ړ�
	// �O���������߂�
	front = at - eye;
	// ���K���i�m�[�}���C�Y�j����
	D3DXVec3Normalize(&front,&front);

	D3DXVECTOR3 vec;// �ړ�����
	vec = front;
	vec.y = 0.0f;
	D3DXVec3Normalize(&vec, &vec);

	// �E�����x�N�g�������߂�
	// (�K���ȏ�����x�N�g�������A����ƑO�����x�N�g���̊O�ς����߂�
	// �[���Q�̃x�N�g���ɑ΂��Ē��p�̃x�N�g�����o���オ��)
	// �Q�̃x�N�g���̂Ȃ����ʂ̌����Ă����
	D3DXVec3Cross(&right, &front, &up);// return�l�͏o�͂̃A�h���X
	//g_right���K������
	D3DXVec3Normalize(&right, &right);

	g_at = at;
	g_eye = eye;
	g_front = front;
	g_right = right;
	g_up = up;

	D3DXMatrixLookAtLH(&g_mtxView, &g_eye, &g_at, &g_up);

	// �v���W�F�N�V�����i�p�[�X�y�N�e�B�u�j�s��̍쐬
	D3DXMatrixPerspectiveFovLH(&g_mtxprj,
		D3DXToRadian(g_radian),//��p(�Y�[���C���D�Y�[���A�E�g)�̔���D3DX_PI wii/openGL-�x�� �ꍇ�ɂ��ύX����̂�����B
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,// ��ʂ̕����鍂��--float�d�v
		0.1f,// >0�j�A�N���b�v
		2000);// �t�@�[�N���b�v100 or 1000
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxprj);
}

// -------------------------------------------------------------
//  �Q�b�g�p�֐�
// -------------------------------------------------------------

// �Q�b�g�s��
const D3DXMATRIX GetCamMtx(void)
{
	return g_mtxView;
}

// �Q�b�g�����Ă����
const D3DXVECTOR3 GetCameraDir()
{
	return g_front;
}

// �Q�b�g���_
const D3DXVECTOR3 GetCameraAt()
{
	return g_at;
}

// �Q�b�g���W
const D3DXVECTOR3 GetCameraEye()
{
	return g_eye;
}
