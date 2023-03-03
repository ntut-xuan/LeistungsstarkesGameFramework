#include "stdafx.h"
#include "Throwable.h"


void Throwable::Update()
{
    if (GetActive())
    {
        Move();
    }
}

float Throwable::GetSpeed()
{
    return speed;
}

void Throwable::Move()
{
    pair<float, float> moveDirection = GetMoveDirection();
    float speed = GetSpeed();
    pair<float, float> dletaMove;
    dletaMove.first = moveDirection.first * speed;
    dletaMove.second = moveDirection.second * speed;
    int top = GetTop() + static_cast<int>(dletaMove.second);
    int left = GetLeft() + static_cast<int>(dletaMove.first);
    SetTopLeft(left, top);
}

//TODO check touch baloon
