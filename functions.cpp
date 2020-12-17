#include "functions.h"
#include "utility"
#include "set"

AFD *read_AFD() {
    std::vector<int> final_states;
    int n, initial_state, n_final_states, temp;
    std::cin >> n >> initial_state >> n_final_states;

    while (n_final_states--) {
        std::cin >> temp;
        final_states.push_back(temp);
    }
    return new AFD(n, initial_state, final_states);
}

void brzozowski() {
    auto afd = read_AFD();
    afd->printAFD();
    auto afnR = new AFN(afd);
    std::cout << '\n';
    afnR->printAFN();
    auto afdR = new AFD(afnR);
    std::cout << '\n';
    afdR->printAFD();
    auto afnF = new AFN(afdR);
    std::cout << '\n';
    afnF->printAFN();
    auto afdF = new AFD(afnF);
    std::cout << '\n';
    afdF->printAFD();

    std::cout << "\nResult:";
    afdF->getAFD();
}

int **Eq_test(AFD afd) {
    int counter = 1;
    int n = afd.getsize();

    int **matrix = new int *[n];

    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }


    for (auto &i : afd.getStates()) {
        for (auto &j : afd.getStates()) {
            int p = i.second->is_final;
            int q = j.second->is_final;
            if ((!(p & q)) && (p | q)) {
                matrix[i.first][j.first] = 0;
            } else {
                matrix[i.first][j.first] = 1;
            }
        }
    }


    while (counter > 0) {
        counter = 0;
        for (int i = 1; i < n; i++)
            for (int j = 0; j <= i - 1; j++) {
                if (matrix[i][j] == 0)continue;

                auto i_zero = afd.getStates()[i]->zero;
                auto j_zero = afd.getStates()[j]->zero;

                if (matrix[i_zero][j_zero] == 0) {
                    matrix[i][j] = 0;
                    matrix[j][i] = 0;
                    counter++;
                    continue;
                }


                auto i_uno = afd.getStates()[i]->one;
                auto j_uno = afd.getStates()[j]->one;

                if (matrix[i_uno][j_uno] == 0) {
                    matrix[i][j] = 0;
                    matrix[j][i] = 0;
                    counter++;
                    continue;
                }
            }
    }


    /* PRINT -----------------------------*/
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i - 1; j++) {
            std::cout << matrix[i][j];
        }
        printf("\n");
    }

    /*
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<=i;j++)
        {
            std::cout<< i << j << "";
        }
        printf("\n");
    }
    ---------------------------------------*/


    return matrix;
}

struct estructura {
    std::pair<int, int> id;
    std::vector<std::pair<int, int> *> dependencies;

    estructura(std::pair<int, int> id) : id(id) {};

    std::vector<std::pair<int, int> *> getDependencies() {
        return dependencies;
    }

    void addDependencie(std::pair<int, int> *dependencie) {
        dependencies.push_back(dependencie);
    }
};


