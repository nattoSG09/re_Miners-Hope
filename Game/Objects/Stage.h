#pragma once
#include "../../Engine/GameObject/GameObject.h"

#include <vector>

class StageObject;

class Stage : public GameObject
{
	std::vector<StageObject*> objects_;
public:
	Stage(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void AddObject(StageObject* _object) { objects_.push_back(_object); }

	std::vector<StageObject*> GetStageObjects() { return objects_; }
};

