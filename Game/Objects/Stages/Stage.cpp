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
				// �Z�[�u����
				if (ImGui::MenuItem("Save")) {
					Save();
				}

				// ���[�h����
				if (ImGui::MenuItem("Load")) {
					Load();
				}

				// �폜���s��
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

		// �V�����I�u�W�F�N�g�𐶐�����
		if (ImGui::TreeNode("CreateButtons")) {
			if (ImGui::Button("Floor")) {
				CreateStageObject("Floor" + std::to_string(objects_.size() + 1), "Models/Stage/Floor.fbx", this);
			}
			ImGui::TreePop();
		}

		// �쐬���ꂽ�I�u�W�F�N�g�̈ʒu����ҏW����
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
	// �Z�[�u�f�[�^�𐶐�����
	json saveData; {
		for (auto obj : objects_) {
			saveData[obj->objectName_]["position_"] = { obj->transform_.position_.x,transform_.position_.y ,transform_.position_.z };
			saveData[obj->objectName_]["rotate_"] = { obj->transform_.rotate_.x,transform_.rotate_.y ,transform_.rotate_.z };
			saveData[obj->objectName_]["scale_"] = { obj->transform_.scale_.x,transform_.scale_.y ,transform_.scale_.z };
			//saveData[obj->objectName_]["modelFilePath_"] = obj->modelFilePath_;
		}
	}

	// �Z�[�u����
	return JsonReader::Save("Data/stageObjects.json", saveData);
}

bool Stage::Load()
{
	// �ۑ�����Ă��Ȃ����݂̃f�[�^���폜
	for (auto obj : objects_) {
		obj->KillMe();
	}
	objects_.clear();

	json loadData;

	// ���[�h����
	if(JsonReader::Load("Data/stageObjects.json", loadData) == false)return false;

	// ���[�h�����f�[�^���g���ăI�u�W�F�N�g�𕜌�����
	for (auto it = loadData.begin(); it != loadData.end(); ++it) {
		std::string objectName = it.key(); // �I�u�W�F�N�g�̖��O���擾

		StageObject* obj = CreateStageObject(objectName, "Models/Stage/Floor.fbx", this);
		// ���[�h�����f�[�^����ʒu�A��]�A�X�P�[���𕜌�����
		auto& transformData = it.value();
		if (transformData.contains("position_")) {
			obj->transform_.position_.x = transformData["position_"][0];
			obj->transform_.position_.y = transformData["position_"][1];
			obj->transform_.position_.z = transformData["position_"][2];
		}
		if (transformData.contains("rotate_")) {
			obj->transform_.rotate_.x = transformData["rotate_"][0];
			obj->transform_.rotate_.y = transformData["rotate_"][1];
			obj->transform_.rotate_.z = transformData["rotate_"][2];
		}
		if (transformData.contains("scale_")) {
			obj->transform_.scale_.x = transformData["scale_"][0];
			obj->transform_.scale_.y = transformData["scale_"][1];
			obj->transform_.scale_.z = transformData["scale_"][2];
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
