#pragma once
#include "../../Library/gameutil.h"
#include "Throwable.h"
#include "Tower.h"

namespace Btd {
	class DartMonkey : public  Tower{
	public:
		DartMonkey();
        void PushThrowablePool();
	private:
	};

}