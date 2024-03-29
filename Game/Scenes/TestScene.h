#pragma once
#include "../../Engine/GameObject/GameObject.h"

class TestScene : public GameObject
{
	int pictHandle_;
public:
	TestScene(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};