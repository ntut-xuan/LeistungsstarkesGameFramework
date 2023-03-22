#include "stdafx.h"
#include "BallonFactory.h"

namespace Btd
{
    queue<Ballon> BallonFactory::BallonPool= queue<Ballon>();
    vector<Ballon> BallonFactory::BallonVector = vector<Ballon>();
    vector<UnitRound> BallonFactory::BallonRound;
    int BallonFactory::BallonCounter = 0;
    int BallonFactory::BallonTimer = 0;
}
