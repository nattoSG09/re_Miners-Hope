#pragma once
#include "../../../Engine/GameObject/GameObject.h"

class UIPanel : public GameObject
{
public:
	UIPanel(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

