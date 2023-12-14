#pragma once
#include"ObjectBase.h"
#include"appframe.h"

class FallWall :public ObjectBase {
public:
	FallWall(class ObjectServer* server);
	virtual ~FallWall();

	bool Initialize()override;
	//bool Terminate()override;
	bool Process()override;
	bool Render()override;
protected:
	bool _is_fall;
	int _count;
};