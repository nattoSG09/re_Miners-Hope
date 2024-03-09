#pragma once
#include "../../Engine/GameObject/GameObject.h"

class Player;
class TPSCamera;

class TestScene : public GameObject
{
	Player* pPlayer_;
	TPSCamera* pCamera_;
public:
	TestScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
