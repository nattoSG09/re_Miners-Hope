#include "TestScene.h"
#include "../Objects/Player.h"
#include "../Objects/TPSCamera.h"

TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{
	pPlayer_ = Instantiate<Player>(this); 
	pCamera_ = Instantiate<TPSCamera>(this); {
		pCamera_->SetTarget(pPlayer_);
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