int **Eq_test_op(AFD afd) {
    auto states = afd.getStates();
    int n = afd.getsize();
    int **matrix = new int *[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    for (auto &i : states) {
        for (auto &j : states) {

            int p = states[i.first]->is_final;
            int q = states[j.first]->is_final;

            if ((!(p & q)) && (p | q)) {
                matrix[i.first][j.first] = 0;
            } else {
                matrix[i.first][j.first] = 1;
            }
        }
    }
    //Creamos la estructura de dependencias
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>> *> dependencies;
    //Iteramos por la matriz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)continue;
            if (matrix[i][j] == 0 || matrix[j][i] == 0)continue;
            int i_zero = states[i]->zero;
            int i_one = states[i]->one;
            int j_zero = states[j]->zero;
            int j_one = states[j]->one;
            //tiene las dependencias(recursividad)
            std::queue<std::pair<int, int>> colita;
            if (matrix[i_zero][j_zero] == 0 || matrix[i_one][j_one] == 0 || matrix[j_zero][i_zero] == 0 || matrix[j_one][i_one] == 0) {
                matrix[i][j] = 0;
                matrix[j][i] = 0;
                if (dependencies.find(std::make_pair(i, j)) == dependencies.end()) {
                    continue;
                } else {
                    for (auto dependency : *dependencies[std::make_pair(i, j)]) {
                        colita.push(std::make_pair(dependency.first, dependency.second));
                    }
                    while (!colita.empty()) {
                        std::pair<int, int> paircito = colita.front();
                        colita.pop();
                        matrix[paircito.first][paircito.second] = 0;
                        if (dependencies.find(std::make_pair(paircito.first, paircito.second)) == dependencies.end()) {
                        } else {
                            for (auto dependency_b : *dependencies[std::make_pair(paircito.first, paircito.second)]) {
                                colita.push(std::make_pair(dependency_b.first, dependency_b.second));
                                colita.push(std::make_pair(dependency_b.second, dependency_b.first));
                            }
                        }
                    }
                }
            } else {
                bool same_zero = true;
                bool inv_zero = true;
                bool same_one = true;
                bool inv_one = true;

                if (i_zero == i and j_zero == j) {
                    same_zero = false;
                } else if (i_zero == j and j_zero == i) {
                    inv_zero = false;
                }
                if (i_one == i and j_one == j) {
                    same_one = false;
                } else if (i_zero == j and j_zero == i) {
                    inv_one = false;
                }
                if (i_zero != j_zero and same_zero and inv_zero) {
                    if(dependencies.find(std::make_pair(i_zero, j_zero)) == dependencies.end())
                    dependencies[std::make_pair(i_zero, j_zero)] = new std::vector<std::pair<int, int>>;


                        dependencies[std::make_pair(i_zero, j_zero)]->push_back(std::make_pair(i, j));
                        dependencies[std::make_pair(i_zero, j_zero)]->push_back(std::make_pair(j, i));


                }
                if (i_one != j_one and same_one and inv_one) {
                    if(dependencies.find(std::make_pair(i_one, j_one)) == dependencies.end())
                    dependencies[std::make_pair(i_one, j_one)] = new std::vector<std::pair<int, int>>;

                        dependencies[std::make_pair(i_one, j_one)]->push_back(std::make_pair(i, j));
                        dependencies[std::make_pair(i_one, j_one)]->push_back(std::make_pair(j, i));

                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            std::cout << matrix[i][j];
        }
        printf("\n");
    }

    std::cout << "\n\n";

    return matrix;
}


int find_initial(int initial, std::set<std::set<int> *> &partitions) {
    int counter = 0;
    for (auto partition : partitions) {
        for (auto element : *partition) {

            if (element == initial) {
                return counter;
            }

        }
        counter++;
    }
}

std::vector<int> find_finals(std::vector<int> finals, std::set<std::set<int> *> &partitions) {
    int counter = 0;
    std::vector<int> new_finals;
    for (auto partition : partitions) {
        for (auto final : finals) {
            for (auto c : *partition) {
                if (final == c) {

                    if (new_finals.empty()) {
                        new_finals.push_back(counter);
                    } else {
                        if (std::find(new_finals.begin(), new_finals.end(), counter) == new_finals.end()) {
                            new_finals.push_back(counter);
                        }
                    }
                }
            }
        }
        counter++;
    }
    return new_finals;
}

int translate(int old, std::set<std::set<int> *> &partitions) {
    int counter = 0;
    for (auto partition : partitions) {
        for (auto element : *partition) {
            if (element == old) {
                return counter;
            }
        }
        counter++;
    }
    return -1;
}

void insertar(int i, int j, std::set<std::set<int> *> &partitions, bool flag) {
    bool found_i = false;
    bool found_j = false;
    std::set<int> *first_reference;
    std::set<int> *second_reference;

    //Si i y j son equivalentes
    if (flag) {
        for (auto c : partitions) {
            for (auto k : *c) {
                //Cuando aun no encuentro ninguno
                if (!(found_j or found_i)) {
                    //Si encuentro i, señalo que lo encontre y guardo la referencia a su partición.
                    if (k == i) {
                        found_i = true;
                        first_reference = c;
                    }
                        //Si encuentro j, señalo que lo encontre, y guardo la referencia.
                    else if (k == j) {
                        found_j = true;
                        first_reference = c;
                    }
                }
                    //Si he encontrado alguno
                else {
                    //Si encuentro i
                    if (k == i) {
                        found_i = true;
                        second_reference = c;
                    } else if (k == j) {
                        found_j = true;
                        second_reference = c;
                    }
                }
            }
        }
        //Ya tengo las referencias de las particiones
        //Si ya se encuentran en la misma particion.
        if (first_reference == second_reference) {
            return;
        }
            //Si se encuentran en particiones diferentes
        else if (found_j and found_i) {
            //Hacemos merge de las partciones.
            for (auto c : *second_reference) {
                first_reference->insert(c);
            }
            partitions.erase(second_reference);
        }
            //Si solo encontre i
        else if (found_i) {
            //Insertamos a j en la partcion de i
            first_reference->insert(j);
        }
            //Si encontramos solo j
        else if (found_j) {
            //Insertamos en la misma particion de j
            first_reference->insert(i);
        }
            //No hemos encontrado ninguno de los dos en ninguna particion
        else {
            //Creamos una nueva particion con ambos valores
            std::set<int> *partition = new std::set<int>;
            partition->insert(i);
            partition->insert(j);
            partitions.insert(partition);
        }
    }
        //Si i y j son distinguibles
    else {
        for (auto partition : partitions) {
            if (partition->find(i) != partition->end()) {
                found_i = true;
            }
            if (partition->find(j) != partition->end()) {
                found_j = true;
            }
        }
        if (found_i) {
            if (!found_j) {
                std::set<int> *partition = new std::set<int>;
                partition->insert(j);
                partitions.insert(partition);
            }
            return;
        }
        if (found_j) {
            if (!found_i) {
                std::set<int> *partition = new std::set<int>;
                partition->insert(i);
                partitions.insert(partition);
            }
            return;
        }
    }
}

AFD *Huffman_Moore(AFD afd) {
    //Eliminamos losestados no alcanzables
    //Cargamos los states originales
    auto states = afd.getStates();
    int n = afd.getsize();
    std::set<int> total;
    for (int i = 0; i < n; i++) {
        total.insert(i);
    }
    std::set<int> reachables;
    std::set<int> unreachables;
    std::queue<int> quecito;
    //Tomamos el estado inicial
    auto initial_state = states[afd.geInitial()];
    quecito.push(initial_state->state_number);
    while (!quecito.empty()) {
        auto actual_state = quecito.front();
        quecito.pop();
        reachables.insert(actual_state);
        if (reachables.find(states[actual_state]->zero) == reachables.end()) {
            quecito.push(states[actual_state]->zero);
        }
        if (reachables.find(states[actual_state]->one) == reachables.end()) {
            quecito.push(states[actual_state]->one);
        }
    }
    for (auto c : total)
        if (reachables.find(c) == reachables.end()) {
            unreachables.insert(c);
        }
    // set unreachable tiene ahora los stados inalcanzables
    // Procedemos a eliminar los stados no alcanzables y renombrar los states afectados.
    for (auto unreachable_state : unreachables) {
        //disminuir en 1 el tamaño del afd;
        afd.setSize(afd.getsize() - 1);
        for (auto state : states) {
            if (state.second->one > unreachable_state) {
                state.second->set_relation(1, state.second->one - 1);
            }
            if (state.second->zero > unreachable_state) {
                state.second->set_relation(0, state.second->zero - 1);
            }
            if (state.first > unreachable_state) {
                states.at(state.first - 1) = states[state.first];
                states[state.first - 1]->state_number--;
            }
        }
        states.erase(afd.getsize());
    }
    afd.updateStates(states);

    int **matrix = Eq_test_op(afd);
    n = afd.getsize();
    std::set<std::set<int> *> partitions;

    //Creamos las particiones
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)continue;
            if (matrix[i][j] == 1) {
                if (partitions.empty()) {
                    std::set<int> *new_partition = new std::set<int>;
                    new_partition->insert(i);
                    new_partition->insert(j);
                    partitions.insert(new_partition);
                } else {
                    insertar(i, j, partitions, 1);
                }
            } else {
                if (partitions.empty()) {
                    std::set<int> *new_partition = new std::set<int>;
                    std::set<int> *new_partition2 = new std::set<int>;
                    new_partition->insert(i);
                    new_partition2->insert(j);
                    partitions.insert(new_partition);
                    partitions.insert(new_partition2);
                } else {
                    insertar(i, j, partitions, 0);
                }
            }
        }
    }
    int new_initial = find_initial(afd.geInitial(), partitions);
    int number = partitions.size();
    std::vector<int> new_final_states = find_finals(afd.geFinals(), partitions);
    AFD *new_AFD = new AFD(number, new_initial, new_final_states, true);

    auto new_states = new_AFD->getStates();
    for (auto i = 0; i < n; i++) {
        new_states[translate(i, partitions)]->set_relation(0, translate(states[i]->zero, partitions));
        new_states[translate(i, partitions)]->set_relation(1, translate(states[i]->one, partitions));
    }

    return new_AFD;
};

