#include "automatas.h"

AFD::AFD(int n, int initial_state, std::vector<int> finals) : n_states(n), n_final(finals.size()) {
    for(int i = 0; i < n_states; ++i)
        states.push_back(new state_d(i));
    set_final_states(finals);
    fill_transitions();
    initial = states[initial_state];
};

AFD::AFD(AFN* afn){
    std::unordered_map<std::string, int> new_states;
    std::queue<std::string> states_queue;
    for(auto& state: afn->states)
        states.push_back(new state_d(state->state_number));

    int cont = states.size();
    for(auto& state: afn->states){
        verify_state(cont, state, new_states, states_queue);
    }

    while (!states_queue.empty()) {
        auto id = states_queue.front();
        states_queue.pop();
        std::vector<int> zero;
        std::vector<int> one;
        for (auto s: id){
            for(auto &zs: afn->states[(int)s-48]->zero){
                if (std::find(zero.begin(), zero.end(), zs->state_number) == zero.end())
                    zero.push_back(zs->state_number);
                
            }
        }

    }
    

}

void AFD::verify_state(int& cont, state_n* state, std::unordered_map<std::string, int>& new_states, std::queue<std::string>& states_queue){
    if (state->zero.empty()){
        insert_new_state("-1", cont, state->state_number, new_states, states_queue);
    }
    else if (state->zero.size() == 1)
        states[state->state_number]->zero = state->zero[0]->state_number;
    else{
        std::string id;
        for (auto& s: state->zero)
            id += std::to_string(s->state_number);
        insert_new_state(id, cont, state->state_number, new_states, states_queue);
    }
    if (state->one.empty()){
        insert_new_state("-1", cont, state->state_number, new_states, states_queue);
    }
    else if (state->one.size() == 1)
        states[state->state_number]->zero = state->zero[0]->state_number;
    else{
        std::string id;
        for (auto& s: state->one)
            id += std::to_string(s->state_number);
        insert_new_state(id, cont, state->state_number, new_states, states_queue);
    }
}

void AFD::insert_new_state(std::string id, int& cont, int index, std::unordered_map<std::string, int>& new_states, std::queue<std::string>& states_queue){
    if (new_states.find(id) == new_states.end()){
        new_states.insert(std::make_pair(id, cont));
        states.push_back(new state_d(cont++));
        states_queue.push(id);
    } else
        states[index]->zero = new_states[id];
}


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

    std::vector<int> finals;
    
    for (auto &state: afd->states){
        states[state->zero]->set_relation(0, states[state->state_number]);
        states[state->one]->set_relation(1, states[state->state_number]);

        if (state->is_final)
            finals.push_back(state->state_number);
        else
            states[state->state_number]->is_final = true;        
    }
    states[afd->initial->state_number]->is_final = true;

    if (finals.size() == 1)
        initial = states[finals[0]];
    else {
        initial = new state_n(n_states++);
        states.push_back(initial);
        for (auto n: finals)
            initial->closure.push_back(states[n]);
    }
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