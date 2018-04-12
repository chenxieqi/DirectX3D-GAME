#ifndef _GAMEFADE_H_
#define _GAMEFADE_H_

#include "main.h"

#define START_WIDTH		(291)
#define START_HEIGHT	(123)

#define TIMEUP_WIDTH	(371)
#define TIMEUP_HEIGHT	(123)

#define BAR_WIDTH		(1280)
#define BAR_HEIGHT		(123)


void InitGameFade(void);
void UninitGameFade(void);
void UpdateGameFade(void);
void DrawGameFade(void);
void SetStart(void);
void SetTimeUp(void);
const bool GetGameFade();


#endif