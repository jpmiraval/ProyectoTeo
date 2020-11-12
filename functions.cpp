#include "functions.h"

AFD* read_AFD(){
    std::vector<int> final_states;
	int n, initial_state, n_final_states, temp;
	std::cin >> n >> initial_state >> n_final_states;

	while(n_final_states--){
		std::cin >> temp;
		final_states.push_back(temp);
	}
	return new AFD(n, initial_state, final_states);
}

void  brzozowski(){
    auto afd = read_AFD();
    afd->printAFD();
    auto afnR = new AFN(afd);
    std::cout << '\n'; afnR->printAFN();
    auto afdR = new AFD(afnR);
    std::cout << '\n'; afdR->printAFD();
    auto afnF= new AFN (afdR);
    std::cout << '\n'; afnF->printAFN();
    auto afdF = new AFD (afnF);
    std::cout << '\n'; afdF->printAFD();

    std::cout << "\nResult:";
    afdF->getAFD();
}

int** Eq_test(AFD afd){
    int counter = 1;
    int n = afd.getsize();

    int** matrix = new int*[n];

    for( int i=0; i<n ; i++){
        matrix[i] = new int[n];
    }


    for(auto& i : afd.getStates()){
        for(auto& j : afd.getStates()){
            int p = i.second->is_final;
            int q = j.second->is_final;
            if( (!(p & q)) && (p | q) ){
                matrix[i.first][j.first] = 0;
            }else{
                matrix[i.first][j.first] = 1;
            }
        }
    }



    while (counter > 0){
        counter = 0;
        for(int i=1;i<n;i++)
            for(int j=0;j<=i-1;j++){
                if(matrix[i][j] == 0)continue;

                auto i_zero = afd.getStates()[i]->zero;
                auto j_zero = afd.getStates()[j]->zero;

                if(matrix[i_zero][j_zero] == 0){
                    matrix[i][j] = 0;
                    matrix[j][i] = 0;
                    counter++;
                    continue;
                }


                auto i_uno = afd.getStates()[i]->one;
                auto j_uno = afd.getStates()[j]->one;

                if(matrix[i_uno][j_uno] == 0){
                    matrix[i][j] = 0;
                    matrix[j][i] = 0;
                    counter++;
                    continue;
                }
            }
    }


    /* PRINT -----------------------------*/
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<=i-1;j++)
        {
            std::cout<< matrix[i][j];
        }
        printf("\n");
    }

    std::cout << "\n\n";

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