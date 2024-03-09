#pragma once
#include "../../Engine/GameObject/GameObject.h"

class TPSCamera : public GameObject
{
	XMFLOAT2 angle_;
	float sensitivity_;

	GameObject* pTarget_;
public:
	TPSCamera(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	
	void SetTarget(GameObject* target) { pTarget_ = target; }
};

