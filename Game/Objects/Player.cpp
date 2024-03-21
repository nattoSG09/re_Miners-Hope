#include "Player.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/ImGui/imgui.h"
#include "../../Engine/GameObject/Camera.h"
#include "TPSCamera.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "Stages/Stage.h"
#include "Stages/StageObject.h"
#include "Enemy.h"
#include "../../Engine/ResourceManager/VFX.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hModel_(-1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Models/Player/Walking.fbx");
	hmColide_ = Model::Load("DebugCollision/BoxCollider.fbx");
	assert(0 <= hModel_);
}

void Player::Update()
{
	Walking();

	if(Input::IsMouseButton(0))EnemyAttack();
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	Transform t = transform_;
	t.scale_ = { 1.5f,3.f,1.5f };
	Direct3D::SetShader(Direct3D::SHADER_UNLIT);
	Model::SetTransform(hmColide_, t);
	Model::Draw(hmColide_);
	Direct3D::SetShader(Direct3D::SHADER_3D);

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
	static bool prevAnim = false;
	if (isAnim == true) {
		if (prevAnim == false)Model::SetAnimFrame(hModel_, 0, 60, 1);
		prevAnim = true;
	}
	else {
		Model::SetAnimFrame(hModel_, 0, 0, 0);
		prevAnim = false;
	}
}

bool Player::IsCollide(XMVECTOR dir)
{
	// 未完成...検証中

	RayCastData rayToColide; {
		rayToColide.start = transform_.position_;	// 発射位置を設定
		rayToColide.start.y += 1.5f;
		XMStoreFloat3(&rayToColide.dir, dir);		// 発射方向を設定
	}
	Model::RayCast(hmColide_, &rayToColide);

	RayCastData rayToPorigon; {
		rayToPorigon.start = transform_.position_;	// 発射位置を設定
		rayToPorigon.start.y+=1.5f;
		XMStoreFloat3(&rayToColide.dir, dir);		// 発射方向を設定
	}

	vector<StageObject*> objects = ((Stage*)FindObject("Stage"))->GetStageObjects();
	for (auto& obj : objects) {
		Model::RayCast(obj->GetModelHandle(), &rayToPorigon);

		if (rayToPorigon.hit == true && rayToColide.hit == true) {
			
			if (rayToPorigon.dist < rayToColide.dist) {
				ImGui::Text(obj->GetObjectName().c_str());
				ImGui::Text("C dist = %f", rayToColide.dist);
				ImGui::Text("P dist = %f", rayToPorigon.dist);
				ImGui::Text("hit now!!");
				return true;
			}
		}
	}
	
	return false;
}

void Player::EnemyAttack()
{
	Enemy* e = (Enemy*)FindObject("Enemy");
	if (e == nullptr)return;
	// 視線ベクトルを取得
	XMVECTOR sightline = XMVector3Normalize(Camera::GetSightline());

	// レイキャストを発射
	RayCastData sightRay; {
		XMStoreFloat3(&sightRay.dir, sightline);
		sightRay.start = Camera::GetPosition();
		Model::RayCast(e->GetModelHandle(), &sightRay);
	}

	if (sightRay.hit) {
		// Effectを出す
		{
			EmitterData data;

			//炎
			data.textureFileName = "Images/cloudA.png";

			data.position = sightRay.pos;
			ImGui::Text("pos = %f,%f,%f", data.position.x, data.position.y, data.position.z);
			data.delay = 0;
			data.number = 80;
			data.lifeTime = 30;
			data.direction = XMFLOAT3(0, 1, 0);
			data.directionRnd = XMFLOAT3(90, 90, 90);
			data.speed = 0.1f;
			data.speedRnd = 0.8;
			data.size = XMFLOAT2(1.2, 1.2);
			data.sizeRnd = XMFLOAT2(0.4, 0.4);
			data.scale = XMFLOAT2(1.05, 1.05);
			data.color = XMFLOAT4(0.5, 0.5, 0.1, 1);
			data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
			VFX::Start(data);

			//火の粉
			data.delay = 0;
			data.number = 80;
			data.lifeTime = 100;
			data.positionRnd = XMFLOAT3(0.5, 0, 0.5);
			data.direction = XMFLOAT3(0, 1, 0);
			data.directionRnd = XMFLOAT3(90, 90, 90);
			data.speed = 0.25f;
			data.speedRnd = 1;
			data.accel = 0.93;
			data.size = XMFLOAT2(0.1, 0.1);
			data.sizeRnd = XMFLOAT2(0.4, 0.4);
			data.scale = XMFLOAT2(0.99, 0.99);
			data.color = XMFLOAT4(0.4, 0.2, 0.0, 1);
			data.deltaColor = XMFLOAT4(0, 0, 0, 0);
			data.gravity = 0.003f;
			VFX::Start(data);
		}

		// 攻撃する
		//e->SetHP(pEnemy_->GetHP() - 20);
	}
}
