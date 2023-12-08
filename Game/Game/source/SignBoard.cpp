#include"SignBoard.h"
#include"ObjectServer.h"
#include"Player.h"
#include"ModeGame.h"
#include"ModeScript.h"

bool SignBoard::Initialize() { 
	_handle = MV1LoadModel("res/SignBoard/signboard.mv1");
	_ui_text = LoadGraph("res/ball.png");
	ObjectBase::Initialize();
	return true; 
}
bool SignBoard::Process(){ 
	auto pos = GetObjectServer()->GetPlayer()->GetPos();

	if (Vector3D::Length(pos, _pos) < 100) {
		auto pad = GetObjectServer()->GetGame()->GetPad();
		if (pad->GetTrgButton() & INPUT_B) {
			ModeServer::GetInstance()->Add(new ModeScript("‹}‚ª‚Î‰ñ‚ê"), 10, "script");
		}

	}
	
	return true;

}
bool SignBoard::Renderer(){ 
	ObjectBase::Renderer();
	auto pos = GetObjectServer()->GetPlayer()->GetPos();
	if (Vector3D::Length(pos, _pos) < 100) {
		VECTOR dp = ConvWorldPosToScreenPos(DxConverter::VecToDx(pos));
		dp.y -= 200;
		SetFontSize(64);
		std::string str = "push B";
		DrawFormatString(dp.x - str.size() * 64 / 4, dp.y - 64 /2, GetColor(255, 0, 0), "%s",str.c_str());
		SetFontSize(16);
	}
	//auto pos = GetObjectServer()->GetPlayer()->GetPos();

	//if (Vector3D::Length(pos, _pos) < 100) {
	//	
	//	DrawBillboard3D(
	//		DxConverter::VecToDx(Vector3D(pos.x,pos.y+170,pos.z)),
	//		0.5, 0.5, 100, _euler_angle.y, _ui_text, TRUE
	//	);
	//	DrawFormatString(0, 100, GetColor(255, 0, 0), "sign");
	//}

	//DrawSphere3D(
	//	DxConverter::VecToDx(_pos),
	//	100,
	//	16,
	//	GetColor(255, 255, 255),
	//	GetColor(255, 0, 0),
	//	FALSE
	//);

	
	return true;
}