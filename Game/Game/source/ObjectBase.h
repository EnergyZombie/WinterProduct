#pragma once
#include"DxLib.h"
#include"appFrame.h"
class ObjectBase {
public:
	ObjectBase(class ObjectServer* _server);
	virtual ~ObjectBase();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	void SetPos(Vector3D pos) {
		_pos = pos; 
	}
	void AddPos(Vector3D vector) { _pos += vector; }
	VECTOR GetDxPos()const { return DxConverter::VecToDx(_pos); }
	Vector3D GetPos()const { return _pos; }
	Vector3D GetOldPos()const { return _old_pos; }

	void SetEulerAngle(Vector3D set) { _euler_angle = set; }

	int GetHandle()const { return _handle; }
	int GetAttachIndex()const { return _attach_index;}




	class ObjectServer* GetObjectServer()const { return _server; }
protected:
	int _handle;
	int _attach_index;

	Vector3D _pos;
	Vector3D _old_pos;

	float _gravity;		//



	Vector3D _euler_angle;

	MATRIX matrix;

	enum class TYPE {
		kPlayer,
	}_type;


private:
	class ObjectServer* _server;

public:


};