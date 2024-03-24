#pragma once
#include "../../Engine/GameObject/GameObject.h"

class TitleScene : public GameObject
{
	int ha_Start;
	int ha_music;
public:
	TitleScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
