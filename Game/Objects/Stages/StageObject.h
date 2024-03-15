#pragma once
#include "../../../Engine/GameObject/GameObject.h"
#include <string>
using std::string;

class StageObject : public GameObject
{
	string modelFilePath_;
	int hModel_;
	friend class Stage;

public:
	StageObject(string _name, string _modelFilePath, GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

