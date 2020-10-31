#include "Brzozowski.h"

void  brzozowski(){
	std::vector<int> final_states;
	int n, initial_state, n_final_states, temp;
	std::cin >> n >> initial_state >> n_final_states;

	while(n_final_states--){
		std::cin >> temp;
		final_states.push_back(temp);
	}

	AFD* afd = new AFD(n, initial_state, final_states);

	
}