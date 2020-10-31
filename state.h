//we consider languages 0,1 and states labeled from 1 to n-1.

class state{
    private:
        int stat;
        bool is_final;
        state* zero;
        state* one;

    public:

        state(int stat ) : stat(stat), is_final(false), zero(nullptr), one(nullptr) {};
        void set_relation(int i, state* estado);

        state* go_zero();
        state* go_one();
        bool get_is_final();
        void set_is_final(bool final);
};

struct state_{
    int stat;
    bool is_final;
    state_* zero;
    state_* one;
    
    state_(int stat ) : stat(stat), is_final(false), zero(nullptr), one(nullptr) {};
    void set_relation(int i, state* estado);
};