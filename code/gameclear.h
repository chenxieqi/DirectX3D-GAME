#ifndef _GAMECLEAR_H_
#define _GAMECLEAR_H_

#include "main.h"

#define CLEAR_WIDTH		(371)
#define CLEAR_HEIGHT	(123)


void InitGameClear(void);
void UninitGameClear(void);
void UpdateGameClear(bool gameclear);
void DrawGameClear(void);

#endif
