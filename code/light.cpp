
// 光
// ======================================

#include "main.h"
#include "light.h"

static D3DLIGHT9 light, light1;
static D3DXVECTOR3 vecDir, vecDir1;

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

void InitLight()
{
	ZeroMemory(&light, sizeof(light));
	ZeroMemory(&light1, sizeof(light1));
	vecDir = { {1.0,-1.0f,0.0f} };				// 光が差す方向
	vecDir1 = { { -50.0f,-50.0f,0.0f } };
}

void UninitLight()
{

}

void UpdateLight()
{
	light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;

	light.Ambient.r = 0.1f;
	light.Ambient.g = 0.1f;
	light.Ambient.b = 0.1f;
	light.Ambient.a = 0.1f;
	
	light1.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVec3Normalize((D3DXVECTOR3*)&light1.Direction, &vecDir1);
	light1.Diffuse.r = 1.0f;
	light1.Diffuse.g = 1.0f;
	light1.Diffuse.b = 0.0f;
	light1.Diffuse.a = 0.2f;
		 
	light1.Ambient.r = 0.1f;
	light1.Ambient.g = 0.1f;
	light1.Ambient.b = 0.0f;
	light1.Ambient.a = 0.1f;

}

void DrawLight()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetLight(0, &light);// ライト番号０～３
	pDevice->LightEnable(0, TRUE);

//	pDevice->SetLight(1, &light1);// ライト番号０～３
//	pDevice->LightEnable(1, TRUE);

}

// -------------------------------------------------------------
//  ゲット用関数
// -------------------------------------------------------------

// ゲット光方向ベクトル
const D3DXVECTOR3 GetLightVec()
{
	return vecDir;
}