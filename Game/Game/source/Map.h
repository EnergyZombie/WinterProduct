#pragma once
#include"DxLib.h"
class Map{
public:

	virtual bool Initialize();
	virtual bool Renderer();
	int GetHandleMap()const { return _handleMap; }
	int GetCollisionIndex()const { return _frameMapCollision; }
	virtual bool Process(class ModeGame* game);
	bool LoadMap(class ModeGame* game);
	//MV1_COLL_RESULT_POLY CheckHitMap(class ObjectBase* obj);

protected:
	int _handleMap;
	int _handleSkySphere;
	int _frameMapCollision;

	int _graph;


	bool _is_over;

public:
	// デバッグ用
	static bool	_bViewCollision;
};