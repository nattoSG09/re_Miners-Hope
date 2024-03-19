#include "TestScene.h"
#include "../Objects/Player.h"
#include "../Objects/TPSCamera.h"
#include "../Objects/Stages/Stage.h"

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
	EditorCamera* ec = Instantiate<EditorCamera>(this); {
		ec->ON();
	}
	
}

void TestScene::Update()
{
#ifdef _DEBUG
	ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_MenuBar); {
		static bool camMode = false;
		ImGui::Checkbox("TPS ON", &camMode);
		if (camMode)pCamera_->SetTarget(pPlayer_);
		else pCamera_->SetTarget(nullptr);

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
