#include <vector>
#include <iostream>
#include <functional>
#include <fstream>
#include <time.h>
#include "subset_sum_problem.hpp"


using namespace std;

vector<bool> hill_climbing(function<double(vector<bool>, vector<int>)> f, vector<bool> p, vector<int> problem) {
    int iterator =0;
    while (true) {

        vector<bool> p_copy = p;
        vector<vector<bool>> ap_pts = create_approximate_working_points(p_copy, problem);
        for (auto p2: ap_pts) {

            if (f(p2,problem) < f(p, problem)) {
                cout << endl<< "iteration : " << iterator << "->" <<  goal_function(p2, problem) << endl;
                p = p2;
            }
        }
        if (p == p_copy) {
            break;
        }
        iterator++;
    }
    return p;
}


vector<bool> hill_climbing_stochastic(function<double(vector<bool>, vector<int>)> f, vector<bool> p, vector<int> problem) {
    int iterator =0;
    while (true) {

        vector<bool> p_copy = p;
        vector<vector<bool>> ap_pts = create_approximate_working_points(p_copy, problem);
        for (auto p2: ap_pts) {

            if (f(p2,problem) < f(p, problem)) {
                cout << endl<< "iteration : " << iterator << "->" <<  goal_function(p2, problem) << endl;
                p = p2;
            }
        }
        if (p == p_copy) {
            break;
        }
        iterator++;
    }
    return p;
}



int main(int argc, char **argv) {
    string infile = "set.txt";

    if (argc == 2) infile = argv[1];
    ifstream hook_in(infile);

    vector<int> problem = read(hook_in);
    vector<bool> choice = random_working_point(problem.size());

    clock_t start = clock();
    vector<bool> best_result = choice;
    int options = int(pow(2, problem.size()));
    for (int i = 0; i < options; i++) {
        cout << "test";
        vector<bool> result = subset_sum(choice, problem);
        if (goal_function(result, problem) < goal_function(best_result,problem)){
            best_result = result;
        }
        iterate_working_point(choice);
    }
    if (argc == 3) {
        ofstream hook_out;
        hook_out.open(argv[2], std::ios::out);
        log(best_result, problem, hook_out);
        hook_out.close();
    }


    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    if (argc == 3) {
        ofstream hook_out;
        hook_out.open(argv[2], std::ios_base::app);
        hook_out << "time:" << elapsed;
        hook_out.close();
    }
    cout << "full time:" << elapsed << endl;

    start = clock();
    vector<bool> wp = random_working_point(problem.size());
    vector<bool> test_result = hill_climbing(goal_function, wp, problem);
    end = clock();
    elapsed = double(end - start) / CLOCKS_PER_SEC;
    cout << "hillclimb time:" << elapsed<<endl;




    return 0;
}
