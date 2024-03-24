#include "TitleScene.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/SceneManager.h"

#include "../Objects/Stages/Stage.h"
#include "../Objects/SkySphere.h"
#include "../Objects/UI/TitleImage.h"

#include "../../Engine/ResourceManager/Audio.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene")
{
}

void TitleScene::Initialize()
{
	CreateStage("Data/stageObjects2.json", this);

	// スカイスフィアを配置
	Instantiate<SkySphere>(this);

	// タイトル画像を配置
	Instantiate<TitleImage>(this);

	ha_Start = Audio::Load("Audio/confirmation_002.wav");
	ha_music = Audio::Load("Audio/Retro-Comedy.wav",true);
	Audio::Play(ha_music);
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSm = (SceneManager*)FindObject("SceneManager");
		Audio::Play(ha_Start);
		pSm->ChangeScene(SCENE_ID_TEST, TID_BLACKOUT, 2.f);
	}

	XMVECTOR sightline{ 0.f,0.f,-1.f,0.f };

	static float angle = 0;
	angle += 0.1f;
	XMMATRIX matRotate = XMMatrixRotationY(XMConvertToRadians(angle)) * XMMatrixRotationX(XMConvertToRadians(30));
	sightline = XMVector3Transform(sightline, matRotate);

	sightline *= 100.f;

	XMFLOAT3 camTgt = Camera::GetTarget();
	XMVECTOR origin_To_camPos = XMLoadFloat3(&camTgt) + sightline;

	XMFLOAT3 camPos{};
	XMStoreFloat3(&camPos, origin_To_camPos);
	camPos.y += 2.f;

	Camera::SetPosition(camPos);

}

void TitleScene::Draw()
{
}

void TitleScene::Release()
{
}
