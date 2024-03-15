#include "TestScene.h"
#include "../Objects/Player.h"
#include "../Objects/TPSCamera.h"
#include "../Objects/Stages/Stage.h"

#include "../../Engine/ImGui/imgui.h"


TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"),pPlayer_(nullptr),pCamera_(nullptr)
{
}

void TestScene::Initialize()
{
	// ステージを配置
	Instantiate<Stage>(this);

	// プレイヤーを配置
	pPlayer_ = Instantiate<Player>(this); 
	
	// カメラを配置
	pCamera_ = Instantiate<TPSCamera>(this); {
		// プレイヤーに焦点を合わせる
		pCamera_->SetTarget(nullptr);
	}
}

void TestScene::Update()
{
	ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_MenuBar); {
		static bool camMode = false;
		ImGui::Checkbox("TPS ON", &camMode);
		if (camMode)pCamera_->SetTarget(pPlayer_);
		else pCamera_->SetTarget(nullptr);

	}ImGui::End();
	
	ImGui::Text("debug texts...");
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
