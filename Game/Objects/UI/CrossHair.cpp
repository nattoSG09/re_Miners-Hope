#include "CrossHair.h"
#include "../../../Engine/ResourceManager/Image.h"

CrossHair::CrossHair(GameObject* parent)
	:GameObject(parent,"CrossHair"),hPict_(-1)
{
}

void CrossHair::Initialize()
{
	hPict_ = Image::Load("Images/crossHair.png");
}

void CrossHair::Update()
{
}

void CrossHair::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void CrossHair::Release()
{
}
