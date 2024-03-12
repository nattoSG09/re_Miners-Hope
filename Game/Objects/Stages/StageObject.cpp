#include "StageObject.h"
#include "../../../Engine/ResourceManager/Model.h"
#include "../../../Engine/Json/JsonReader.h"
#include "../../../Engine/ImGui/imgui.h"

StageObject::StageObject(GameObject* parent,std::string _name,std::string _filePath)
	:GameObject(parent,"StageObject"),hModel_(-1),filePath_(_filePath),name_(_name)
{
}

void StageObject::Initialize()
{
	hModel_ = Model::Load(filePath_);
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

void StageObject::Load()
{
	json objData;
	if (!JsonReader::Load("Data/stageObjects.json", objData))return;

	// トランスフォームを設定
	transform_.position_ = { objData[name_]["POSITION"][0],objData[name_]["POSITION"][1] ,objData[name_]["POSITION"][2] };
	transform_.rotate_ = { objData[name_]["ROTATE"][0],objData[name_]["ROTATE"][1] ,objData[name_]["ROTATE"][2] };
	transform_.scale_ = { objData[name_]["SCALE"][0],objData[name_]["SCALE"][1] ,objData[name_]["SCALE"][2] };

	filePath_ = objData[name_]["MODEL_FILEPATH"];
}

void StageObject::Save()
{
	json objData{
		{name_,
			{"POSITION",{transform_.position_.x,transform_.position_.y,transform_.position_.z}},
			{"ROTATE",{transform_.rotate_.x,transform_.rotate_.y,transform_.rotate_.z}},
			{"SCALE",{transform_.scale_.x,transform_.scale_.y,transform_.scale_.z}},
			{"MODEL_FILEPATH",filePath_}
		}
	};
	
	if (!JsonReader::Save("Data/StageObjects.json", objData))return;
}

StageObject* CreateObject(GameObject* parent,std::string _name, std::string modelFilePath)
{
	StageObject* obj = new StageObject(parent,_name,modelFilePath);
	if (parent != nullptr)parent->PushBackChild(obj);
	obj->Initialize();
	return obj;
}