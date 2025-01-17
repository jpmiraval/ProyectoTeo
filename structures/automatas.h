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
    std::vector<int> finals;
    void fill_transitions();
    void set_final_states(const std::vector<int>& finals);

public:
    AFD(int n, int initial_state, const std::vector<int>& finals);
    AFD(int n, int initial_state, const std::vector<int>& finals, bool flag);
    AFD(AFN* afn);
    void printAFD();
    int getsize(){
        return n_states;
    }
    int setSize(int n){
        n_states = n;
    }
    void updateStates(std::map<int, state_d*> nuevo){
        states = nuevo;
    }
    int geInitial(){return initial->state_number;}
    std::vector<int> geFinals(){return finals;}
    std::map<int, state_d*> getStates(){return states;}
    void getAFD();
    friend class AFN;
};



class AFN{
private:
    int n_states;
    int n_final;
    state_n* initial;
    std::map<int, state_n*> states{};

    void fill_transitions(int trans);
    void set_final_states(const std::vector<int>& finals);

public:
    inline AFN() : initial(nullptr) {};
    AFN(int n, int initial_state, const std::vector<int>& finals, int trans);
    AFN(AFD* afd);

    void printAFN();
    void getAFN();
    friend class AFD;
};
