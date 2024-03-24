#pragma once
#include "../../../Engine/GameObject/GameObject.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

class StageObject;
class Coin;

class Stage : public GameObject
{
	vector<StageObject*> objects_;
	vector<Coin*> coins_;
	string stageFilePath_;
public:
	Stage(GameObject* parent,string _modelFileName);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	vector<StageObject*> GetStageObjects() { return objects_; }
	vector<Coin*> GetStageCoins() { return coins_; }
	void SetStageCoins(vector<Coin*> _coins) { coins_ = _coins; }

	void DeleteCoin(Coin* c);
	void DeleteObject(StageObject* obj);
private:
	void Edit();
	bool Save(string _modelFileName);
	bool Load(string _modelFileName);
	StageObject* CreateStageObject(string _name, string _modelFilePath, GameObject* _parent);
	Coin* CreateCoin(GameObject* parent);
};

Stage* CreateStage(string _modelFilePath, GameObject* parent);