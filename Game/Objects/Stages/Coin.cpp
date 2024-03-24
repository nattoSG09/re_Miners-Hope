#include "Coin.h"
#include "../../../Engine/ResourceManager/Model.h"
#include "../../../Engine/Collider/BoxCollider.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../Player.h"
#include "../../../Engine/ResourceManager/VFX.h"

Coin::Coin(GameObject* parent, std::string name)
	:GameObject(parent, name)
{
}

void Coin::Initialize()
{
	hModel_ = Model::Load("Models/Coin.fbx");
	transform_.scale_ = { 2.f,2.f, 2.f };
}

void Coin::Update()
{
	myCircle_.center_ = { transform_.position_.x ,transform_.position_.z};
	myCircle_.radius_ = 1.2f;

	transform_.rotate_.y += 0.5f;

	static float direction = 0; {
		if (transform_.position_.y <= 0.0f) {
			direction = 0.01f; // �ړ����x�𐳂ɕύX
		}
		// y��0.5f�ȏ�̏ꍇ�A�����𕉂ɕύX
		else if (transform_.position_.y >= 0.5f) {
			direction = -0.01f; // �ړ����x�𕉂ɕύX
		}

		// y�̒l���X�V
		transform_.position_.y += direction;
	}
}

void Coin::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Coin::Release()
{
}

void Coin::DeadEfect()
{

	EmitterData data;
	data.position = transform_.position_;
	//�΂̕�
	data.delay = 0;
	data.number = 80;
	data.lifeTime = 100;
	data.positionRnd = XMFLOAT3(0.5, 0, 0.5);
	data.direction = XMFLOAT3(0, 1, 0);
	data.directionRnd = XMFLOAT3(90, 90, 90);
	data.speed = 0.25f;
	data.speedRnd = 1;
	data.accel = 0.93;
	data.size = XMFLOAT2(0.5, 0.5);
	data.sizeRnd = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(0.99, 0.99);
	data.color = XMFLOAT4(0.2, 0.2, 0.5, 1);
	data.deltaColor = XMFLOAT4(0, 0, 0, 0);
	data.gravity = 0.003f;
	VFX::Start(data);
}
