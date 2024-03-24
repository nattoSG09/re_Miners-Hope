#pragma once
#include "../../Engine/GameObject/GameObject.h"
class Player : public GameObject
{
	int hModel_;
	int hmColide_;
	bool isDead_;
	int myCoinNum_;
	bool isDash_;
	int ha_getCoin_;
	int ha_footstep_;
	int ha_gameOver_;
	int ha_gameClear_;
public:
	Player(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void OnCollision(GameObject* target) override;

	bool IsDead() { return isDead_ == true; }
	bool IsDash() { return isDash_ == true; }
	void CoinsHitChack();
	int GetCoinNum() { return myCoinNum_; }
private:
	void Move(XMVECTOR dir,float speed);
	void Walking();
	void EnemyAttack();

};

