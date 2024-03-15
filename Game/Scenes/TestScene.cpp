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
	// �X�e�[�W��z�u
	Instantiate<Stage>(this);

	// �v���C���[��z�u
	pPlayer_ = Instantiate<Player>(this); 
	
	// �J������z�u
	pCamera_ = Instantiate<TPSCamera>(this); {
		// �v���C���[�ɏœ_�����킹��
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
