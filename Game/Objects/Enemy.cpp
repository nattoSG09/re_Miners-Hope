#include "Enemy.h"
#include "../../Engine/ResourceManager/Model.h"
#include "Player.h"
#include "../../Engine/Collider/BoxCollider.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy")
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Models/Enemy/Walking.fbx");
	Model::SetAnimFrame(hModel_, 0, 82, 1);

	AddCollider(new BoxCollider(XMFLOAT3(0, 3, 0), XMFLOAT3(2, 3, 2)));
}

void Enemy::Update()
{
	// �ʒu���擾
	XMFLOAT3 playerPosition = ((Player*)FindObject("Player"))->GetPosition();

	// �i�s������ݒ�
	XMVECTOR dir = {}; {
		dir = XMLoadFloat3(&playerPosition) - XMLoadFloat3(&transform_.position_);
		dir = XMVector3Normalize(dir);
	}

	// ���x��ݒ�
	float speed = 0.1f;

	// �ړ�
	Move(dir, speed);

}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::Move(XMVECTOR dir, float speed)
{
	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + (dir * speed));
}