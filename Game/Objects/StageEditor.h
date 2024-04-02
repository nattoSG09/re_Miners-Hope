#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include <vector>

class Stage;
class StageObject;

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

	void DrawWorldOutliner(std::vector<StageObject*> _objects);
	void DrawDetails(std::vector<StageObject*> _objects);

	bool GetModelFileName(std::string& _dst);
	void AddStageObject();
	void SaveStageObject();
	void LoadStageObject();
	void NameChange(StageObject* _obj);
};

