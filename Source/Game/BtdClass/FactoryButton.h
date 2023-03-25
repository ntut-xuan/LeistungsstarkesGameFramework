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
        void SetAttribute(TowerType attribute);
    private:
        TowerType _attribute;
    
    };
    
}
