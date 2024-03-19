#include "EditorCamera.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ImGui/imgui.h"

EditorCamera::EditorCamera(GameObject* parent)
    :GameObject(parent,"EditorCamera"),isMove_(false)
{
}

void EditorCamera::Initialize()
{
}

void EditorCamera::Update()
{
    if (isMove_ == false)return;

    // �J�����̏œ_�E�ʒu���i�[����ϐ���p��
    XMFLOAT3 camTarget{};
    XMFLOAT3 camPosition{};

    // �J�����̒��S�_��ݒ�
    XMFLOAT3 center = transform_.position_;

    // �p�x��ݒ�
    {
        if (Input::IsKey(DIK_UP)) angle_.x++;
        if (Input::IsKey(DIK_DOWN)) angle_.x--;
        if (Input::IsKey(DIK_LEFT)) angle_.y--;
        if (Input::IsKey(DIK_RIGHT)) angle_.y++;
    }
    
    
    // �����̉�]���s��
    {
        // ��]�s����쐬
        XMMATRIX rotateY = XMMatrixRotationY(XMConvertToRadians(angle_.y));
        // ���̍s������ɉ�]
        XMVECTOR center_To_camTarget = { 0,0,1,0 };
        center_To_camTarget = XMVector3Transform(center_To_camTarget, rotateY);
        // ������������
        static float center_To_camTargetDistance = 70.f;
#ifdef _DEBUG
        ImGui::SliderFloat("center_To_camTargetDistance", &center_To_camTargetDistance, 1.0f, 100.f);
#endif // _DEBUG
        if (Input::IsMouseButton(1))center_To_camTargetDistance = 3.f;
        center_To_camTarget *= center_To_camTargetDistance;
        // ���_����̈ʒu�����߂āA�J�����̏œ_��ݒ�
        XMVECTOR origin_To_camTarget = XMLoadFloat3(&center) + center_To_camTarget;
        XMStoreFloat3(&camTarget, origin_To_camTarget);
        // center_To_camTarget�̋t�x�N�g����p��
        XMVECTOR center_To_camPosition = -center_To_camTarget;
        // ������Ɖ�]������
        float littleAngle = -30.f;
        if (Input::IsMouseButton(1))littleAngle = -60.f;
        center_To_camPosition = XMVector3Transform(center_To_camPosition, XMMatrixRotationY(XMConvertToRadians(littleAngle)));
        // ���_����̈ʒu�����߂āA�J�����̈ʒu��ݒ�
        XMVECTOR origin_To_camPosition = XMLoadFloat3(&center) + center_To_camPosition;
        XMStoreFloat3(&camPosition, origin_To_camPosition);
    }
    // �����̉�]���s��
    {
        // �c��]�̎����쐬
        XMVECTOR newCenter = (XMLoadFloat3(&camPosition) + XMLoadFloat3(&camTarget)) * 0.5f;
        XMFLOAT3 prevCenter = center;
        XMStoreFloat3(&center, newCenter);
        XMVECTOR axis = XMLoadFloat3(&center) - XMLoadFloat3(&prevCenter);
        //// ��]�s����쐬
        XMMATRIX rotateAxis = XMMatrixRotationAxis(axis, XMConvertToRadians(angle_.x));
        //�@�œ_��ݒ� 
        XMVECTOR newCenter_To_camTarget = XMLoadFloat3(&camTarget) - XMLoadFloat3(&prevCenter);
        newCenter_To_camTarget = XMVector3Transform(newCenter_To_camTarget, rotateAxis);
        XMVECTOR origin_To_camTarget = XMLoadFloat3(&prevCenter) + newCenter_To_camTarget;
        XMStoreFloat3(&camTarget, origin_To_camTarget);
        // �ʒu��ݒ�
        XMVECTOR newCenter_To_camPosition = -newCenter_To_camTarget;
        XMVECTOR origin_To_camPosition = XMLoadFloat3(&prevCenter) + newCenter_To_camPosition;
        XMStoreFloat3(&camPosition, origin_To_camPosition);
    }

    Camera::SetTarget(camTarget);
    Camera::SetPosition(camPosition);
}

void EditorCamera::Draw()
{
}

void EditorCamera::Release()
{
}
