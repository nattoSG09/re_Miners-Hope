#pragma once
#include "../../../Engine/GameObject/GameObject.h"
#include <string>
#include <vector>
using std::string;
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

private:
	void Edit();
	bool Save();
	bool Load();
	StageObject* CreateStageObject(string _name, string _modelFilePath, GameObject* _parent);
};

