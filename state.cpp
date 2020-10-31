#include "state.h"

void state::set_relation(int i, state* estado){
		switch(i){
			case 0:
				zero = estado;
				break;
			case 1:
				one = estado;
				break;
		}
	}

state* state::go_zero(){
		return zero;
	}

state* state::go_one(){
	return one;
}

bool state::get_is_final(){
	return is_final;
}

void state::set_is_final(bool final){
	is_final = final;
}