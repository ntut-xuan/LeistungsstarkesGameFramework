#pragma once
#include "../../Library/gameutil.h"
#include "Throwable.h"
#include "Tower.h"

namespace Btd {
	class DartMonkey : public  Tower{
	public:
		DartMonkey()
		{
			_range = 160;
			ThrowablePath = {"resources/towers/bomb/bomb.bmp"};
		}
	private:
	};

}