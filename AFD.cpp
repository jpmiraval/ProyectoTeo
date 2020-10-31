#include "AFD.h"

AFD::AFD(int n, int initial_state, std::vector<int> finals) : n_states(n), n_final(finals.size()) {
    for(int i = 0; i < n_states; i++)
        states.push_back(new state(i));
        set_final_states(finals);
        fill_transitions();
}

void AFD::set_final_states(std::vector<int> finals){
    for(auto &i: finals)
        states[i]->set_is_final(true);
}

void AFD::fill_transitions(){
    int from, with, to;
    for(int i = 0; i < n_states*2; ++i){
        std::cin >> from >> with >> to;
        states[from]->set_relation(with, states[to]);
    }
}