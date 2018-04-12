
// 地面
// ======================================
#include "Floor.h"

#define MAX_TEX		(10)


static LPD3DXMESH g_pMesh[FLOOR_MAX];
static DWORD g_nMaterialNum[FLOOR_MAX];
static LPD3DXBUFFER g_pMaterials[FLOOR_MAX];
static LPDIRECT3DTEXTURE9 g_pXTextures[FLOOR_MAX][MAX_TEX];
static D3DXMATRIX g_mtxWorld[FLOOR_MAX];

static const char XmodFileName[FLOOR_MAX][256] = { { "data/model/floor2.x" },{ "data/model/floor1.x" },{ "data/model/floor.x" } };

static float g_rot_s,g_rot_m,g_rot_l;
static D3DXMATRIX g_mtxRot_s, g_mtxRot_m, g_mtxRot_l;

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

// 初期化
bool InitFloor()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	for (int i = 0; i < FLOOR_MAX; i++)
	{
		g_pMesh[i] = NULL;
		g_nMaterialNum[i] = 0;
		g_pMaterials[i] = NULL;


		HRESULT hr;
		LPD3DXBUFFER pAdjacency = NULL;


		hr = D3DXLoadMeshFromX(XmodFileName[i], D3DXMESH_SYSTEMMEM, pDevice, &pAdjacency, &g_pMaterials[i], NULL, &g_nMaterialNum[i], &g_pMesh[i]);
		if (FAILED(hr)) {
			MessageBox(NULL, "FLOOR-Xファイル読み込み失敗", "エラー", MB_OK);
			return false;
		}
		// 最適化処理
		hr = g_pMesh[i]->OptimizeInplace(
			D3DXMESHOPT_COMPACT |// 使わない頂点と面を削除
			D3DXMESHOPT_ATTRSORT |// 
			D3DXMESHOPT_VERTEXCACHE,// キャッシュのヒット効率を上げる
			(DWORD*)pAdjacency->GetBufferPointer(),
			NULL, NULL, NULL
		);
		if (FAILED(hr)) {
			MessageBox(NULL, "最適化処理失敗", "エラー", MB_OK);
			return false;
		}

		D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH + 1];
		LPD3DXMESH pCloneMesh;// 高速、編集できない
		g_pMesh[i]->GetDeclaration(elements);
		hr = g_pMesh[i]->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, elements, pDevice, &pCloneMesh);
		if (FAILED(hr)) {
			MessageBox(NULL, "メッシュクローン失敗", "エラー", MB_OK);
			return false;
		}
		g_pMesh[i]->Release();
		g_pMesh[i] = pCloneMesh;

		LPD3DXMATERIAL pMaterials = (LPD3DXMATERIAL)g_pMaterials[i]->GetBufferPointer();
		for (DWORD j = 0; j < g_nMaterialNum[i]; j++)
		{
			g_pXTextures[i][j] = NULL;
			if (pMaterials[j].pTextureFilename != NULL && strlen(pMaterials[j].pTextureFilename) > 0)
			{
				hr = D3DXCreateTextureFromFile(pDevice, pMaterials[j].pTextureFilename, &g_pXTextures[i][j]);
				if (FAILED(hr)) {
					MessageBox(NULL, "失敗", "エラー", MB_OK);
					return false;
				}
			}
			else
			{
				hr = D3DXCreateTextureFromFile(pDevice, "data/texture/yellow.jpg", &g_pXTextures[i][j]);
				if (FAILED(hr)) {
					MessageBox(NULL, "失敗", "エラー", MB_OK);
					return false;
				}
			}
		}
		D3DXMatrixIdentity(&g_mtxWorld[i]);
	}

	D3DXMatrixTranslation(&g_mtxWorld[FLOOR_S], 0.0f, 0.0f,  -1.0f);
	D3DXMatrixTranslation(&g_mtxWorld[FLOOR_M], 0.0f, 0.0f, -1.0f);
	D3DXMatrixTranslation(&g_mtxWorld[FLOOR_L], 0.0f, 0.0f, 0.0f);

	g_rot_s = -0.001f;
	g_rot_m = 0.005f; 
	g_rot_l = -0.01f;

	return true;
}

// 解放
void UninitFloor()
{
	for (int i = 0; i < FLOOR_MAX; i++)
	{
		if (g_pMaterials[i] != NULL) {
			g_pMaterials[i]->Release();
			g_pMaterials[i] = NULL;
		}
	}
}

// 更新
void UpdateFloor()
{
	D3DXMatrixRotationY(&g_mtxRot_s, g_rot_s);
	D3DXMatrixRotationY(&g_mtxRot_m, g_rot_m);
	D3DXMatrixRotationY(&g_mtxRot_l, g_rot_l);
}

// 描画処理
void DrawFloor()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	D3DXMatrixMultiply(&g_mtxWorld[FLOOR_S], &g_mtxWorld[FLOOR_S], &g_mtxRot_s);
	D3DXMatrixMultiply(&g_mtxWorld[FLOOR_M], &g_mtxWorld[FLOOR_M], &g_mtxRot_m);
	D3DXMatrixMultiply(&g_mtxWorld[FLOOR_L], &g_mtxWorld[FLOOR_L], &g_mtxRot_l);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	for (int i = 0; i < FLOOR_MAX; i++)
	{
		LPD3DXMATERIAL pMaterials = (LPD3DXMATERIAL)g_pMaterials[i]->GetBufferPointer();

		for (int j = 0; j < g_nMaterialNum[i]; j++)
		{
			D3DMATERIAL9  mat = pMaterials[j].MatD3D;

			mat.Ambient = mat.Diffuse;
			mat.Emissive.r = 0.3f;
			mat.Emissive.g = 0.3f;
			mat.Emissive.b = 0.3f;
			mat.Emissive.a = 1.0f;
			pDevice->SetMaterial(&mat);

			pDevice->SetTexture(0, g_pXTextures[i][j]);

			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld[i]);


			//SetTextureNum(TEXTURE_WATER);
			g_pMesh[i]->DrawSubset(j);
		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


}

// -------------------------------------------------------------
//  ゲット用関数
// -------------------------------------------------------------

// ゲット地面回転速度
const float GetFloorRot(int floorNum)
{
	switch ((FLOOR_NUM)floorNum)
	{
	case FLOOR_S:
		return g_rot_s;
		break;
	case FLOOR_M:
		return g_rot_m;
		break;
	case FLOOR_L:
		return g_rot_l;
		break;
	default:
		break;
	}
}