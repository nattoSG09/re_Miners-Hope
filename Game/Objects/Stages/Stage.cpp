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
		if (ImGui::Button("Floor")) {
			objects_.push_back(CreateObject(this, "Models/Stage/stageFloor.fbx"));
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
