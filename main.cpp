#include <vector>
#include <iostream>
#include <functional>
#include <fstream>
#include <time.h>
#include "subset_sum_problem.hpp"

using namespace std;



int main(int argc, char **argv) {
    string infile = "set.txt";

    if (argc == 2) infile = argv[1];
    ifstream hook_in(infile);


    vector<int> problem = read(hook_in);
    vector<bool> choice = random_working_point(problem.size());

    int options = int(pow(2, choice.size()));
    double best_result = 0.0;
    clock_t start = clock();
    for (int i = 0; i < options; i++) {
        if (argc == 3){
            ofstream hook_out;
            hook_out.open(argv[2], std::ios_base::app);
            pair result = subset_sum(choice, problem, hook_out);
            if (result.second>best_result){
                cout << result.second;
            }
            iterate_working_point(choice);
            hook_out.close();
        }else{
            subset_sum(choice, problem);
            iterate_working_point(choice);
        }
    }
    clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;
        if (argc == 3){
        ofstream hook_out;
        hook_out.open(argv[2], std::ios_base::app);
        hook_out << "time:" << elapsed;
        hook_out.close();
    }

    cout << "time:" << elapsed;

    return 0;
}
