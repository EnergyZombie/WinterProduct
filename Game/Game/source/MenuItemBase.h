
#include "appframe.h"

#include <string>

// ���j���[���ڗp�x�[�X�N���X
class MenuItemBase
{
public:
	MenuItemBase(void* param, std::string text) {
		_param = param;
		_text = text;
	}
	virtual ~MenuItemBase() {
	}

	// ���ڂ����肵���炱�̊֐����Ă΂��
	// return int : 0 = ���j���[�p��, 1 = ���j���[�I��
	virtual int Selected() {
		return 0;
	}

public:
	void* _param;
	std::string		_text;
};
