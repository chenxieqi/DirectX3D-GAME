#ifndef TEXT_H_
#define TEXT_H_

#include "main.h"

void InitDebugText();
void UninitDebugText();
void SetDebugTextColor(D3DCOLOR color);
void DebugText(int x, int y, const char* pFormat, ...);

#endif