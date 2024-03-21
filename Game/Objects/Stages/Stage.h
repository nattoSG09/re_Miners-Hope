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
	string modelFileName_;
public:
	Stage(GameObject* parent,string _modelFileName);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	vector<StageObject*> GetStageObjects() { return objects_; }
private:
	void Edit();
	bool Save(string _modelFileName);
	bool Load(string _modelFileName);
	StageObject* CreateStageObject(string _name, string _modelFilePath, GameObject* _parent);
};

Stage* CreateStage(string _modelFilePath, GameObject* parent);