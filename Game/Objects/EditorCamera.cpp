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

    // カメラの焦点・位置を格納する変数を用意
    XMFLOAT3 camTarget{};
    XMFLOAT3 camPosition{};

    // カメラの中心点を設定
    XMFLOAT3 center = transform_.position_;

    // 角度を設定
    {
        if (Input::IsKey(DIK_UP)) angle_.x++;
        if (Input::IsKey(DIK_DOWN)) angle_.x--;
        if (Input::IsKey(DIK_LEFT)) angle_.y--;
        if (Input::IsKey(DIK_RIGHT)) angle_.y++;
    }
    
    
    // ｙ軸の回転を行う
    {
        // 回転行列を作成
        XMMATRIX rotateY = XMMatrixRotationY(XMConvertToRadians(angle_.y));
        // ↑の行列を元に回転
        XMVECTOR center_To_camTarget = { 0,0,1,0 };
        center_To_camTarget = XMVector3Transform(center_To_camTarget, rotateY);
        // 長さを加える
        static float center_To_camTargetDistance = 70.f;
#ifdef _DEBUG
        ImGui::SliderFloat("center_To_camTargetDistance", &center_To_camTargetDistance, 1.0f, 100.f);
#endif // _DEBUG
        if (Input::IsMouseButton(1))center_To_camTargetDistance = 3.f;
        center_To_camTarget *= center_To_camTargetDistance;
        // 原点からの位置を求めて、カメラの焦点を設定
        XMVECTOR origin_To_camTarget = XMLoadFloat3(&center) + center_To_camTarget;
        XMStoreFloat3(&camTarget, origin_To_camTarget);
        // center_To_camTargetの逆ベクトルを用意
        XMVECTOR center_To_camPosition = -center_To_camTarget;
        // ちょっと回転させる
        float littleAngle = -30.f;
        if (Input::IsMouseButton(1))littleAngle = -60.f;
        center_To_camPosition = XMVector3Transform(center_To_camPosition, XMMatrixRotationY(XMConvertToRadians(littleAngle)));
        // 原点からの位置を求めて、カメラの位置を設定
        XMVECTOR origin_To_camPosition = XMLoadFloat3(&center) + center_To_camPosition;
        XMStoreFloat3(&camPosition, origin_To_camPosition);
    }
    // ｘ軸の回転を行う
    {
        // 縦回転の軸を作成
        XMVECTOR newCenter = (XMLoadFloat3(&camPosition) + XMLoadFloat3(&camTarget)) * 0.5f;
        XMFLOAT3 prevCenter = center;
        XMStoreFloat3(&center, newCenter);
        XMVECTOR axis = XMLoadFloat3(&center) - XMLoadFloat3(&prevCenter);
        //// 回転行列を作成
        XMMATRIX rotateAxis = XMMatrixRotationAxis(axis, XMConvertToRadians(angle_.x));
        //　焦点を設定 
        XMVECTOR newCenter_To_camTarget = XMLoadFloat3(&camTarget) - XMLoadFloat3(&prevCenter);
        newCenter_To_camTarget = XMVector3Transform(newCenter_To_camTarget, rotateAxis);
        XMVECTOR origin_To_camTarget = XMLoadFloat3(&prevCenter) + newCenter_To_camTarget;
        XMStoreFloat3(&camTarget, origin_To_camTarget);
        // 位置を設定
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
