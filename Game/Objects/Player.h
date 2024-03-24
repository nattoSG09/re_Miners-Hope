#pragma once
#include "../../Engine/GameObject/GameObject.h"
class Player : public GameObject
{
	int hModel_;
	int hmColide_;
	bool isDead_;
public:
	Player(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void OnCollision(GameObject* target) override;

	bool IsDead() { return isDead_ == true; }
	void CoinsHitChack();
private:
	void Move(XMVECTOR dir,float speed);
	void Walking();
	void EnemyAttack();

};

