#include "UIPanel.h"
#include "CrossHair.h"

UIPanel::UIPanel(GameObject* parent)
	:GameObject(parent,"UIPanel")

{
}

void UIPanel::Initialize()
{
	Instantiate<CrossHair>(this);
}

void UIPanel::Update()
{
}

void UIPanel::Draw()
{
}

void UIPanel::Release()
{
}
