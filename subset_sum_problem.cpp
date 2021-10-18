#include <vector>
#include <iostream>
#include <fstream>
#include <functional>


void log(std::vector<bool> solution, std::vector<int> subset, std::ostream &out = std::cout) {
    out << "set :" << "\n";
    for (auto v: subset) {
        out << v << ", ";
    }
    out << std::endl;
    out << "subset :" << "\n";
    for (auto v: solution) {
        out << v << ", ";
    }
    out << std::endl;
}

std::vector<int> read(std::istream &input_file) {
//    std::ifstream input_file(filename);
    std::vector<int> out;
    while (!input_file.eof()) {
        int value;
        input_file >> value;
        out.push_back(value);
    }
    return out;
}

int subset_sum(std::vector<bool> taken_items, std::vector<int> problem) {
    int sum = 0;
    for (int i = 0; i < taken_items.size(); i++) {
        if (taken_items[i]) {
            sum += problem[i];
        }
    }
    log(taken_items, problem);
    std::cout << "sum :" << "\n";
    return sum;
}

std::vector<bool> random_working_point(int problem_size) {
    srand(time(NULL));
    std::vector<bool> generated_working_point;
    for (int i = 0; i < problem_size; i++) {
        generated_working_point.push_back(rand() % 2);
    }
    return generated_working_point;
}

void iterate_working_point(std::vector<bool> &working_point, int iterator = 0) {
    if (iterator==working_point.size()) iterator=0;
    if (!working_point[iterator]) {
        working_point[iterator] = true;
    } else {
        working_point[iterator] = false;
        iterate_working_point(working_point,iterator+1);
    }
}

//
//std::vector<int> subset_sum(solution sol) {
//    std::vector<int> sum_vec;
//    int sum = 0;
//    log(sol);
//    for(int i=0; i<sol.amount_of_solutions; i++){
//        for (auto v: sol.solutions ) {
//            for (int j = 0; j < v.size(); j++) {
//                if (v[j]) {
//                    sum += sol.problem[j];
//                }
//            }
//            std::cout << "suma " << std::endl;
//            sum_vec.push_back(sum);
//
//        }
//    }
//    return sum_vec;
//}
