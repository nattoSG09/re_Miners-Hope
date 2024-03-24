#include "Player.h"

#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/ImGui/imgui.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Engine/ResourceManager/VFX.h"
#include "../../Engine/Collider/BoxCollider.h"

#include "Stages/Stage.h"
#include "Stages/StageObject.h"
#include "TPSCamera.h"
#include "Enemy.h"
#include "../Objects/Stages/Coin.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/ResourceManager/Audio.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hModel_(-1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Models/Player/Walking.fbx");
	hmColide_ = Model::Load("DebugCollision/BoxCollider.fbx");
	assert(0 <= hModel_);
	AddCollider(new BoxCollider(XMFLOAT3(0, 2, 0), XMFLOAT3(1, 4, 1)));

	ha_getCoin_ = Audio::Load("Audio/phaseJump3.wav");
	ha_footstep_ = Audio::Load("Audio/footstep09.wav");
	ha_gameOver_ = Audio::Load("Audio/gameover4.wav");
	ha_gameClear_ = Audio::Load("Audio/confirmation_002.wav");
	Audio::SetPlaybackRate(ha_footstep_, 0.3f);
	Audio::SetVolume(ha_footstep_, 0.3f);
}

void Player::Update()
{

	static bool gameoverPlay = false;
	static int time = 0;
	if (isDead_ || myCoinNum_ == 10) {
		if (isDead_ && gameoverPlay == false) {
			Audio::Play(ha_gameOver_);
			gameoverPlay = true;
		}

		if (gameoverPlay == false) {
			Audio::Play(ha_gameClear_);
			gameoverPlay = true;
		}

		if (time >= 2 * 60) {
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");
			sm->ChangeScene(SCENE_ID_TITLE, TID_WHITEOUT);
		}
		time++;
	}
	else {
		Walking();
		CoinsHitChack();
		time = 0;
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

void Player::CoinsHitChack()
{
	Stage* s = (Stage*)FindObject("Stage");
	for (auto c : s->GetStageCoins()) {
		if (c->GetCircle().ContainsPoint(transform_.position_.x, transform_.position_.z) == true) {
			Audio::Play(ha_getCoin_);
			c->DeadEfect();
			s->DeleteCoin(c);
			myCoinNum_++;
		}
	}
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

		isDash_ = false;
		// ���x��ݒ�
		float speed = 0.1f;
		if (Input::IsKey(DIK_LSHIFT)) {
			speed *= 2.f;
			isDash_ = true;
		}

		// �ړ�
		Move(dir, speed);

		if(Input::IsKey(DIK_W)|| Input::IsKey(DIK_A)|| Input::IsKey(DIK_S)|| Input::IsKey(DIK_D))
			Audio::Play(ha_footstep_);


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

void Player::EnemyAttack()
{
	// ������...���ؒ�

	Enemy* e = (Enemy*)FindObject("Enemy");
	if (e == nullptr)return;
	// �����x�N�g�����擾
	XMVECTOR sightline = XMVector3Normalize(Camera::GetSightline());

	// ���C�L���X�g�𔭎�
	RayCastData sightRay; {
		XMStoreFloat3(&sightRay.dir, sightline);
		sightRay.start = Camera::GetPosition();
		Model::RayCast(e->GetModelHandle(), &sightRay);
	}

	if (sightRay.hit) {
		// Effect���o��
		{
			EmitterData data;

			//��
			data.textureFileName = "Images/cloudA.png";

			data.position = sightRay.pos;
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
			data.size = XMFLOAT2(0.1, 0.1);
			data.sizeRnd = XMFLOAT2(0.4, 0.4);
			data.scale = XMFLOAT2(0.99, 0.99);
			data.color = XMFLOAT4(0.4, 0.2, 0.0, 1);
			data.deltaColor = XMFLOAT4(0, 0, 0, 0);
			data.gravity = 0.003f;
			VFX::Start(data);
		}

		// �U������
		//e->SetHP(pEnemy_->GetHP() - 20);
	}
}

void Player::OnCollision(GameObject* target)
{
	if (target->GetObjectName() == "Enemy") {
		isDead_ = true;
		Model::SetAnimFrame(hModel_, 0, 0, 0);
		// Effect���o��
		{
			EmitterData data;

			//��
			data.textureFileName = "Images/cloudA.png";

			data.position = transform_.position_;
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
			data.size = XMFLOAT2(0.1, 0.1);
			data.sizeRnd = XMFLOAT2(0.4, 0.4);
			data.scale = XMFLOAT2(0.99, 0.99);
			data.color = XMFLOAT4(0.4, 0.2, 0.0, 1);
			data.deltaColor = XMFLOAT4(0, 0, 0, 0);
			data.gravity = 0.003f;
			VFX::Start(data);
		}
	}
}
