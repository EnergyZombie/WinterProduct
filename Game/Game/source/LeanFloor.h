#pragma once
#include"ObjectBase.h"

class LeanFloor :public ObjectBase {
public:
	LeanFloor(class ObjectServer* server);
	virtual ~LeanFloor();

	bool Initialize()override;
	//bool Terminate()override;
	bool Process()override;

protected:

	bool _is_lean;

};