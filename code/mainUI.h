#ifndef _MAINUI_H_
#define _MAINUI_H_

#define UI_WIDTH	(1280)
#define UI_HEIGHT	(800)

#define HP_WIDTH	(420)
#define HP_HEIGHT	(27)

#define BOSS_HP_WIDTH	(962)
#define BOSS_HP_HEIGHT	(10)

#define ENERGE_WIDTH	(173)
#define ENERGE_HEIGHT	(169)

#include "main.h"

void InitTimer();
void UpdateTimer();
void UpdateMainUI();
void DrawMainUI();
void UpdatePauseTimer();


#endif 
