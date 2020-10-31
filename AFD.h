#include "state.h"

#include <iostream>
#include <vector>

class AFD{
	private:
        int n_states;
        int n_final;
        state* initial;
        std::vector <state*> states;

        void fill_transitions();
        void set_final_states(std::vector<int> finals);

	public:

        AFD(int n, int initial_state, std::vector<int> finals);

};