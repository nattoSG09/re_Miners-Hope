#pragma once
#include "../../Engine/GameObject/GameObject.h"
class Player : public GameObject
{
	int hModel_;

	int hmDebug_;
public:
	Player(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	void Move(XMVECTOR dir,float speed);
	void Walking();
};

