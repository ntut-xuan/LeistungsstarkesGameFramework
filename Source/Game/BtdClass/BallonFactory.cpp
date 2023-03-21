#include "stdafx.h"
#include "BallonFactory.h"

namespace Btd
{
    queue<Ballon> BallonFactory::BallonPool= queue<Ballon>();
    vector<Ballon> BallonFactory::BallonVector = vector<Ballon>();
}
