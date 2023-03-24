#include <fstream>
#include <iostream>

namespace Btd
{
    class BloonDB
    {
    private:
        string route;

    public:
        void GetRoutes()
        {
            std::string delimiter = ",";
            std::ifstream fin("resources/bloon/round.csv");
            while (fin)
            {
                std::string s;
                getline(fin, s);
                size_t pos = 0;
                std::string token;
                std::string time;
                bool flag = true;
                while (flag)
                {
                    if ((pos = s.find(delimiter)) == std::string::npos)
                    {
                        flag = false;
                    }
                    token = s.substr(0, pos);
                    s.erase(0, pos + delimiter.length());
                    time = s.substr(0, pos);
                    s.erase(0, pos + delimiter.length());
                    int tmp = stoi(time);
                    
                    switch (token) {  }
                }
            }
            fin.close();
        }
    };
} // namespace Btd
