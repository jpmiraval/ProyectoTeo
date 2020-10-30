#include <iostream>
#include <vector>

//we consider languages 0,1 and states labeled from 1 to n-1.

class state{
	private:
	int stat;
	state* zero;
	state* one;

	public:

	state(int stat ) : stat(stat){};
	void set_relation(int i, state* estado){
		switch(i){
			case 0:
				zero = estado;
				break;
			case 1:
				one = estado;
				break;
		}
	}

	state* goZero(){
		return zero;
	}

	state* goOne(){
		return one;
	}

};

class AFD{
	private:
	int n; // # of states
	int n_final; // # of final states
	state* inicial; // Initial state
	std::vector <state*> states; // Set of states
	std::vector <int> finals; // Set of final states


	public:

	AFD(int n, int n_final, std::vector<state*> states, std::vector<int> finals) : n(n), n_final(n_final), states(states), finals(finals){
	fill();
	}

	//Creates all rules of transitions between states.
	void fill(){
		int num1, num2, num3;
		for(int i = 0; i < n*2; i++){
			std::cin >> num1 >> num2 >> num3;
			states[num1]->set_relation(num2, states[num3]);
		}
	}

};

int  main(){
	std::vector <int> final_states;
	std::vector <state*> states;
	int num1, num2, num3, num4;
	std::cin >> num1 >> num2 >> num3;

	for(int i = 0; i < num1; i++){
		states.push_back(new state(i));
	}


	for(int i = 0; i < num3; i++){
		std::cin >> num4;
		final_states.push_back(num4);
	}

	AFD* afd = new AFD(num1, num2, states, final_states);

	return 0;
}
