#include "SkySphere.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
SkySphere::SkySphere(GameObject* parent)
	:GameObject(parent,"SkySphere"),hModel_(-1)
{
}

void SkySphere::Initialize()
{
	hModel_ = Model::Load("Models/SkySphere.fbx");
}

void SkySphere::Update()
{
}

void SkySphere::Draw()
{
	Direct3D::SetShader(Direct3D::SHADER_TYPE::SHADER_SKY);
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	Direct3D::SetShader(Direct3D::SHADER_TYPE::SHADER_3D);

}

void SkySphere::Release()
{
}
