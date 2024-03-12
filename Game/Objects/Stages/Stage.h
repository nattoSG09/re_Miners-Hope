#pragma once
#include "../../../Engine/GameObject/GameObject.h"
#include <vector>
using std::vector;

class StageObject;

class Stage : public GameObject
{
	vector<StageObject*> objects_;
public:
	Stage(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};