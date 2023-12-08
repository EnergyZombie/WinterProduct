#pragma once
#include"ObjectBase.h"

class SignBoard :public ObjectBase {
public:
	SignBoard(class ObjectServer* base):ObjectBase(base){}
	bool Initialize()override;
	bool Process()override;
	bool Renderer()override;
protected:
	int _ui_text;
};