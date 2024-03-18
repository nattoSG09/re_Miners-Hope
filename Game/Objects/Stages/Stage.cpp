#include "Stage.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/Json/JsonReader.h"
#include "StageObject.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage")
{
}

void Stage::Initialize()
{
	Load();
}

void Stage::Update()
{
#ifdef _DEBUG
	Edit();
#endif // _DEBUG

}

void Stage::Draw()
{
}

void Stage::Release()
{
}

void Stage::Edit()
{
	ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_MenuBar); {
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File"))
			{
				// セーブする
				if (ImGui::MenuItem("Save")) {
					Save();
				}

				// ロードする
				if (ImGui::MenuItem("Load")) {
					Load();
				}

				// 削除を行う
				if (ImGui::MenuItem("delete")) {
					for (auto obj : objects_) {
						obj->KillMe();
					}
					objects_.clear();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		// 新しいオブジェクトを生成する
		if (ImGui::TreeNode("CreateButtons")) {
			if (ImGui::Button("Floor")) {
				CreateStageObject("Floor" + std::to_string(objects_.size() + 1), "Models/Stage/Floor.fbx", this);
			}
			if (ImGui::Button("Wall")) {
				CreateStageObject("Wall" + std::to_string(objects_.size() + 1), "Models/Stage/Wall.fbx", this);
			}
			ImGui::TreePop();
		}

		// 作成されたオブジェクトの位置等を編集する
		if (ImGui::TreeNode("ObjectList")) {
			for (auto obj : objects_) {
				if (ImGui::TreeNode(obj->objectName_.c_str())) {
					if (ImGui::TreeNode("position_")) {
						ImGui::InputFloat("x", &obj->transform_.position_.x);
						ImGui::InputFloat("y", &obj->transform_.position_.y);
						ImGui::InputFloat("z", &obj->transform_.position_.z);
						ImGui::TreePop();
					}

					if (ImGui::TreeNode("rotate_")) {
						ImGui::InputFloat("x", &obj->transform_.rotate_.x);
						ImGui::InputFloat("y", &obj->transform_.rotate_.y);
						ImGui::InputFloat("z", &obj->transform_.rotate_.z);
						ImGui::TreePop();
					}

					if (ImGui::TreeNode("scale_")) {
						ImGui::InputFloat("x", &obj->transform_.scale_.x);
						ImGui::InputFloat("y", &obj->transform_.scale_.y);
						ImGui::InputFloat("z", &obj->transform_.scale_.z);
						ImGui::TreePop();
					}
					ImGui::TreePop();
				}

			}
			ImGui::TreePop();
		}
	}ImGui::End();

}

bool Stage::Save()
{
	// セーブデータを生成する
	json saveData; {
		for (auto obj : objects_) {
			saveData[obj->objectName_]["position_"] = { obj->transform_.position_.x,transform_.position_.y ,transform_.position_.z };
			saveData[obj->objectName_]["rotate_"] = { obj->transform_.rotate_.x,transform_.rotate_.y ,transform_.rotate_.z };
			saveData[obj->objectName_]["scale_"] = { obj->transform_.scale_.x,transform_.scale_.y ,transform_.scale_.z };
			saveData[obj->objectName_]["modelFilePath_"] = obj->modelFilePath_;
		}
	}

	// セーブする
	return JsonReader::Save("Data/stageObjects.json", saveData);
}

bool Stage::Load()
{
	// 保存されていない現在のデータを削除
	for (auto obj : objects_) {
		obj->KillMe();
	}
	objects_.clear();

	json loadData;

	// ロードする
	if(JsonReader::Load("Data/stageObjects.json", loadData) == false)return false;

	// ロードしたデータを使ってオブジェクトを復元する
	for (auto it = loadData.begin(); it != loadData.end(); ++it) {
		std::string objectName = it.key(); // オブジェクトの名前を取得

		// ロードしたデータから位置、回転、スケールを復元する
		auto& data = it.value();

		StageObject* obj = nullptr;
		if (data.contains("modelFilePath_")) {
			obj = CreateStageObject(objectName, data["modelFilePath_"], this);
		}

		if (obj == nullptr)continue;

		if (data.contains("position_")) {
			obj->transform_.position_.x = data["position_"][0].get<float>();
			obj->transform_.position_.y = data["position_"][1].get<float>();
			obj->transform_.position_.z = data["position_"][2].get<float>();
		}
		if (data.contains("rotate_")) {
			obj->transform_.rotate_.x = data["rotate_"][0].get<float>();
			obj->transform_.rotate_.y = data["rotate_"][1].get<float>();
			obj->transform_.rotate_.z = data["rotate_"][2].get<float>();
		}
		if (data.contains("scale_")) {
			obj->transform_.scale_.x = data["scale_"][0].get<float>();
			obj->transform_.scale_.y = data["scale_"][1].get<float>();
			obj->transform_.scale_.z = data["scale_"][2].get<float>();
		}
	}

	return true;
}

StageObject* Stage::CreateStageObject(string _name, string _modelFilePath, GameObject* _parent)
{
	StageObject* obj = new StageObject(_name, _modelFilePath, _parent);
	obj->Initialize();
	if (_parent != nullptr)_parent->PushBackChild(obj);
	objects_.push_back(obj);
	return obj;
}
