#pragma once
#include<vector>

class ObjectServer {

public:
	ObjectServer(class ModeGame* game);
	~ObjectServer();

	void AddObj(class ObjectBase* obj);
	void DeleteObj(class ObjectBase* obj);

	void SetPlayer(class Player* obj);
	class Player* GetPlayer()const { return _player; }

	bool Initialize();
	bool Terminate();
	bool Process();
	bool Renderer();

	class ModeGame* GetGame()const { return _game; }

	std::vector<class ObjectBase*> GetObjects()const { return _obj; }

	bool ClearObject();

protected:
	std::vector<class ObjectBase*> _obj;
	std::vector<class ObjectBase*> _add_obj;
	std::vector<class ObjectBase*> _delete_obj;

	class Player* _player;
private:
	class ModeGame* _game;
};