#include "TestScene.h"
#include "../Objects/Player.h"
#include "../Objects/TPSCamera.h"
#include "../Objects/Stages/Stage.h"

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
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
