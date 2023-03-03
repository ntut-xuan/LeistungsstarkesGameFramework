#include "stdafx.h"
#include "GameObject.h"

void GameObject::SetActive(bool active)
{
    _isActive = active;
}

bool GameObject::GetActive()
{
    return _isActive;
}

void GameObject::SetTag(string tag)
{
    _tag = tag;
}

string GameObject::GetTag()
{
    return _tag;
}
