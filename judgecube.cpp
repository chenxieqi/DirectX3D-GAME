
// �����蔻��̋���L���[�u�[�f�o�b�O�p
// ======================================

#include "judgecube.h"


// ���_�\���̂̐錾
typedef struct
{
	D3DXVECTOR3 pos;	// 3D
	D3DCOLOR color;
}VERTEX_JUDEGCUBE;

// FVF�̐錾(�萔)
#define FVF_VERTEX3D		(D3DFVF_XYZ|D3DFVF_DIFFUSE)

static D3DXMATRIX g_mtx;

VERTEX_JUDEGCUBE cube[2][5];

// -------------------------------------------------------------
//  ��{�֐�
// -------------------------------------------------------------

void InitJudgecube()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cube[i][j].pos = D3DXVECTOR3(0, 0, 0);
			cube[i][j].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
	}
}
void UninitJudgecube()
{

}
void UpdateJudgecube()
{
	D3DXMatrixIdentity(&g_mtx);

}
void DrawJudgecube(D3DXMATRIX mtx)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// FVF�ݒ�
	pDevice->SetFVF(FVF_VERTEX3D);

	g_mtx = mtx;
	// �e��s��̐ݒ�--�󋵂ɂ��ݒ肷��
	pDevice->SetTransform(D3DTS_WORLD, &g_mtx);

	for (int i = 0; i < 2; i++)
	{
		pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &cube[i][0], sizeof(VERTEX_JUDEGCUBE));
	}

}

// ��������
void SetJudgecube(float Width, float Height)
{
	// XY���̕���
	float width = Width;
	float height = Height;
	cube[0][0].pos.x =- width*0.5f;
	cube[0][0].pos.y =  height*0.5f;
	cube[0][1].pos.x =- width*0.5f;
	cube[0][1].pos.y =- height*0.5f;
	cube[0][2].pos.x =  width*0.5f;
	cube[0][2].pos.y =- height*0.5f;
	cube[0][3].pos.x =  width*0.5f;
	cube[0][3].pos.y =  height*0.5f;
	cube[0][4].pos = cube[0][0].pos;

	// ZY���̕���
	cube[1][0].pos.z = - width*0.5f;
	cube[1][0].pos.y =   height*0.5f;
	cube[1][1].pos.z = - width*0.5f;
	cube[1][1].pos.y = - height*0.5f;
	cube[1][2].pos.z =   width*0.5f;
	cube[1][2].pos.y = - height*0.5f;
	cube[1][3].pos.z =   width*0.5f;
	cube[1][3].pos.y =   height*0.5f;
	cube[1][4].pos = cube[1][0].pos;
}