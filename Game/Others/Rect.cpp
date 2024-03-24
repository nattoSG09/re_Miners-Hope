#include "Rect.h"

Rect::Rect()
    :Rect(0.f,0.f,5.f,5.f)
{
}

Rect::Rect(float _cx, float _cy, float _width, float _height)
	:Rect(XMFLOAT2(_cx,_cy),_width,_height)
{
}

Rect::Rect(XMFLOAT2 _center, float _width, float _height)
	:center_(_center),width_(_width),height_(_height)
{
}

bool Rect::ContainsPoint(float _px, float _py)
{
	return ContainsPoint(XMFLOAT2(_px,_py));
}

bool Rect::ContainsPoint(XMFLOAT2 _point)
{
    // ��`�̍���̍��W�����߂�
    XMFLOAT2 upperLeftPoint = { center_.x - (width_ / 2), center_.y - (height_ / 2) };

    // ��`�̉E���̍��W
    XMFLOAT2 bottomRightPoint = { center_.x + (width_ / 2), center_.y + (height_ / 2) };

    // �_����`���ɂ��邩�ǂ����𔻒�
    return (_point.x >= upperLeftPoint.x && _point.x <= bottomRightPoint.x &&
        _point.y >= upperLeftPoint.y && _point.y <= bottomRightPoint.y);
}
