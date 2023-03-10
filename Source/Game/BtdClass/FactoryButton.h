#pragma once

#include "Button.h"

namespace Btd
{
    class FactoryButton : public Button
    {
    public:
        FactoryButton() = default;
        ~FactoryButton() = default;
        void Update() override;
        void SetAttribute(Attribute attribute);
    private:
        Attribute _attribute;
    
    };
    
}
