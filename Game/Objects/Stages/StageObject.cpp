#include "StageObject.h"
#include "../../../Engine/ResourceManager/Model.h"

StageObject::StageObject(string _name, string _modelFilePath, GameObject* _parent)
	:GameObject(_parent,_name),modelFilePath_(_modelFilePath)
{
}

void StageObject::Initialize()
{
	hModel_ = Model::Load(modelFilePath_);
}

void StageObject::Update()
{
}

void StageObject::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void StageObject::Release()
{
}
