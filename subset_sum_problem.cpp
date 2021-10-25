#include <vector>
#include <iostream>
#include <fstream>
#include <functional>


void log(int sum, std::vector<bool> solution, std::vector<int> subset, std::ostream &out) {
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
    out << "sum :" << sum << "\n";
    if (!sum) {
        out << "good solution\n\n";
    } else {
        out << "bad solution\n\n";
    }
}

std::vector<int> read(std::istream &input_file) {
    std::vector<int> out;
    while (!input_file.eof()) {
        int value;
        input_file >> value;
        out.push_back(value);
    }
    return out;
}

int subset_sum(std::vector<bool> taken_items, std::vector<int> problem, std::ostream &out = std::cout) {
    int sum = 0;
    for (int i = 0; i < taken_items.size(); i++) {
        if (taken_items[i]) {
            sum += problem[i];
        }
    }
    log(sum, taken_items, problem, out);

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
    if (iterator == working_point.size()) iterator = 0;
    if (!working_point[iterator]) {
        working_point[iterator] = true;
    } else {
        working_point[iterator] = false;
        iterate_working_point(working_point, iterator + 1);
    }
}



