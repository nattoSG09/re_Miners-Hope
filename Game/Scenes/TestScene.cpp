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
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
