#include "UIPanel.h"
#include "CrossHair.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../Player.h"

UIPanel::UIPanel(GameObject* parent)
	:GameObject(parent,"UIPanel")

{
}

void UIPanel::Initialize()
{
	Instantiate<CrossHair>(this);

	hp_dispQuestText = Image::Load("Images/dispQuestText.png");
	hp_youDead = Image::Load("Images/youDead.png");
	hp_concentrationline = Image::Load("Images/concentrationline.png");
	hp_gameClear = Image::Load("Images/gameClear.png");
	hp_key = Image::Load("Images/key.png");
	pText_ = new Text;
	pText_->Initialize();
}

void UIPanel::Update()
{
}

void UIPanel::Draw()
{
	Player* p = (Player*)FindObject("Player");
	if (p == nullptr)return;

	if (p->GetCoinNum() == 10) {
		Transform t;
		t.scale_ = { 0.7f,0.7f ,0.7f };
		Image::SetTransform(hp_gameClear, t);
		Image::Draw(hp_gameClear);
		return;
	}

	if (p->IsDead()) {
		// 「YOU DEAD」というテキストを表示する
		Transform t_youDead;
		t_youDead.scale_ = { 0.5f,0.5f, 0.5f };
		Image::SetTransform(hp_youDead, t_youDead);
		Image::Draw(hp_youDead);
	}
	else {
		// 「コインを集めろ」というテキストを表示する
		Transform t_dispQuestText;
		t_dispQuestText.scale_ = { 0.5f,0.5f, 0.5f };
		t_dispQuestText.position_.y += 0.8f;
		Image::SetTransform(hp_dispQuestText, t_dispQuestText);
		Image::Draw(hp_dispQuestText);

		pText_->SetScale(2.f);
		pText_->Draw(1100, 600, p->GetCoinNum());
		pText_->Draw(1150, 600, "/");
		pText_->Draw(1200, 600, 10);

		Transform t_key;
		t_key.scale_ = { 0.6f,0.6f, 0.6f };
		Image::SetTransform(hp_key,t_key);
		Image::Draw(hp_key);

		if (p->IsDash()) {
			Transform t_concentrationline;
			Image::SetTransform(hp_concentrationline, t_concentrationline);
			Image::Draw(hp_concentrationline);
		}
	}
}

void UIPanel::Release()
{
}
