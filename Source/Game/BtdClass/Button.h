#pragma once
#include "GameObject.h"
#include "BtdUtil.h"

namespace Btd
{
    class Button : public GameObject 
    {
    public:
        Button(Attribute attribute);
        ~Button();
        bool IsFocus();
    private:
        Attribute _attribute;
    };
}
