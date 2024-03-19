#include "Stage.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/Json/JsonReader.h"
#include "StageObject.h"

Stage::Stage(GameObject* parent, string _modelFileName)
	:GameObject(parent, "Stage"),modelFileName_(_modelFileName)
{
}

void Stage::Initialize()
{
	Load(modelFileName_);
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
					Save(modelFileName_);
				}

				// ���[�h����
				if (ImGui::MenuItem("Load")) {
					Load(modelFileName_);
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
			if (ImGui::Button("Wall")) {
				CreateStageObject("Wall" + std::to_string(objects_.size() + 1), "Models/Stage/Wall.fbx", this);
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

bool Stage::Save(string _modelFileName)
{
	// �Z�[�u�f�[�^�𐶐�����
	json saveData; {
		for (auto obj : objects_) {
			saveData[obj->objectName_]["position_"]["x"] = obj->transform_.position_.x;
			saveData[obj->objectName_]["position_"]["y"] = obj->transform_.position_.y;
			saveData[obj->objectName_]["position_"]["z"] = obj->transform_.position_.z;

			saveData[obj->objectName_]["rotate_"]["x"] = obj->transform_.rotate_.x;
			saveData[obj->objectName_]["rotate_"]["y"] = obj->transform_.rotate_.y;
			saveData[obj->objectName_]["rotate_"]["z"] = obj->transform_.rotate_.z;

			saveData[obj->objectName_]["scale_"]["x"] = obj->transform_.scale_.x;
			saveData[obj->objectName_]["scale_"]["y"] = obj->transform_.scale_.y;
			saveData[obj->objectName_]["scale_"]["z"] = obj->transform_.scale_.z;

			saveData[obj->objectName_]["modelFilePath_"] = obj->modelFilePath_;

		}
	}

	// �Z�[�u����
	return JsonReader::Save(_modelFileName, saveData);
}

bool Stage::Load(string _modelFileName)
{
	// �ۑ�����Ă��Ȃ����݂̃f�[�^���폜
	for (auto obj : objects_) {
		obj->KillMe();
	}
	objects_.clear();

	// ���[�h����
	json loadData;
	if(JsonReader::Load(_modelFileName, loadData) == false)return false;

	// ���[�h�����f�[�^���g���ăI�u�W�F�N�g�𕜌�����
	for (auto it = loadData.begin(); it != loadData.end(); ++it) {
		std::string objectName = it.key(); // �I�u�W�F�N�g�̖��O���擾

		// ���[�h�����f�[�^����ʒu�A��]�A�X�P�[���𕜌�����
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

Stage* CreateStage(string _modelFilePath, GameObject* parent)
{
	Stage* stage = new Stage(parent, _modelFilePath);
	stage->Initialize();

	if (parent != nullptr)parent->PushBackChild(stage);
	return stage;
}
