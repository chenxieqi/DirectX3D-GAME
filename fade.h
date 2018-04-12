#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

bool InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();
void CreatFade();
bool Isfade();
int IsChangeFlag();
void FlagBeChange(int num);
void ChangeFlag();

#endif 
