#include "Coin.h"
#include "../../../Engine/ResourceManager/Model.h"

Coin::Coin(GameObject* parent, std::string name)
	:GameObject(parent, name)
{
}

void Coin::Initialize()
{
	hModel_ = Model::Load("Models/Coin.fbx");
	transform_.scale_ = { 1.1f,1.1f, 1.1f };
}

void Coin::Update()
{
}

void Coin::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Coin::Release()
{
}
