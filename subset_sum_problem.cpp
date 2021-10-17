#include <vector>
#include <iostream>
#include <fstream>
#include <functional>


void log(std::vector<bool> solution, std::vector<int> subset) {
    std::cout << "subset :" << "\n";
    for (auto v: subset) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;
    std::cout << "choice :" << "\n";
    for (auto v: solution) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;
}

std::vector<int> read(const std::string &filename){
    std::ifstream input_file(filename);
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
    log(taken_items,problem);
    std::cout << "sum :" << "\n";
    return sum;
}
