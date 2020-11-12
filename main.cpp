#include "functions.h"

int main(){
    //brzozowski();
    auto afd = read_AFD();
    Eq_test(*afd);
    /*
    auto afn = new AFN(4, 0, std::vector<int>{1, 3}, 8);
    std::cout << '\n'; afn->printAFN();
    auto afd2 = new AFD(afn);
    std::cout << '\n'; afd2->printAFD();*/

    return EXIT_SUCCESS;
}
