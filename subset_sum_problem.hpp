//
// Created by Maciek on 17.10.2021.
//

#ifndef LAB1_SUBSET_SUM_PROBLEM_HPP
#define LAB1_SUBSET_SUM_PROBLEM_HPP
void log(std::vector<bool> solution, std::vector<int> subset);
std::vector<int> read(std::istream &input_file);
int subset_sum(std::vector<bool> taken_items, std::vector<int> problem);
std::vector<bool> random_working_point(int problem_size);
void iterate_working_point(std::vector<bool> &working_point, int iterator = 0);
#endif //LAB1_SUBSET_SUM_PROBLEM_HPP
