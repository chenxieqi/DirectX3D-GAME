#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();
void UpdateScore();
void PlayerPlusFloor();
void PlayerTurn();
void IsPlayerInStage();
void PlayerCollisionDetection();
void SetPlayerMatrix();
const D3DXMATRIX GetPlayerMtx();
const D3DXVECTOR3 GetPlayerPos();
const float GetPlayerLife();
const float GetPLayerEnerge();
const int GetPlayerScoreInc();
const int GetPlayerScore();
const D3DXVECTOR3 GetPlayerPmin();
const D3DXVECTOR3 GetPlayerPmax();
void PlayerBAttack();
float VecToVecDegree(D3DXVECTOR3* firstVec, D3DXVECTOR3* secondVec);
#endif // !_PLAYER_H_
