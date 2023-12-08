
#include "appframe.h"
#include"Map.h"




class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	XGamePad* GetPad()const;
	class Camera* GetCamera()const { return _camera; }
	Map* GetMap()const { return _map; }
	class ObjectServer* GetObjectServer()const { return _obj_server; }

protected:

	class ObjectServer* _obj_server;
	class Camera* _camera;
	//マップクラスにする
	Map* _map;
}; 
