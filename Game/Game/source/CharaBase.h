#pragma once
#include"ObjectBase.h"

class CharaBase :public ObjectBase{
public :
	CharaBase(class ObjectServer* server);

	//
	bool Renderer()override;

	//
	bool IsHitMap();
	double GetRadian()const { return radian; }
	float GetCollSubY()const { return _colSubY; }
	void AddMove(Vector3D add) { _move += add; }
	ObjectBase* GetOnObject()const { return _onObj; }
protected:
	double radian;
	bool	_is_stand;		//�I�u�W�F�N�g�̏�ɗ����Ă��邩
	Vector3D _move;
	float _play_time;
	float _total_time;

	ObjectBase* _onObj;
public:
	float _colSubY;	// �R���W�������莞��Y�␳(���ʒu�j
};