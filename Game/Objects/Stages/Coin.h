#pragma once
#include "../../../Engine/GameObject/GameObject.h"

class Coin : public GameObject
{
	int hModel_;
	friend class Stage;
public:
	Coin(GameObject* parent,std::string name);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};

