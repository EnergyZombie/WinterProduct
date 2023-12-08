#pragma once
#include"../Math/mymath.h"
#include"DxLib.h"
//struct XINPUT_STATE
//{
//	unsigned char	Buttons[16];	// �{�^���P�U��( �Y���ɂ� XINPUT_BUTTON_DPAD_UP �����g�p����A
//	//			0:������Ă��Ȃ�  1:������Ă��� )
//	unsigned char	LeftTrigger;	// ���g���K�[( 0�`255 )
//	unsigned char	RightTrigger;	// �E�g���K�[( 0�`255 )
//	short		ThumbLX;	// ���X�e�B�b�N�̉����l( -32768 �` 32767 )
//	short		ThumbLY;	// ���X�e�B�b�N�̏c���l( -32768 �` 32767 )
//	short		ThumbRX;	// �E�X�e�B�b�N�̉����l( -32768 �` 32767 )
//	short		ThumbRY;	// �E�X�e�B�b�N�̏c���l( -32768 �` 32767 )
//};

// �Ȃ�10��11���������Ă�
//#define XINPUT_BUTTON_DPAD_UP		(0)	// �f�W�^�������{�^����
//#define XINPUT_BUTTON_DPAD_DOWN		(1)	// �f�W�^�������{�^����
//#define XINPUT_BUTTON_DPAD_LEFT		(2)	// �f�W�^�������{�^����
//#define XINPUT_BUTTON_DPAD_RIGHT	(3)	// �f�W�^�������{�^���E
//#define XINPUT_BUTTON_START		(4)	// START�{�^��
//#define XINPUT_BUTTON_BACK		(5)	// BACK�{�^��
//#define XINPUT_BUTTON_LEFT_THUMB	(6)	// ���X�e�B�b�N��������
//#define XINPUT_BUTTON_RIGHT_THUMB	(7)	// �E�X�e�B�b�N��������
//#define XINPUT_BUTTON_LEFT_SHOULDER	(8)	// LB�{�^��
//#define XINPUT_BUTTON_RIGHT_SHOULDER	(9)	// RB�{�^��
//#define XINPUT_BUTTON_A			(12)	// A�{�^��
//#define XINPUT_BUTTON_B			(13)	// B�{�^��
//#define XINPUT_BUTTON_X			(14)	// X�{�^��
//#define XINPUT_BUTTON_Y			(15)	// Y�{�^��

namespace {
	constexpr auto INPUT_DPAD_UP =				0b0000000000000001;		 //1			
	constexpr auto INPUT_DPAD_DOWN =			0b0000000000000010;		 //2		
	constexpr auto INPUT__DPAD_LEFT =			0b0000000000000100;		 //4		
	constexpr auto INPUT__DPAD_RIGHT =			0b0000000000001000;		 //8
	constexpr auto INPUT_START =				0b0000000000010000;		 //16
	constexpr auto INPUT_BACK =					0b0000000000100000;		 //32
	constexpr auto INPUT_LEFT_THUMB =			0b0000000001000000;		 //64
	constexpr auto INPUT_RIGHT_THUMB =			0b0000000010000000;		 //128
	constexpr auto INPUT_LEFT_SHOULDER =		0b0000000100000000;		 //256
	constexpr auto INPUT_RIGHT_SHOULDER =		0b0000001000000000;		 //512
	constexpr auto INPUT_LEFT2_SHOULDER =		0b0000010000000000;		 //1024
	constexpr auto INPUT_RIGHT2_SHOULDER =		0b0000100000000000;		 //2048
	constexpr auto INPUT_A =					0b0001000000000000;		 //4096
	constexpr auto INPUT_B =					0b0010000000000000;		 //8192
	constexpr auto INPUT_X =					0b0100000000000000;		 //16384
	constexpr auto INPUT_Y =					0b1000000000000000;		 //32768

	constexpr int STICK_DEPTH = 20000;

	struct STICK {
		short x, y;
	};
}

class XGamePad {
public:
	XGamePad(int num);
	~XGamePad();
	virtual void Input();

	unsigned int GetKeyButton()const { return _key; }
	unsigned int GetTrgButton()const { return _trg; }
	unsigned int GetRelButton()const { return _rel; }

	unsigned char GetLeftTrigger()const { return _input.LeftTrigger; }
	unsigned char GetRightTrigger()const { return _input.RightTrigger; }

	STICK GetLeftStick()const {
		STICK stick = { _input.ThumbLX ,_input.ThumbLY };
		return stick;
	}

	STICK GetRightStick()const {
		STICK stick = { _input.ThumbRX ,_input.ThumbRY };
		return stick;
	}

	bool IsInputLeftStick()const { return _input.ThumbLX > STICK_DEPTH || _input.ThumbLX < -STICK_DEPTH || _input.ThumbLY > STICK_DEPTH || _input.ThumbLY < -STICK_DEPTH; }
	bool IsInputRightStick()const { return _input.ThumbRX > STICK_DEPTH || _input.ThumbRX < -STICK_DEPTH || _input.ThumbRY > STICK_DEPTH || _input.ThumbRY < -STICK_DEPTH;	}

	float GetLeftStickRad()const { return (float) (atan2(_input.ThumbLY, _input.ThumbLX)); }
	float GetRightStickRad()const { return (float) ( atan2(_input.ThumbRY, _input.ThumbRX)); }

protected:
	//�X�V����Q�[���p�b�h�̎��
	int _padNum;

	//�X�V����Q�[���p�b�h�̍\����
	//�E�̃A�i���O�X�e�B�b�N���g����������
	XINPUT_STATE _input;

	//���͂̌v�Z��bit���Z�ōs��
	//XINPUT_STATE���g���K�[�ƃ����[�X���p�ӂ�������������̃o�C�g�������点�邽��
	//�~�����̂̓{�^�������ŃX�e�B�b�N�n�͂���Ȃ��̂�
	//		1byte		�~		(16 + 2)		+		2byte	�~				4				=	26byte
	//unsigned char				�{�^���̐�				short		���E�X�e�B�b�N�̏c������		XINPUT_STATE�̎g�p������

	//XINPUT_STATE���g���K�[�ƃ����[�X���p�ӂ����78byte�ɂȂ�
	//�����bit���Z�Ŏg�p����int�^�ϐ�3���ƁA
	//unsigned int				��				XINPUT_STATE�͈�͕K�v������				���v�g�p������ 
	//		4byte		�~		3		+				26byte					=		38byte
	//40byte�̐ߖ�ɂȂ�
	//�萔���܂߂���A�g�p�������͑����Ă͂��邪�Q�[���p�b�h�̏�񂪑����������l������Ƒ������Ȃ��Ȃ��Ă���
	//�ȂɁH�ߖ�ł��郁�����������Ȃ����A��������������?���邹���I�����A��������Ibit���Z������������������!
	unsigned int _key;
	unsigned int _trg;
	unsigned int _rel;

};



