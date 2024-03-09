#pragma once
#include "Engine/GameObject/GameObject.h"
#include <string>
using std::string;

class TestScene : public GameObject
{
	bool isSave;
	string pn;
	string en;
public:
	TestScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
