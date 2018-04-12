
// ステンシルバッファ（影用）
// ======================================

#include "stencil.h"


static LPDIRECT3DDEVICE9 pDevice;


void SetMask()
{

	// z設定
	//pDevice->SetRenderState(D3DRS_ZENABLE, true);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER)
	pDevice = GetD3DDevice();
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	// 書き込み時マスクカラーの設定
	pDevice->SetRenderState(D3DRS_STENCILREF, 0);
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);



	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void StencilClear()
{
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	// ステンシルを無効化しバッファをクリア
	pDevice->SetRenderState(D3DRS_STENCILENABLE, false);
	pDevice->Clear(0, NULL, D3DCLEAR_STENCIL, 0, 1.0f, static_cast<DWORD>(0xff));
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
