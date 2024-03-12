#pragma once
#include "../../../Engine/GameObject/GameObject.h"

class StageObject : public GameObject
{
protected:
	int hModel_;
	std::string filePath_;
	std::string name_;
public:
	StageObject(GameObject* parent,std::string name,std::string filePath);
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;

	int GetModelHandle() { return hModel_; }
	void SetModelHandle(int _hModel) { hModel_ = hModel_; }
	void Load();
	void Save();
};

StageObject* CreateObject(GameObject* parent,std::string name, std::string modelFilePath);