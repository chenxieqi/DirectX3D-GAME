
// Xモデル読み込み
// ======================================

#include "Xmodel.h"

#define MAX_TEX		(10)

static LPD3DXMESH g_pMesh[XMODEL_MAX];
static DWORD g_nMaterialNum[XMODEL_MAX];
static LPD3DXBUFFER g_pMaterials[XMODEL_MAX];
static LPDIRECT3DTEXTURE9 g_pXTextures[XMODEL_MAX][MAX_TEX];
static LPDIRECT3DTEXTURE9 g_pXBlack;

static const char XmodFileName[XMODEL_MAX][256] = {
{ "data/model/player_stand.x" },		  // プレイヤー
{ "data/model/player_attack.x" },		  // プレイヤー攻撃
{ "data/model/player_charge.x" },		  // プレイヤーチャージ
{ "data/model/enemy.x" },				  // エネミー
{ "data/model/bakudan.x" },				  // 弾
{ "data/model/candybullet.x" }, 		  // キャンディーバクダン
{ "data/model/mark.x" }					  // 弾mark
};


// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

bool InitXmodel()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	for (int i = 0; i < XMODEL_MAX; i++)
	{
		g_pMesh[i] = NULL;
		g_nMaterialNum[i] = 0;
		g_pMaterials[i] = NULL;


		HRESULT hr;
		LPD3DXBUFFER pAdjacency = NULL;


		hr = D3DXLoadMeshFromX(XmodFileName[i], D3DXMESH_SYSTEMMEM, pDevice, &pAdjacency, &g_pMaterials[i], NULL, &g_nMaterialNum[i], &g_pMesh[i]);
		if (FAILED(hr)) {
			MessageBox(NULL, "Xファイル読み込み失敗", "エラー", MB_OK);
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
		for (DWORD j = 0; j < g_nMaterialNum[i];j++)
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
				hr = D3DXCreateTextureFromFile(pDevice, "data/texture/purple.jpg", &g_pXTextures[i][j]);
				if (FAILED(hr)) {
					MessageBox(NULL, "失敗", "エラー", MB_OK);
					return false;
				}
			}
		}


	}

	D3DXCreateTextureFromFile(pDevice, "data/texture/grey.png", &g_pXBlack);

	return true;
}

void UninitXmodel()
{
	for (int i = 0; i < XMODEL_MAX; i++)
	{
		if (g_pMaterials[i] != NULL) {
			g_pMaterials[i]->Release();
			g_pMaterials[i] = NULL;
		}
	}
}

void UpdateXmodel()
{
}

// 描画（行列、テクスチャありなし、テクスチャナンバー）
void DrawXmodel(D3DXMATRIX mtx,int iftex, XMODEL_NUM num)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	LPD3DXMATERIAL pMaterials = (LPD3DXMATERIAL)g_pMaterials[num]->GetBufferPointer();

	for (int i = 0; i < g_nMaterialNum[num]; i++)
	{
		
		//pMaterials->MatD3D
		D3DMATERIAL9  mat = pMaterials[i].MatD3D;
		//pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME );
		//pDevice->SetRenderState(D3DRS_DITHERENABLE, true);
		//pDevice->SetRenderState(D3DRS_LASTPIXEL, true);

		mat.Ambient = mat.Diffuse;
		mat.Emissive.r = 0.3f;
		mat.Emissive.g = 0.3f;
		mat.Emissive.b = 0.3f;
		mat.Emissive.a = 1.0f;
		pDevice->SetMaterial(&mat);


		if (0==iftex)
		{
			pDevice->SetTexture(0, g_pXBlack);

		}
		else {
			pDevice->SetTexture(0, g_pXTextures[num][i]);

		}
		pDevice->SetTransform(D3DTS_WORLD, &mtx);

		g_pMesh[num]->DrawSubset(i);
	}


}
