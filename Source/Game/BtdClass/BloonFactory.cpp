#include "stdafx.h"
#include "BloonFactory.h"

namespace Btd
{
    queue<Bloon> BloonFactory::BloonPool = queue<Bloon>();
    vector<Bloon> BloonFactory::BloonVector = vector<Bloon>();
    vector<UnitRound> BloonFactory::BloonRound;
    int BloonFactory::BloonCounter = 0;
    int BloonFactory::BloonTimer = 0;
    vector<string> BloonFactory::balloonPath = {
        "Resources/bloon/bloon_red.bmp", "Resources/bloon/bloon_blue.bmp", "Resources/bloon/bloon_green.bmp",
        "Resources/bloon/bloon_yellow.bmp", "Resources/bloon/bloon_black.bmp",
        "Resources/bloon/bloon_white.bmp",
    };
}
