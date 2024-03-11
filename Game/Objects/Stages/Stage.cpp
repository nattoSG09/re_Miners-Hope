#include "Stage.h"
#include "StageObject.h"
#include "../../../Engine/ResourceManager/Model.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent)
{
}

void Stage::Initialize()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
}

void Stage::Release()
{
}

StageObject* Stage::SetingStageObject(std::string objName)
{
	StageObject* obj = Instantiate<StageObject>(this);
	obj->Load(objName);
	objects_.push_back(obj);
	return obj;
}
