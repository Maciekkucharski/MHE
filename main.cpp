#include <vector>
#include <iostream>
#include <functional>
#include <fstream>
#include <ctime>
#include "subset_sum_problem.hpp"
#include <cmath>
#include <random>
#include <chrono>
#include <set>


auto tabu_search = [](
        auto cost,
        auto generate_first_point,
        auto neighbours_f, /// current work point neighbours
        int N,
        int tabu_size,
        std::vector<int> problem,
        std::function<void(int c, double dt)> on_statistics = [](int c, double dt) {}) {
    using namespace std;
    auto start = chrono::steady_clock::now();

    auto best_p = generate_first_point();

    set<decltype(best_p)> taboo_set;
    list<decltype(best_p)> taboo_list;

    auto is_in_taboo = [&](auto e) {
        //if (taboo_set.count(e)) cerr << "tabu hit" << endl;
        return taboo_set.count(e);
    };
    auto add_to_taboo = [&](auto e) {
        taboo_set.insert(e);
        taboo_list.push_back(e);
    };
    auto shrink_taboo = [&]() {
        if (taboo_set.size() > tabu_size) {
            taboo_set.erase(taboo_list.front());
            taboo_list.pop_front();
            cerr << "shrink list" << endl;
        }
    };

    auto p = best_p; // current work point

    int iterator = 0;
    while ((iterator < N) && (goal_function(p, problem)) > 1) {
        auto neighbours = neighbours_f(best_p);
        neighbours.erase(std::remove_if(neighbours.begin(),
                                        neighbours.end(),
                                        [&](auto e) { return is_in_taboo(e); }),
                         neighbours.end());
        if (neighbours.size() == 0) break;
        p = *max_element(neighbours.begin(), neighbours.end(), [&](auto a, auto b) {
            return cost(a, problem) > cost(b, problem);
        });
        add_to_taboo(p);
        const double cost_value = cost(p, problem);
        if (cost(p, problem) < cost(best_p, problem)) {
            best_p = p;
            cout << "# TL better:  " << cost(best_p, problem) << endl;
        }
        shrink_taboo();
        iterator++;
    }


//    for (int i = 0; i < N; i++) {
//
//    }
    auto finish = chrono::steady_clock::now();
    chrono::duration<double> duration = finish - start;
    on_statistics(N, duration.count());
    return best_p;
};

using namespace std;

vector<bool>
hill_climbing(function<double(vector<bool>, vector<int>)> f, vector<bool> p, vector<int> problem, int iterations) {
    int iterator = 0;
    while ((iterator < iterations) && (goal_function(p, problem)) > 1) {

        vector<bool> p_copy = p;
        vector<vector<bool>> ap_pts = create_approximate_working_points(p_copy);
        for (auto p2: ap_pts) {

            if (f(p2, problem) < f(p, problem)) {
                cout << endl << "iteration : " << iterator << "->" << goal_function(p2, problem) << endl;
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


vector<bool>hill_climbing_stochastic(function<double(vector<bool>, vector<int>)> f, vector<bool> p, vector<int> problem,
                         int interations) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, p.size() - 1);
    int iterator = 0;
    while ((iterator < interations) && (goal_function(p, problem)) > 1) {

        vector<bool> p_copy = p;
        vector<vector<bool>> ap_pts = create_approximate_working_points(p_copy);

        for (int i = 0; i < ap_pts.size(); ++i) {
            int random_iteration = distrib(gen);
            if (f(ap_pts[random_iteration], problem) < f(p, problem)) {
                cout << endl << "iteration : " << iterator << "->" << goal_function((ap_pts[random_iteration]), problem)
                     << endl;
                p = (ap_pts[random_iteration]);
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
    string infile = argv[1];
    cout << infile;
    ifstream hook_in(infile);

//    if (argc == 2) infile = argv[1];
//    cout << infile;
//    ifstream hook_in(infile);

    int i = 20;

    vector<int> problem = read(hook_in);
    vector<bool> choice = random_working_point(problem.size());

    clock_t start = clock();
    //brute force
//    vector<bool> best_result = choice;
//    double options = (pow(2, problem.size()));
//    for (int i = 0; i < options; i++) {
//        if (goal_function(choice, problem) < goal_function(best_result,problem)){
//            best_result = choice;
//            cout << endl << " result :" << "\n";
//            for (auto v: choice) {
//                cout << v << ", ";
//            }
//            cout << " score : " << goal_function(choice, problem);
//        }
//        if (goal_function(best_result, problem) == 0) break;
//        iterate_working_point(choice);
//    }
//    cout<< endl << "best result :" << "\n";
//    for (auto v: best_result) {
//        cout << v << ", ";
//    }
//    cout << " score : " << goal_function(best_result, problem);
//    if (argc == 3) {
//        ofstream hook_out;
//        hook_out.open(argv[2], std::ios::out);
//        log(best_result, problem, hook_out);
//        hook_out.close();
//    }
//
//
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;

//    if (argc == 3) {
//        ofstream hook_out;
//        hook_out.open(argv[2], std::ios_base::app);
//        hook_out << "time:" << elapsed;
//        hook_out.close();
//    }
//    cout << endl << "full time:" << elapsed << endl;
    //hillclimb
    for (int j = 0; j < 10; ++j) {
        vector<bool> wp = random_working_point(problem.size());
        start = clock();

        vector<bool> result = hill_climbing(goal_function, wp, problem, i);
        end = clock();
        elapsed = double(end - start) / CLOCKS_PER_SEC;
        cout << "hillclimb time:" << elapsed << endl;

        string filename = "hill_climb_size_3000_iterations_20";
        ofstream hook_out;
        hook_out.open(filename, std::ios_base::app);
        hook_out << "hillclimb 1000 " << elapsed << " " << goal_function(result, problem) << endl;
        hook_out.close();
    }

//
//    //hillclimb stochastic
    for (int j = 0; j < 10; ++j) {
        vector<bool> wp = random_working_point(problem.size());
        start = clock();
        wp = random_working_point(problem.size());
        vector<bool> result = hill_climbing_stochastic(goal_function, wp, problem, i);
        end = clock();
        elapsed = double(end - start) / CLOCKS_PER_SEC;
        cout << "hillclimb stochastic time:" << elapsed << endl;

        string filename = "hill_climb_stochastic_size_3000_iterations_20";
        ofstream hook_out;
        hook_out.open(filename, std::ios_base::app);
        hook_out << "hillclimb_stochastic 1000 " << elapsed << " " << goal_function(result, problem) << endl;
        hook_out.close();
    }
    //taboo search
    for (int j = 0; j < 10; ++j) {
        vector<bool> wp = random_working_point(problem.size());
        start = clock();
        vector<bool> result_ts = tabu_search(
                goal_function,
                [&]() { return wp; },
                create_approximate_working_points,
                i,
                100,
                problem,
                [](int c, double dt) {
                    cout << "# count TS: " << c << "; dt:  " << dt << endl;
                });
        end = clock();
        elapsed = double(end - start) / CLOCKS_PER_SEC;
        cout << "taboo time:" << elapsed << endl;


        string filename = "taboo_size_3000_iterations_20";
        ofstream hook_out;
        hook_out.open(filename, std::ios_base::app);
        hook_out << "hillclimb_stochastic 1000 " << elapsed << " " << goal_function(result_ts, problem) << endl;
        hook_out.close();

    }
    return 0;
}
