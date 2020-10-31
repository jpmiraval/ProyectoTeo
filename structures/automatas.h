#include "state.h"

#include <iostream>

class AFN;

class AFD{
private:
    int n_states;
    int n_final;
    state_d* initial;
    std::vector <state_d*> states;

    void fill_transitions();
    void set_final_states(std::vector<int> finals);

public:
    AFD(int n, int initial_state, std::vector<int> finals);
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