AFD *Hopcroft(AFD afd) {
    //Separamos el afd en grupos según su comportamiento de final o no final
    std::set<std::set<int> *> nondistinguishable;
    std::set<std::set<int> *> Partitions;
    auto states = afd.getStates();
    std::set<int> *new_set = new std::set<int>;
    std::set<int> *new_set2 = new std::set<int>;
    for (auto c : states) {
        if (c.second->is_final) {
            new_set->insert(c.first);
        } else {
            new_set2->insert(c.first);
        }
    }
    //Insertamos las particioncitas de no finales y finales.
    nondistinguishable.insert(new_set);
    nondistinguishable.insert(new_set2);
    Partitions = nondistinguishable;
    std::set<int> intersection;
    bool flag = true;
    //Empezamos a iterar
    while (!nondistinguishable.empty()) {
        intersection.clear();
        //Elegimos el distinct más pequeño y lo almacenamos en min
        std::set<int> *min = nullptr;
        for (auto a : nondistinguishable) {
            if (min == nullptr) {
                min = a;
            } else {
                if (min->size() > a->size()) {
                    min = a;
                }
            }
        }
        for (auto a : Partitions) {
            for (auto m : *a) {
                if (min->find(states[m]->zero) != min->end()) {
                    intersection.insert(m);
                }
            }
            if (intersection.size() == a->size() || intersection.size() == 0) {
                intersection.clear();
                for (auto m : *a) {
                    if (min->find(states[m]->one) != min->end()) {
                        intersection.insert(m);
                    }
                }
            }
            if (intersection.size() == a->size() || intersection.size() == 0) {
                intersection.clear();
                continue;
            }

            std::set<int> *temp = new std::set<int>;
            for (auto s : intersection) {
                a->erase(s);
                temp->insert(s);
            }
            Partitions.insert(temp);
            if (a->size() > temp->size()) {
                nondistinguishable.insert(temp);
            } else {
                nondistinguishable.insert(a);
            }
            intersection.clear();
        }
        nondistinguishable.erase(min);
    }



    int new_initial = find_initial(afd.geInitial(), Partitions);
    int number = Partitions.size();
    std::vector<int> new_final_states = find_finals(afd.geFinals(), Partitions);
    AFD *new_AFD = new AFD(number, new_initial, new_final_states, true);
    auto new_states = new_AFD->getStates();
    for (auto i = 0; i < afd.getsize(); i++) {
        new_states[translate(i, Partitions)]->set_relation(0, translate(states[i]->zero, Partitions));
        new_states[translate(i, Partitions)]->set_relation(1, translate(states[i]->one, Partitions));
    }
    return new_AFD;
}
