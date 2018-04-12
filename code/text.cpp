
// テキスト
// ======================================

#include "text.h"
#include <stdio.h>


#ifdef _DEBUG
static LPD3DXFONT g_pFont = NULL;
#endif

static D3DCOLOR g_DebugTextColor = D3DCOLOR_ARGB(255, 255, 255, 255);

void InitDebugText()
{
#ifdef _DEBUG
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	if (pDevice == NULL)
	{
		return;
	}

	D3DXCreateFont(pDevice,22,0,0,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"MS コジック",&g_pFont);
#endif
}
void UninitDebugText()
{
#ifdef _DEBUG
	if (g_pFont)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
#endif
}
void SetDebugTextColor(D3DCOLOR color)
{
	g_DebugTextColor = color;
}
// テキスト描画（座標、文字列）
void DebugText(int x, int y, const char* pFormat, ...)
{
#ifdef _DEBUG
	va_list argp;
	char strBuf[512];
	va_start(argp, pFormat);
	vsprintf_s(strBuf, 512, pFormat, argp);
	va_end(argp);

	RECT rect ={x,y,SCREEN_WIDTH,SCREEN_HEIGHT};

	g_pFont->DrawText(NULL,strBuf,-1,&rect,DT_LEFT,g_DebugTextColor);
#endif
}

