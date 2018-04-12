#ifndef _FINALSCORE_H_
#define _FINALSCORE_H_

#include "main.h"

void InitFinalScore();
void UninitFinalScore();
void UpdateFinalScore();
void DrawFinalScore(int score, int dig, float x, float y, bool bZero);
const int GetFinalScore();
#endif // 