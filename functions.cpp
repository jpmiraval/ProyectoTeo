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
	AFN afnR(afd);
	std::cout << '\n'; afnR.printAFN();
	AFD afdR(&afnR);
	std::cout << '\n'; afdR.printAFD();
    AFN afnF(&afdR);
    std::cout << '\n'; afnF.printAFN();
    AFD afdF(&afnF);
    std::cout << '\n'; afdF.printAFD();

}