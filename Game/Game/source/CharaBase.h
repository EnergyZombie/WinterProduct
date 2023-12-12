#pragma once
#include"ObjectBase.h"

class CharaBase :public ObjectBase{
public :
	CharaBase(class ObjectServer* server);

	//
	bool Render()override;

	//
	bool IsHitMap();
	bool IsPushedObject(class ObjectBase* obj);
	bool IsPushedChara(class CharaBase* chara);
	double GetRadian()const { return _radian; }
	float GetCollSubY()const { return _colSubY; }
	void AddMove(Vector3D add) { _move += add; }
	ObjectBase* GetOnObject()const { return _onObj; }
	Segment3D GetCapsuleSegment() {
		Vector3D under_pos(_pos);
		under_pos.y += _radian;
		Vector3D over_pos(under_pos);
		over_pos.y += _colSubY;
		return Segment3D(under_pos, over_pos);
	}

	virtual void ProcessGravity();
protected:
	double _radian;
	bool	_is_stand;		//オブジェクトの上に立っているか
	Vector3D _move;
	float _play_time;
	float _total_time;

	ObjectBase* _onObj;
public:
	float _colSubY;	// コリジョン判定時のY補正(腰位置）
	static bool collision;
};