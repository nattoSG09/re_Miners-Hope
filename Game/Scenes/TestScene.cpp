#include "TestScene.h"
#include "../Objects/Player.h"
#include "../Objects/TPSCamera.h"
#include "../Objects/Stages/Stage.h"
#include "../Objects/SkySphere.h"
#include "../Objects/UI/UIPanel.h"

#include "../../Engine/ImGui/imgui.h"
#include "../Objects/EditorCamera.h"
#include "../Objects/Enemy.h"
#include "../Objects/Stages/Coin.h"
#include "../../Engine/ResourceManager/Audio.h"


TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"),pPlayer_(nullptr),pCamera_(nullptr)
{
}

void TestScene::Initialize()
{

	// �X�e�[�W�𐧍�
	CreateStage("Data/stageObjects2.json", this);

	// �v���C���[��z�u
	pPlayer_ = Instantiate<Player>(this); 
	
	// �J������z�u
	pCamera_ = Instantiate<TPSCamera>(this); {
		// �v���C���[�ɏœ_�����킹��
		pCamera_->SetTarget(pPlayer_);
	}

	// �X�J�C�X�t�B�A��z�u
	Instantiate<SkySphere>(this);

#ifdef _DEBUG

	ec_ = Instantiate<EditorCamera>(this); {
		ec_->ON();
	}

#else
	ha_music = Audio::Load("Audio/Retro-Comedy.wav",true);
	Audio::Play(ha_music);

	Enemy* e = Instantiate<Enemy>(this); {
		e->SetPosition(30, 0, 30);
	}

	// UI��z�u
	Instantiate<UIPanel>(this);

#endif // _DEBUG

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
