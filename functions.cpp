#include "functions.h"

AFD* read_AFD(){
    std::vector<int> final_states;
	int n, initial_state, n_final_states, temp;
	std::cin >> n >> initial_state >> n_final_states;

	while(n_final_states--){
		std::cin >> temp;
		final_states.push_back(temp);
	}
	return new AFD(n, initial_state, final_states);
}

void  brzozowski(){
    auto afd = read_AFD();
    afd->printAFD();
    auto afnR = new AFN(afd);
    std::cout << '\n'; afnR->printAFN();
    auto afdR = new AFD(afnR);
    std::cout << '\n'; afdR->printAFD();
    auto afnF= new AFN (afdR);
    std::cout << '\n'; afnF->printAFN();
    auto afdF = new AFD (afnF);
    std::cout << '\n'; afdF->printAFD();

    std::cout << "\nResult:";
    afdF->getAFD();
}