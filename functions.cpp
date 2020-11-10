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
	auto afn = new AFN(afd);
	std::cout << '\n'; afn->printAFN();
	auto afd2 = new AFD(afn);
	std::cout << '\n'; afd2->printAFD();
}