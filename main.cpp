#include <vector>
#include <iostream>
#include <functional>
#include <fstream>
#include "subset_sum_problem.hpp"

using namespace std;

int main(int argc, char **argv) {
    string infile = "set.txt";

    if (argc == 2) infile = argv[1];
    ifstream hook_in(infile);
    if (argc == 3){
        ofstream hook_out;
        hook_out.open(argv[2]);
        hook_out.close();
    }

    vector<int> problem = read(hook_in);
    vector<bool> choice = random_working_point(problem.size());

    int options = int(pow(2, choice.size()));

    for (int i = 0; i < options; i++) {
        if (argc == 3){
            ofstream hook_out;
            hook_out.open(argv[2], std::ios_base::app);
            subset_sum(choice, problem, hook_out);
            iterate_working_point(choice);
            hook_out.close();
        }else{
            subset_sum(choice, problem);
            iterate_working_point(choice);
        }
    }
    return 0;
}
