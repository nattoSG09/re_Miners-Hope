#pragma once
#include "../../../Engine/GameObject/GameObject.h"
#include "../../Others/Circle.h"

class Coin : public GameObject
{
	int hModel_;
	Circle myCircle_;

	friend class Stage;
public:
	Coin(GameObject* parent,std::string name);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void DeadEfect();
	Circle GetCircle() { return myCircle_; }
};

