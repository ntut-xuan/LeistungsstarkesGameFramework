#include <fstream>
#include <iostream>
namespace Btd {
class BloonDB {
public:
  void GetRoutes() {

    std::ifstream fin("./mytest.txt");
    std::string s;
    while (fin) {
      getline(fin, s);
    }
    fin.close();
  }
};
} // namespace Btd