#include "structures/automatas.h"

AFD* read_AFD();
void  brzozowski();
int** Eq_test(AFD afd);
int** Eq_test_op(AFD afd);
AFD* Huffman_Moore(AFD afd);
AFD* Hopcroft(AFD afd);
