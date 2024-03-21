#pragma once
#include "../../../Engine/GameObject/GameObject.h"

class CrossHair : GameObject
{
	int hModel_;
public:
	CrossHair(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
