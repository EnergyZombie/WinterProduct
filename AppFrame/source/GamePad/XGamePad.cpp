#include"XGamePad.h"
//�R���g���[���[�̌������̃{�^��(2�Ԗ�)�����ʂ̕ϐ�������(LeftTrigger��RightTrigger)
//LeftTrigger��RightTrigger����������ł��甽������悤�ɂ��Ă���
constexpr short TRIGGER_DEPTH = 255;


XGamePad::XGamePad(int num){
	_padNum = num;
	_key = 0;
	_trg = 0;
	_rel = 0;
	_input = { {0},0,0,0,0,0,0 };
}

XGamePad::~XGamePad() {

}

void XGamePad::Input() {

	XINPUT_STATE old_input = _input;
	GetJoypadXInputState(_padNum, &_input);

	//������
	//���Ȃ��ƑO�̏�񂪎c�����܂܂ł����������A�E�g?����
	_key = 0;
	_trg = 0;
	_rel = 0;

	//�{�^���̐�
	//unsigned char �͐��l�Ƃ��ė��p�ł��A1Byte�������������g�p���Ȃ�����
	unsigned char button_num = sizeof(_input.Buttons) / sizeof(_input.Buttons[0]);

	for (int a = 0; a < button_num; a++) {
		//XINPUT_STATE��10��11�������͂Ɋ֗^���Ȃ�����v�Z�͂��Ȃ�
		//�������A2^10��2^11�̒l�͌�Ŏg�p����
		if (a == 10 || a == 11) { continue; }

		if (_input.Buttons[a]) {
			_key += 1 << a;
		}
		if ((_input.Buttons[a] ^ old_input.Buttons[a]) & ~old_input.Buttons[a]) {
			_trg += 1 << a;
		}
		if ((_input.Buttons[a] ^ old_input.Buttons[a]) & old_input.Buttons[a]) {
			_rel += 1 << a;
		}
	}

	//LeftTrigger��RightTrigger�̃L�[�A�g���K�[�A�����[�X���ǂꂮ�炢�����ꂽ�����m�F���āA�擾����
	//���Ȃ��Ă�������������Ȃ����ǁA�ꉞ����Ă���
	//��L�Ŏg�p���Ȃ�����2^10��2^11�̒l�������Ŏg�p����
	auto Trigger = [this](unsigned char trigger,unsigned char old_trigger, unsigned char exp) {
		if (trigger >= TRIGGER_DEPTH) {
			_key += 1 << exp;
		}
		if (trigger == TRIGGER_DEPTH) {
			if ((trigger ^ old_trigger) & ~old_trigger)
				_trg += 1 << exp;
		}
		if (old_trigger == TRIGGER_DEPTH) {
			if ((trigger ^ old_trigger) & old_trigger)
				_rel += 1 << exp;
		}
	};

	Trigger(_input.LeftTrigger,old_input.LeftTrigger,10);
	Trigger(_input.RightTrigger,old_input.RightTrigger,11);

}