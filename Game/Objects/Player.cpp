#include "Player.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/ImGui/imgui.h"
#include "../../Engine/GameObject/Camera.h"
#include "TPSCamera.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hModel_(-1),hmDebug_(-1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Models/Player/Walking.fbx");
	hmDebug_ = Model::Load("DebugCollision/BoxCollider.fbx");

	assert(0 <= hModel_);
	Model::SetAnimFrame(hModel_, 0, 60, 1);
}

void Player::Update()
{
	XMFLOAT3 bonePose = Model::GetBonePosition(hModel_, "mixamorig:RightHandIndex1");
	ImGui::Text("bonePose = %f,%f,%f", bonePose.x, bonePose.y, bonePose.z);
	Walking();
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	Transform t;
	t.position_ = Model::GetBonePosition(hModel_, "mixamorig:RightHandIndex1");
	Model::SetTransform(hmDebug_, t);
	Model::Draw(hmDebug_);
}

void Player::Release()
{
}

void Player::Move(XMVECTOR dir, float speed)
{
	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + (dir * speed));
}

void Player::Walking()
{
	// アニメーションを行うかどうか
	bool isAnim = false;

	// 移動処理
	{
		TPSCamera* cam = (TPSCamera*)FindObject("TPSCamera");
		float angle = cam->GetAngle().y;
		// 方向を設定
		XMVECTOR dir{}; {
			// 視線ベクトルを取得
			XMVECTOR sightline = XMVector3Normalize(XMVectorSetY(Camera::GetSightline(), 0));

			// 前方に移動
			if (Input::IsKey(DIK_W)) {
				dir += sightline; isAnim = true;
				transform_.rotate_.y = angle - 25;
			}
			// 後方に移動
			if (Input::IsKey(DIK_S)) {
				dir += -sightline; isAnim = true;
				transform_.rotate_.y = (angle - 25) + 180;
			}
			// 左方に移動
			if (Input::IsKey(DIK_A)) {
				dir += XMVector3Transform(sightline, XMMatrixRotationY(XMConvertToRadians(-90))); isAnim = true;
				transform_.rotate_.y = (angle - 25) - 90;
			}
			// 右方に移動
			if (Input::IsKey(DIK_D)) {
				dir += XMVector3Transform(sightline, XMMatrixRotationY(XMConvertToRadians(90))); isAnim = true;
				transform_.rotate_.y = (angle - 25) + 90;
			}
			// 正規化して
			dir = XMVector3Normalize(dir);
		}

		// 速度を設定
		float speed = 0.1f;
		if (Input::IsKey(DIK_LSHIFT))speed *= 2.f;

		// 移動
		Move(dir, speed);
	}

	// アニメーションを行う
	/*static bool prevAnim = false;
	if (isAnim == true) {
		if (prevAnim == false)Model::SetAnimFrame(hModel_, 0, 60, 1);
		prevAnim = true;
	}
	else {
		Model::SetAnimFrame(hModel_, 0, 0, 0);
		prevAnim = false;
	}*/
}
