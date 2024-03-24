#pragma once
#include "../../Engine/GameObject/GameObject.h"

class Player;
class TPSCamera;
class EditorCamera;

class TestScene : public GameObject
{
	int ha_music;
	Player* pPlayer_;
	TPSCamera* pCamera_;
	EditorCamera* ec_;
public:
	TestScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
