
// �n�ʔ���͈́[�f�o�b�O�p
// ======================================

#include "grid.h"

// ���_�\���̂̐錾
typedef struct
{
	D3DXVECTOR3 pos;	// 3D
	D3DCOLOR color;
}VERTEX_GRID;

// FVF�̐錾(�萔)
#define FVF_VERTEX3D		(D3DFVF_XYZ|D3DFVF_DIFFUSE)
#define MAX_GRID			(72)

static D3DXMATRIX g_mtxGrid;

VERTEX_GRID grid[MAX_GRID];

// -------------------------------------------------------------
//  ��{�֐�
// -------------------------------------------------------------

void InitGrid(void) 
{
	int degree = 0;
	for (int i = 0; i < MAX_GRID; i++)
	{
		grid[i].pos.x = cosf(D3DXToRadian(degree))*FLOOR_L_R;
		grid[i].pos.z = sinf(D3DXToRadian(degree))*FLOOR_L_R;
		grid[i].pos.y = 0;
		grid[i].color= D3DCOLOR_RGBA(255, 0, 255, 255);

		degree += 10;
	}

}
void UninitGrid(void) {

}
void UpdateGrid(void) {
	// ���[���h�ϊ��s��
	// �������Ȃ��i�P�ʍs��j
	D3DXMatrixIdentity(&g_mtxGrid);

}
void DrawGrid(void) {

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	
	// FVF�ݒ�
	pDevice->SetFVF(FVF_VERTEX3D);



	// �e��s��̐ݒ�--�󋵂ɂ��ݒ肷��
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxGrid);


	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 71, &grid[0], sizeof(VERTEX_GRID));

}