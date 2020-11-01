#include "state.h"

#include <iostream>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

class AFN;

class AFD{
private:
    int n_states;
    int n_final;
    state_d* initial;
    std::vector <state_d*> states;

    void fill_transitions();
    void set_final_states(std::vector<int> finals);
    void verify_state(int& cont, state_n* state, std::unordered_map<std::string, int>& new_states, std::queue<std::string>& states_queue);
    void insert_new_state(std::string id, int& cont, int index, std::unordered_map<std::string, int>& new_states, std::queue<std::string>& states_queue);

public:
    AFD(int n, int initial_state, std::vector<int> finals);
    AFD(AFN* afn);
    friend class AFN;
};



class AFN{
private:
    int n_states;
    int n_final;
    state_n* initial;
    std::vector <state_n*> states{};

public:
    inline AFN() : initial(nullptr) {};
    AFN(AFD* afd);
    void printAFN();
    friend class AFD;
};