#include "StageObject.h"
#include "../../Engine/ResourceManager/Model.h"

StageObject::StageObject(std::string _name, std::string _modelFilePath,GameObject* _parent)
	:GameObject(_parent, _name),modelHandle_(NONE),modelFilePath_(_modelFilePath)
{
}

void StageObject::Initialize()
{
	// ƒ‚ƒfƒ‹‚ð“Ç‚Ýž‚Þ
	modelHandle_ = Model::Load(modelFilePath_);
	assert(modelHandle_ >= NONE);
}

void StageObject::Update()
{
}

void StageObject::Draw()
{
	if (modelHandle_ >= NONE)return;

	// •`‰æˆ—‚ðs‚¤
	Model::SetTransform(modelHandle_, transform_);
	Model::Draw(modelHandle_);
}

void StageObject::Release()
{
}

StageObject* CreateStageObject(std::string _name, std::string _modelFilePath, GameObject* _parent)
{
	StageObject* obj = new StageObject(_name, _modelFilePath, _parent);
	obj->Initialize();
	if (_parent != nullptr)_parent->PushBackChild(obj);
	return obj;
}
