//we consider languages 0,1 and states labeled from 1 to n-1.
#include <vector>

struct state{
    int state_number;
    bool is_final;
    
    state(int stat ) : state_number(stat), is_final(false) {};
};



struct state_d : state{
    int zero;
    int one;

    state_d(int stat): state(stat), zero(-1), one(-1) {};
    void set_relation(int i, int estado);
};



struct state_n : state{
    std::vector<state_n*> zero{};
    std::vector<state_n*> one{};

    state_n(int stat): state(stat) {};
    void set_relation(int i, state_n* estado);
};