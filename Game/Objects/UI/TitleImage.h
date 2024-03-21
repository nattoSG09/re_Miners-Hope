#pragma once
#include "../../../Engine/GameObject/GameObject.h"

class TitleImage : public GameObject
{
	int hPict_;
	int hpSpace_;
public:
	TitleImage(GameObject* parent);
	void Initialize();
	void Update();
	void Draw();
	void Release();
};

