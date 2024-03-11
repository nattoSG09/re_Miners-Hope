#pragma once
#include "../../../Engine/GameObject/GameObject.h"

class StageObject : public GameObject
{
protected:
	int hModel_;

public:
	StageObject(GameObject* parent);
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;

	int GetModelHandle() { return hModel_; }
	void SetModelHandle(int _hModel) { hModel_ = hModel_; }

	void Load(std::string _objName);
};
