#include "functions.h"

int main(){


   //brzozowski();


    AFD *afd = read_AFD();
    AFD afd_bu = *afd;

    std::cout << "Sin optimizar\n\n";
    Eq_test(*afd);
    *afd = afd_bu;
    std::cout << "\nOptimizado\n\n";
    Eq_test_op(*afd);
    *afd = afd_bu;
    auto answer_5 = Hopcroft(*afd);
    *afd = afd_bu;
    auto answer_4 = Huffman_Moore(*afd);
    *afd = afd_bu;
    std::cout << "\n\nHuffman\n\n";
    answer_4 ->printAFD();
    std::cout << "\n\nHopcroft\n\n";
    answer_5 ->printAFD();
    return EXIT_SUCCESS;
}
