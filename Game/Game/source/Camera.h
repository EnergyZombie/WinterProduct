#pragma once
#include "DxLib.h"
class Camera {
public:
	Camera(class ModeGame* game) { _game = game; }
	virtual bool Process();
	void SetPos(VECTOR pos) { _vPos = pos; }
	void SetPosX(float x) { _vPos.x = x; }
	void SetPosY(float y) { _vPos.y = y; }
	void SetPosZ(float z) { _vPos.z = z; }
	void SetTarget(VECTOR pos) { _vTarget = pos; }

	VECTOR GetPos()const { return _vPos; }
	float  GetPosY()const { return _vPos.y; }
	VECTOR GetTarget()const { return _vTarget; }

	void AddPosX(float x) { _vPos.x += x; }
	void AddPosY(float y) { _vPos.y += y; }
	void AddPosZ(float z) { _vPos.z += z; }
	void AddPos(VECTOR pos) { _vPos = VAdd(_vPos, pos); }
protected:
	VECTOR	_vPos;					// 位置（本来指定したい場所）
	VECTOR	_vPosAdjust;			// 位置（補正した位置）
	VECTOR	_vTarget;				// 距離
	float	_clipNear, _clipFar;	// クリップ
public:
	float RotateY = 0;
	float RotateX = 0;
	MATRIX Matrix;
private:
	class ModeGame* _game;
 };