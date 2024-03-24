#pragma once
#include "../../../Engine/GameObject/GameObject.h"
#include "../../../Engine/ResourceManager/Text.h"

class UIPanel : public GameObject
{
	int hp_dispQuestText;
	int hp_youDead;

	Text* pText_;
public:
	UIPanel(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

