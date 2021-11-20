#include <vector>
#include <iostream>
#include <functional>
#include <tuple>

double goal_function(std::vector<bool> solution, std::vector<int> problem) {
    double sum = 0;
    for (double i = 0; i < solution.size(); ++i) {
        if (solution[i] == true)
            sum += problem[i];
    }
    return abs(sum);
}

void log(std::vector<bool> solution, std::vector<int> problem, std::ostream &out) {
    out << "problem :" << "\n";
    for (auto v: problem) {
        out << v << ", ";
    }
    out << std::endl;
    out << "subset :" << "\n";
    for (auto v: solution) {
        out << v << ", ";
    }
    out << std::endl;
    out << "result :" << goal_function(solution, problem) << "\n\n" ;
}

std::vector<int> read(std::istream &input_file) {

    std::vector<int> out;
    while (!input_file.eof()) {
        int value;
        input_file >> value;
        out.push_back(value);
//        std::cout << value;
    }
    return out;
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


std::vector<std::vector<bool>> create_approximate_working_points(std::vector<bool> working_point) {
    std::vector<std::vector<bool>> approximate_points;

    for (int i = 0; i < working_point.size(); ++i) {
        std::vector<bool> working_point_copy = working_point;
        working_point_copy[i] = !working_point[i];
        approximate_points.push_back(working_point_copy);
    }
    return approximate_points;
}


