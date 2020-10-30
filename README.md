# ProyectoTeo


AFD class contains:
    # of states
    # of final states
    pointer to initial state
    set of states
    set of names of final states

Each state contains:
    name of the state
    pointer to the state after getting 1 as input
    pointer to the state after getting 0 as input


---Note: It s possible to represent the whole set of states and rules with a 2-dimensional array or a map. This implementation design would have been easier to implement, but Alexander realised this after coding the AFD as an independent Class. Maybe in the future Alexander will add an alternative implementation of the AFD just using a matrix or stuff like that.
