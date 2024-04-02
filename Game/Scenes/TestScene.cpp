#include "TestScene.h"

#include "../../Game/Objects/StageEditor.h"
#include "../../Game/Objects/Stage.h"

#include "../../Engine/ResourceManager/Image.h"

TestScene::TestScene(GameObject * _parent)
	: GameObject(_parent, "TestScene")
{
}

void TestScene::Initialize()
{
	// ステージを用意
	Stage* pStage = Instantiate<Stage>(this);

#ifdef _DEBUG
	// ステージエディタを用意
	StageEditor* pStageEditor = Instantiate<StageEditor>(this);
	pStageEditor->SetTarget(pStage);
#endif // _DEBUG

	pictHandle_ = Image::Load("Images/title_gray01.png");
	SetScale(0.7f);
}

void TestScene::Update()
{
}

void TestScene::Draw()
{
	Image::SetTransform(pictHandle_, transform_);
	Image::Draw(pictHandle_);
}

void TestScene::Release()
{
}
