#include "TestScene.h"
#include "../Objects/Player.h"
#include "../Objects/TPSCamera.h"
#include "../Objects/Stages/Stage.h"
#include "../Objects/SkySphere.h"

#include "../../Engine/ImGui/imgui.h"
#include "../Objects/EditorCamera.h"




TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"),pPlayer_(nullptr),pCamera_(nullptr)
{
}

void TestScene::Initialize()
{
	// ステージを制作
	CreateStage("Data/stageObjects.json", this);

	// プレイヤーを配置
	pPlayer_ = Instantiate<Player>(this); 
	
	// カメラを配置
	pCamera_ = Instantiate<TPSCamera>(this); {
		// プレイヤーに焦点を合わせる
		pCamera_->SetTarget(pPlayer_);
	}
#ifdef _DEBUG


	ec_ = Instantiate<EditorCamera>(this); {
		ec_->ON();
	}
#endif // _DEBUG
	
	Instantiate<SkySphere>(this);

}

void TestScene::Update()
{
#ifdef _DEBUG
	ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_MenuBar); {
		static bool camMode = false;
		ImGui::Checkbox("TPS ON", &camMode);
		if (camMode) {
			pCamera_->SetTarget(pPlayer_);
			ec_->OFF();

		}
		else {
			pCamera_->SetTarget(nullptr);
			ec_->ON();
		}
	}ImGui::End();
	
	ImGui::Text("debug texts...");

#endif // _DEBUG

}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
