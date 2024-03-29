#pragma once
#include "../../Engine/GameObject/GameObject.h"

class Stage;

class StageEditor :  public GameObject
{
	Stage* editTarget_;
	int selectedIndex_;
public:
	StageEditor(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void SetTarget(Stage* _target) { editTarget_ = _target; }

	bool GetModelFileName(std::string& _dst);
	void AddStageObject();
};

