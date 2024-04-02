#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "StageEditor.h"

class StageObject : public GameObject
{
	std::string modelFilePath_;
	int modelHandle_;
	friend StageEditor;
	friend Stage;
public:
	StageObject(std::string _name, std::string _modelFilePath,GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

StageObject* CreateStageObject(std::string _name, std::string _modelFilePath, GameObject* _parent);