#include "stdafx.h"
#include "GameObject.h"

namespace Btd
{
    void GameObject::Update()
    {
    }

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

    void GameObject::SetCenter(int x, int y)
    {
		int halfWidth = (location.right - location.left) / 2;
		int halfHeight = (location.bottom - location.top) /2;
		location.left = x - halfWidth;
		location.top = y - halfHeight;
        location.right = x + halfWidth;
        location.bottom = y + halfHeight;
    }

}
