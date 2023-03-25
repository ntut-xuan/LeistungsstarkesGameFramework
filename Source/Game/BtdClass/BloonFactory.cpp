#include "stdafx.h"
#include "BloonFactory.h"

namespace Btd
{
    queue<Bloon> BloonFactory::BloonPool= queue<Bloon>();
    vector<Bloon> BloonFactory::BloonVector = vector<Bloon>();
    vector<UnitRound> BloonFactory::BloonRound;
    int BloonFactory::BloonCounter = 0;
    int BloonFactory::BloonTimer = 0;
}
