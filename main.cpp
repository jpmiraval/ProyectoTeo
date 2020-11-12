#include "functions.h"

int main(){
    brzozowski();
    std::cout << "\n \nEq\n";
    auto afd = read_AFD();
    Eq_test(*afd);

    return EXIT_SUCCESS;
}
