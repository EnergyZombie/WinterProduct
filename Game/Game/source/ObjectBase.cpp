#include"ObjectBase.h"
#include"ObjectServer.h"
#include"appframe.h"
#include"ModeGame.h"
#include<string>
ObjectBase::ObjectBase(ObjectServer* server) {
	//�������Ǘ�����T�[�o�[���L�^����
	_server = server;
}

ObjectBase::~ObjectBase() {
	Terminate();
}

bool ObjectBase::Initialize() {

	matrix = MGetIdent();
	matrix = MMult(matrix, MGetRotX(_euler_angle.x));
	matrix = MMult(matrix, MGetRotY(_euler_angle.y));
	matrix = MMult(matrix, MGetRotZ(_euler_angle.z));
	matrix = MMult(matrix, MGetTranslate(DxConverter::VecToDx(_pos)));
	MV1SetMatrix(_handle, matrix);

	return true;
}

bool ObjectBase::Terminate() {
	MV1DeleteModel(_handle);
	return false;
}

bool ObjectBase::Process() {
	//// �Đ����Ԃ�i�߂�
	//_play_time += 0.5f;
	//// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	//if (_play_time >= _total_time) {
	//	_play_time = 0.0f;
	//}
		matrix = MGetIdent();
	matrix = MMult(matrix, MGetRotX(_euler_angle.x));
	matrix = MMult(matrix, MGetRotY(_euler_angle.y));
	matrix = MMult(matrix, MGetRotZ(_euler_angle.z));
	matrix = MMult(matrix, MGetTranslate(DxConverter::VecToDx(_pos)));
	MV1SetMatrix(_handle, matrix);
	return true;
}

bool ObjectBase::Render() {

	matrix = MGetIdent();
	matrix = MMult(matrix, MGetRotX(_euler_angle.x));
	matrix = MMult(matrix, MGetRotZ(_euler_angle.z));
	matrix = MMult(matrix, MGetRotY(_euler_angle.y));

	matrix = MMult(matrix, MGetTranslate(DxConverter::VecToDx(_pos)));
	MV1SetMatrix(_handle, matrix);
	// ���f����`�悷��
	MV1DrawModel(_handle);

	return true;
}



