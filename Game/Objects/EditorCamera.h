#pragma once
#include "../../Engine/GameObject/GameObject.h"

class EditorCamera : public GameObject
{
	XMFLOAT2 angle_;

	bool isMove_;
public:
	EditorCamera(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void ON() { isMove_ = true; }
	void OFF() { isMove_ = false; }

	XMFLOAT2 GetAngle() { return angle_; }
};

