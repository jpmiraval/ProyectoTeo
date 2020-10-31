#include "automatas.h"

AFD::AFD(int n, int initial_state, std::vector<int> finals) : n_states(n), n_final(finals.size()) {
        for(int i = 0; i < n_states; ++i)
            states.push_back(new state_d(i));
        set_final_states(finals);
        fill_transitions();
        initial = states[initial_state];
    };

void AFD::set_final_states(std::vector<int> finals){
    for(auto &i: finals)
        states[i]->is_final = true;
}

void AFD::fill_transitions(){
    int from, with, to;
    for(int i = 0; i < n_states*2; ++i){
        std::cin >> from >> with >> to;
        states[from]->set_relation(with, states[to]->state_number);
    }
}



AFN::AFN(AFD* afd): n_states(afd->n_states), n_final(afd->n_final) {
    for(int i = 0; i < n_states; ++i)
        states.push_back(new state_n(i));
    
    for (auto &state: afd->states){
        states[state->zero]->set_relation(0, states[state->state_number]);
        states[state->one]->set_relation(1, states[state->state_number]);

        if (state->is_final)
            states[state->state_number]->is_final = true;
    }
    initial = states[afd->initial->state_number];
}

void AFN::printAFN(){
    for (auto& state: states){
        std::cout << "Number: " << state->state_number << "    Zero: ";
        for (auto& i: state->zero)
            std::cout << i->state_number << " ";
        std::cout << "    One: ";
        for (auto& i: state->one)
            std::cout << i->state_number << " ";
        std::cout << "\n";
    }
}