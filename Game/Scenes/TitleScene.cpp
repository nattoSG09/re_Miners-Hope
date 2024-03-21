#include "TitleScene.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/SceneManager.h"

#include "../Objects/Stages/Stage.h"
#include "../Objects/SkySphere.h"
#include "../Objects/UI/TitleImage.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene")
{
}

void TitleScene::Initialize()
{
	CreateStage("Data/stageObjects.json", this);

	// スカイスフィアを配置
	Instantiate<SkySphere>(this);

	// タイトル画像を配置
	Instantiate<TitleImage>(this);

}

void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSm = (SceneManager*)FindObject("SceneManager");
		pSm->ChangeScene(SCENE_ID_TEST, TID_BLACKOUT, 2.f);

	}

	XMVECTOR sightline{ 0.f,0.f,-1.f,0.f };

	static float angle = 0;
	angle += 0.1f;
	XMMATRIX matRotate = XMMatrixRotationY(XMConvertToRadians(angle));
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
