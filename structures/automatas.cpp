#include "automatas.h"

AFD::AFD(int n, int initial_state, std::vector<int> finals) : n_states(n), n_final(finals.size()) {
    for(int i = 0; i < n_states; ++i)
        states[i] = new state_d(i);
    set_final_states(finals);
    fill_transitions();
    initial = states[initial_state];
};

//Conversión AFN a AFD
AFD::AFD(AFN* afn){
    std::map<std::set<int>*, int> new_states;
    std::set<int> added;
    std::queue<int> states_queue;
    int n = states.size();
    int cont = states.size();
    while(!states_queue.empty()){
        auto id = states_queue.front();
        states_queue.pop();

        states[id] = new state_d(id);

        if(afn->states[id]->zero.empty()){
            auto new_state = new std::set<int>;
            new_state->insert(-1);
            if (new_states.find(new_state) == new_states.end()) {
                added.insert(cont);
                states_queue.push(cont);
                new_states[new_state] = cont;
                afn->states[cont] = new state_n(cont++);
            }
            states[id]->zero = new_states[new_state];
        }
        
        else if (afn->states[id]->zero.size() == 1)
            states[1]->zero = afn->states[id]->zero[0]->state_number;
        else{
            auto new_state = new std::set<int>;
            for (auto i: afn->states[id]->zero)
                new_state->insert(i);

            if (new_states.find(new_state) == new_states.end()) {
                added.insert(cont);
                states_queue.push(cont);
                new_states[new_state] = cont;
                afn->states[cont] = new state_n(cont);
                std::queue<int> closure;
                std::set<int> visited;
                for (auto it=new_state->begin(); it!=new_state->end(); ++it){
                    for (auto i: afn->states[*it]->zero)
                        afn->states[cont]->zero.push_back(i);
                    for (auto i: afn->states[*it]->one)
                        afn->states[cont]->one.push_back(i);
                    for (auto i: afn->states[*it]->closure)
                        closure.push_back(i);
                }
                while (!closure.empty()){
                    auto c = closure.front();
                    closure.pop();
                    afn->states[cont]->closure.push_back(c);
                    visited.insert(c);
                    for (auto i: afn->states[c]->closure){
                        if (visited.find(i) == visited.end())
                            closure.push_back(i)
                    }
                }
            }
            states[id]->zero = new_states[new_state];
        }
        if (afn->states[id]->one.empty()){
            auto new_state = new std::set<int>;
            new_state->insert(-1);
            if (new_states.find(new_state) == new_states.end()) {
                added.insert(cont);
                states_queue.push(cont);
                new_states[new_state] = cont;
                afn->states[cont] = new state_n(cont++);
            }
            states[id]->one = new_states[new_state];
        }
        else if (afn->states[id]->one.size() == 1)
            states[afn->states[id]->state_number]->one = afn->states[id]->one[0]->state_number;
        else{
            auto new_state = new std::set<int>;
            for (auto i: afn->states[id]->one)
                new_state->insert(i);

            if (new_states.find(new_state) == new_states.end()) {
                added.insert(cont);
                states_queue.push(cont);
                new_states[new_state] = cont;
                afn->states[cont] = new state_n(cont);
                std::queue<int> closure;
                std::set<int> visited;
                for (auto it=new_state->begin(); it!=new_state->end(); ++it){
                    for (auto i: afn->states[*it]->zero)
                        afn->states[cont]->zero.push_back(i);
                    for (auto i: afn->states[*it]->one)
                        afn->states[cont]->one.push_back(i);
                    for (auto i: afn->states[*it]->closure)
                        closure.push_back(i);
                }
                while (!closure.empty()){
                    auto c = closure.front();
                    closure.pop();
                    afn->states[cont]->closure.push_back(c);
                    visited.insert(c);
                    for (auto i: afn->states[c]->closure){
                        if (visited.find(i) == visited.end())
                            closure.push_back(i)
                    }
                }
            }
            states[id]->one = new_states[new_state];
        }
    }
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
        states[i] = new state_n(i);

    std::vector<int> finals;
    
    for (auto& state: afd->states){
        states[state.second->zero]->set_relation(0, state.second->state_number);
        states[state.second->one]->set_relation(1, state.second->state_number);
        if (state.second->is_final)
            finals.push_back(state.second->state_number);
        else
            states[state.second->state_number]->is_final = true;        
    }
    states[afd->initial->state_number]->is_final = true;

    if (finals.size() == 1)
        initial = states[finals[0]];
    else {
        initial = new state_n(n_states);
        states[n_states++] = initial;
        for (auto n: finals)
            initial->closure.push_back(n);
    }
}

void AFN::printAFN(){
    for (auto& state: states){
        std::cout << "Number: " << state.second->state_number << "    Zero: ";
        for (auto& i: state.second->zero)
            std::cout << i->state_number << " ";
        std::cout << "    One: ";
        for (auto& i: state.second->one)
            std::cout << i->state_number << " ";
        std::cout << "\n";
    }
}