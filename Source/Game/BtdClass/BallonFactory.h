#include "Ballon.h"
#include <queue>
#include <vector>
#include <string>



namespace Btd {
    class BallonFactory{
        public:
        static queue<Ballon, vector<Ballon>> BallonPool;
        //todo idk should new or not 

        Ballon MakeBallon(string type){
            Ballon tmpBallon;
            tmpBallon.LoadEmptyBitmap(30, 30);
            tmpBallon.SetTopLeft(10,10);
            BallonPool.enqueue(tmpBallon);
            return  tmpBallon;
        }

    }
}