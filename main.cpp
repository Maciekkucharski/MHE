#include <vector>
#include <iostream>
#include <functional>
#include "subset_sum_problem.hpp"

using namespace std;

int main(int argc, char **argv) {
    srand(time(NULL));
    string filename = "set.txt";
    if (argc == 2) filename = argv[1];

    vector<int> problem = read(filename);
    vector<bool> choice = {true, false, true, true, true, true, true};
    cout << subset_sum(choice, problem);

    return 0;
}
