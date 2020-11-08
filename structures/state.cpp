#include "state.h"

void state_d::set_relation(int i, int estado){
    switch(i){
        case 0:
            zero = estado;
            break;
        case 1:
            one = estado;
            break;
    }
};


void state_n::set_relation(int i, int estado){
    switch(i){
        case 0:
            zero.push_back(estado);
            break;
        case 1:
            one.push_back(estado);
            break;
    }
};