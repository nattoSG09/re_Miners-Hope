#include "StageObject.h"
#include "../../../Engine/ResourceManager/Model.h"
#include "../../../Engine/Json/JsonReader.h"

StageObject::StageObject(GameObject* parent)
	:GameObject(parent,"StageObject"),hModel_(-1)
{
}

void StageObject::Initialize()
{
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

void StageObject::Load(string _objName)
{
	json objData;
	if (!JsonReader::Load("Data/stageObjects.json", objData))return;

	// トランスフォームを設定
	transform_.position_ = { objData[_objName]["POSITION"][0],objData[_objName]["POSITION"][1] ,objData[_objName]["POSITION"][2] };
	transform_.rotate_ = { objData[_objName]["ROTATE"][0],objData[_objName]["ROTATE"][1] ,objData[_objName]["ROTATE"][2] };
	transform_.scale_ = { objData[_objName]["SCALE"][0],objData[_objName]["SCALE"][1] ,objData[_objName]["SCALE"][2] };
	
	// モデルをロード
	string filePath = objData[_objName]["MODEL_FILEPATH"];
	hModel_ = Model::Load(filePath);
}
