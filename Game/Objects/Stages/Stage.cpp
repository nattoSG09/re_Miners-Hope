#include "Stage.h"
#include "StageObject.h"
#include "../../../Engine/ImGui/imgui.h"
Stage::Stage(GameObject* parent)
	:GameObject(parent)
{
}

void Stage::Initialize()
{
}

void Stage::Update()
{
#ifdef _DEBUG
	ImGui::Begin("CreateObject"); {
		static int number = 0;
		if (ImGui::Button("Floor")) {
			objects_.push_back(CreateObject(this, "Object" + std::to_string(number), "Models/Stage/stageFloor.fbx"));
		}
	}
	ImGui::End();
#endif // _DEBUG

}

void Stage::Draw()
{
}

void Stage::Release()
{
	for (auto obj : objects_) {
		obj->Save();
	}
}
