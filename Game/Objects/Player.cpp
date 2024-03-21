#include "Player.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/ImGui/imgui.h"
#include "../../Engine/GameObject/Camera.h"
#include "TPSCamera.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "Stages/Stage.h"
#include "Stages/StageObject.h"

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
	// �A�j���[�V�������s�����ǂ���
	bool isAnim = false;

	// �ړ�����
	{
		TPSCamera* cam = (TPSCamera*)FindObject("TPSCamera");
		float angle = cam->GetAngle().y;
		// ������ݒ�
		XMVECTOR dir{}; {
			// �����x�N�g�����擾
			XMVECTOR sightline = XMVector3Normalize(XMVectorSetY(Camera::GetSightline(), 0));

			// �O���Ɉړ�
			if (Input::IsKey(DIK_W)) {
				dir += sightline; isAnim = true;
				transform_.rotate_.y = angle - 25;

			}
			// ����Ɉړ�
			if (Input::IsKey(DIK_S)) {
				dir += -sightline; isAnim = true;
				transform_.rotate_.y = (angle - 25) + 180;
			}
			// �����Ɉړ�
			if (Input::IsKey(DIK_A)) {
				dir += XMVector3Transform(sightline, XMMatrixRotationY(XMConvertToRadians(-90))); isAnim = true;
				transform_.rotate_.y = (angle - 25) - 90;
			}
			// �E���Ɉړ�
			if (Input::IsKey(DIK_D)) {
				dir += XMVector3Transform(sightline, XMMatrixRotationY(XMConvertToRadians(90))); isAnim = true;
				transform_.rotate_.y = (angle - 25) + 90;
			}

			// ���K������
			dir = XMVector3Normalize(dir);
		}

		// ���x��ݒ�
		float speed = 0.1f;
		if (Input::IsKey(DIK_LSHIFT))speed *= 2.f;

		// �ړ�
		Move(dir, speed);
	}

	// �A�j���[�V�������s��
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
	// ������...���ؒ�

	RayCastData rayToColide; {
		rayToColide.start = transform_.position_;	// ���ˈʒu��ݒ�
		rayToColide.start.y += 1.5f;
		XMStoreFloat3(&rayToColide.dir, dir);		// ���˕�����ݒ�
	}
	Model::RayCast(hmColide_, &rayToColide);

	RayCastData rayToPorigon; {
		rayToPorigon.start = transform_.position_;	// ���ˈʒu��ݒ�
		rayToPorigon.start.y+=1.5f;
		XMStoreFloat3(&rayToColide.dir, dir);		// ���˕�����ݒ�
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
