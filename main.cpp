#include <vector>
#include <iostream>
#include <functional>
#include <fstream>
#include "subset_sum_problem.hpp"

using namespace std;

int main(int argc, char **argv) {
//    srand(time(NULL));
    string filename = "set.txt";
    if (argc == 2) filename = argv[1];
    ifstream hook(filename);
    vector<int> problem = read(hook);
    vector<bool> choice = random_working_point(problem.size());
    cout << subset_sum(choice, problem) << endl;
    iterate_working_point(choice);
    cout << subset_sum(choice, problem) << endl;


    return 0;
}
