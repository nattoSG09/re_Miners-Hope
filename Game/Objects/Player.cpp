#include "Player.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/ImGui/imgui.h"
#include "../../Engine/GameObject/Camera.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hModel_(-1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Models/Player/Walking02.fbx");
	assert(0 <= hModel_);
}

void Player::Update()
{
	ImGui::Text("position = %f,%f,%f",transform_.position_.x,transform_.position_.y,transform_.position_.z);

	// 移動処理
	{
		// 方向を設定
		XMVECTOR dir{}; {
			// 視線ベクトルを取得
			XMVECTOR sightline = XMVector3Normalize(XMVectorSetY(Camera::GetSightline(), 0));

			// 前方に移動
			if (Input::IsKey(DIK_W)) dir += sightline;
			
			// 左方に移動
			if (Input::IsKey(DIK_A)) dir += XMVector3Transform(sightline, XMMatrixRotationY(XMConvertToRadians(-90)));

			// 後方に移動
			if (Input::IsKey(DIK_S)) dir += -sightline;

			// 右方に移動
			if (Input::IsKey(DIK_D)) dir += XMVector3Transform(sightline, XMMatrixRotationY(XMConvertToRadians(90)));
			
			// 正規化して
			dir = XMVector3Normalize(dir);
		}

		// 速度を設定
		float speed = 0.1f;
		if (Input::IsKey(DIK_LSHIFT))speed *= 2.f;

		// 移動
		Move(dir, speed);
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::Move(XMVECTOR dir, float speed)
{
	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + (dir * speed));
}
