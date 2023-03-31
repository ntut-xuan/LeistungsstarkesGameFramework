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

    Vector2 GameObject::GetCenter()
    {
        return {static_cast<float>(GetLeft()) + GetWidth() / 2, static_cast<float>(GetTop()) + GetHeight() / 2};
    }


    void GameObject::SetCenter(int x, int y)
    {
        SetTopLeft(x - GetWidth() / 2, y - GetHeight() / 2);
    }

    void GameObject::SetBottomCenter(int x, int y)
    {
        SetTopLeft(x - GetWidth() / 2, y - GetHeight());
    }

    Vector2 GameObject::GetBottomCenter()
    {
        return {static_cast<float>(GetLeft()) + GetWidth() / 2, static_cast<float>(GetTop()) + GetHeight()};
    }

    bool IsOverlap(GameObject& character, GameObject& other)
    {
        if ((character.GetTop() + character.GetHeight() >= other.GetTop() &&
                character.GetTop() <= other.GetTop() + other.GetHeight())
            && (character.GetLeft() + character.GetWidth() >= other.GetLeft() &&
                character.GetLeft() <= other.GetLeft() + other.GetWidth()))
        {
            return true;
        }
        return false;
    }
}
