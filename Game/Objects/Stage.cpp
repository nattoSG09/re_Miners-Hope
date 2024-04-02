#include "Stage.h"
#include "StageObject.h"
#include "../../Engine/Json/JsonReader.h"

Stage::Stage(GameObject* _parent)
	:GameObject(_parent,"Stage")
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

void Stage::Load(std::string fileName)
{
	// 保存されていない現在のデータを削除
	for (auto obj : objects_) {
		obj->KillMe();
	}
	objects_.clear();

	json objectData;
	if (JsonReader::Load(fileName, objectData) == false)return;

	// ロードしたデータを使ってオブジェクトを復元する
	for (auto it = objectData.begin(); it != objectData.end(); ++it) {
		std::string objectName = it.key(); // オブジェクトの名前を取得

		// ロードしたデータから位置、回転、スケールを復元する
		auto& data = it.value();

		StageObject* obj = nullptr;
		if (data.contains("modelFilePath_")) {
			obj = CreateStageObject(objectName, data["modelFilePath_"], this);
		}

		if (obj == nullptr)continue;

		if (data.contains("position_")) {
			obj->transform_.position_.x = data["position_"]["x"];
			obj->transform_.position_.y = data["position_"]["y"];
			obj->transform_.position_.z = data["position_"]["z"];
		}
		if (data.contains("rotate_")) {
			obj->transform_.rotate_.x = data["rotate_"]["x"];
			obj->transform_.rotate_.y = data["rotate_"]["y"];
			obj->transform_.rotate_.z = data["rotate_"]["z"];
		}
		if (data.contains("scale_")) {
			obj->transform_.scale_.x = data["scale_"]["x"];
			obj->transform_.scale_.y = data["scale_"]["y"];
			obj->transform_.scale_.z = data["scale_"]["z"];
		}
	}
}
