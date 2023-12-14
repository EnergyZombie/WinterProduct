#pragma once
#include"CharaBase.h"

struct capsul {
	VECTOR v1;
	VECTOR v2;
	float rad;
};

class Player :public CharaBase {
public:
	Player(class ObjectServer* server);
	~Player();

	bool Initialize()override;
	bool Process()override;
	bool Render()override;

protected:

	VECTOR _onPos;
		enum class ACTION_STATE {
		kNone,
		kIdle,
		kWalk
	}_action_state;


};
