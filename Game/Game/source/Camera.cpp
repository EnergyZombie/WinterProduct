#include"Camera.h"
#include"ModeGame.h"


bool Camera::Process() {

	auto Rstick = _game->GetPad()->GetRightStick();
	if (Rstick.x > 30000) {
		RotateY -= DegToRad(1);
		if (RotateY < 0) {
			RotateY = DegToRad(360);
		}
	}
	if (Rstick.x < -30000) {
		RotateY += DegToRad(1);
		if (RotateY > DegToRad(360)) {
			RotateY = 0;
		}
	}
	if (Rstick.y > 30000) {
		RotateX -= DegToRad(1);
		if (RotateX < -DegToRad(90)) {
			RotateX = -DegToRad(90);
		}
	}
	if (Rstick.y < -30000) {
		RotateX += DegToRad(1);
		if (RotateX > DegToRad(90)) {
			RotateX = DegToRad(90);
		}
	}
	return true;
}