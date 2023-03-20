#include "stdafx.h"
#include "FactoryButton.h"
#include "TowerFactory.h"

namespace Btd
{
    vector<Tower*> TowerFactory::TowerVector = {};
    void FactoryButton::SetAttribute(Attribute attribute)
    {
        _attribute = attribute;
    }
    void FactoryButton::Update()
    {
        if (_isClicked == true)
        {
            TowerFactory::MakeTower(_attribute);
            SetClicked(false);
        }
    }

    
}
