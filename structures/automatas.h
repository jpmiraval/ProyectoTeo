#include "state.h"

#include <iostream>
#include <unordered_map>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <utility>
#include <string>

class AFN;

class AFD{
private:
    int n_states;
    int n_final;
    state_d* initial;
    std::map<int, state_d*> states;

    void fill_transitions();
    void set_final_states(std::vector<int> finals);

public:
    AFD(int n, int initial_state, std::vector<int> finals);
    AFD(AFN* afn);
    void printAFD();
    friend class AFN;
};



class AFN{
private:
    int n_states;
    int n_final;
    state_n* initial;
    std::map<int, state_n*> states{};

    void fill_transitions(int trans);
    void set_final_states(std::vector<int> finals);

public:
    inline AFN() : initial(nullptr) {};
    AFN(int n, int initial_state, std::vector<int> finals, int trans);
    AFN(AFD* afd);
    void printAFN();
    friend class AFD;
};