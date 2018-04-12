#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

#define PAUSE_WIDTH		(632)
#define PAUSE_HEIGHT	(326)

void InitGame();
void UninitGame();
void UpdateGame();
void DrawGame();
void GameOver();
void GameNow();
void GameNotNow();
void DrawPause();
const bool IfPause();

#endif // 
