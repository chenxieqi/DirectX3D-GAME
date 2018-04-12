#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

void CameraInit(void);
void CameraUninit(void);
void CameraUpdate(void);
const D3DXMATRIX GetCamMtx(void);
const D3DXVECTOR3 GetCameraDir();
const D3DXVECTOR3 GetCameraAt();
const D3DXVECTOR3 GetCameraEye();

#endif